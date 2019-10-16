// Copyright (c) 2014 The Chromium Embedded Framework Authors.
// Portions copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "libcef/browser/osr/render_widget_host_view_osr.h"

#include <stdint.h>

#include <utility>

#include "libcef/browser/browser_host_impl.h"
#include "libcef/browser/osr/osr_util.h"
#include "libcef/browser/osr/software_output_device_osr.h"
#include "libcef/browser/thread_util.h"

#include "base/callback_helpers.h"
#include "base/command_line.h"
#include "base/memory/ptr_util.h"
#include "cc/base/switches.h"
#include "components/viz/common/frame_sinks/copy_output_request.h"
#include "components/viz/common/frame_sinks/delay_based_time_source.h"
#include "components/viz/common/gl_helper.h"
#include "components/viz/common/switches.h"
#include "content/browser/bad_message.h"
#include "content/browser/compositor/image_transport_factory.h"
#include "content/browser/frame_host/render_widget_host_view_guest.h"
#include "content/browser/renderer_host/dip_util.h"
#include "content/browser/renderer_host/render_widget_host_delegate.h"
#include "content/browser/renderer_host/render_widget_host_impl.h"
#include "content/browser/renderer_host/render_widget_host_view_frame_subscriber.h"
#include "content/common/input_messages.h"
#include "content/common/view_messages.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/context_factory.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/common/content_switches.h"
#include "media/base/video_frame.h"
#include "ui/gfx/geometry/dip_util.h"
#include "ui/gfx/geometry/size_conversions.h"

namespace {

const float kDefaultScaleFactor = 1.0;

// The maximum number of retry counts if frame capture fails.
const int kFrameRetryLimit = 2;

static content::ScreenInfo ScreenInfoFrom(const CefScreenInfo& src) {
  content::ScreenInfo screenInfo;
  screenInfo.device_scale_factor = src.device_scale_factor;
  screenInfo.depth = src.depth;
  screenInfo.depth_per_component = src.depth_per_component;
  screenInfo.is_monochrome = src.is_monochrome ? true : false;
  screenInfo.rect =
      gfx::Rect(src.rect.x, src.rect.y, src.rect.width, src.rect.height);
  screenInfo.available_rect =
      gfx::Rect(src.available_rect.x, src.available_rect.y,
                src.available_rect.width, src.available_rect.height);

  return screenInfo;
}

}  // namespace

// Used for managing copy requests when GPU compositing is enabled. Based on
// RendererOverridesHandler::InnerSwapCompositorFrame and
// DelegatedFrameHost::CopyFromCompositingSurface.
class CefCopyFrameGenerator {
 public:
  CefCopyFrameGenerator(int frame_rate_threshold_us,
                        CefRenderWidgetHostViewOSR* view)
      : view_(view),
        frame_retry_count_(0),
        next_frame_time_(base::TimeTicks::Now()),
        frame_duration_(
            base::TimeDelta::FromMicroseconds(frame_rate_threshold_us)),
        weak_ptr_factory_(this) {}

  void GenerateCopyFrame(const gfx::Rect& damage_rect) {
    if (!view_->render_widget_host())
      return;
    // The below code is similar in functionality to
    // DelegatedFrameHost::CopyFromCompositingSurface but we reuse the same
    // SkBitmap in the GPU codepath and avoid scaling where possible.
    // Let the compositor copy into a new SkBitmap
    std::unique_ptr<viz::CopyOutputRequest> request =
        std::make_unique<viz::CopyOutputRequest>(
            viz::CopyOutputRequest::ResultFormat::RGBA_BITMAP,
            base::Bind(
                &CefCopyFrameGenerator::CopyFromCompositingSurfaceHasResult,
                weak_ptr_factory_.GetWeakPtr(), damage_rect));

    request->set_area(gfx::Rect(view_->GetPhysicalBackingSize()));
    view_->GetRootLayer()->RequestCopyOfOutput(std::move(request));
  }

  void set_frame_rate_threshold_us(int frame_rate_threshold_us) {
    frame_duration_ =
        base::TimeDelta::FromMicroseconds(frame_rate_threshold_us);
  }

 private:
  void CopyFromCompositingSurfaceHasResult(
      const gfx::Rect& damage_rect,
      std::unique_ptr<viz::CopyOutputResult> result) {
    if (result->IsEmpty() || result->size().IsEmpty() ||
        !view_->render_widget_host()) {
      OnCopyFrameCaptureFailure(damage_rect);
      return;
    }

    std::unique_ptr<SkBitmap> source =
        std::make_unique<SkBitmap>(result->AsSkBitmap());
    DCHECK(source);

    if (source) {
      std::shared_ptr<SkBitmap> bitmap(std::move(source));

      base::TimeTicks now = base::TimeTicks::Now();
      base::TimeDelta next_frame_in = next_frame_time_ - now;
      if (next_frame_in > frame_duration_ / 4) {
        next_frame_time_ += frame_duration_;
        content::BrowserThread::PostDelayedTask(
            CEF_UIT, FROM_HERE,
            base::Bind(&CefCopyFrameGenerator::OnCopyFrameCaptureSuccess,
                       weak_ptr_factory_.GetWeakPtr(), damage_rect, bitmap),
            next_frame_in);
      } else {
        next_frame_time_ = now + frame_duration_;
        OnCopyFrameCaptureSuccess(damage_rect, bitmap);
      }

      // Reset the frame retry count on successful frame generation.
      frame_retry_count_ = 0;
    } else {
      OnCopyFrameCaptureFailure(damage_rect);
    }
  }

  void OnCopyFrameCaptureFailure(const gfx::Rect& damage_rect) {
    const bool force_frame = (++frame_retry_count_ <= kFrameRetryLimit);
    if (force_frame) {
      // Retry with the same |damage_rect|.
      CEF_POST_TASK(CEF_UIT,
                    base::Bind(&CefCopyFrameGenerator::GenerateCopyFrame,
                               weak_ptr_factory_.GetWeakPtr(), damage_rect));
    }
  }

  void OnCopyFrameCaptureSuccess(const gfx::Rect& damage_rect,
                                 std::shared_ptr<SkBitmap> bitmap) {
    view_->OnPaint(damage_rect, bitmap->width(), bitmap->height(),
                   bitmap->getPixels());
  }

  CefRenderWidgetHostViewOSR* view_;
  int frame_retry_count_;
  base::TimeTicks next_frame_time_;
  base::TimeDelta frame_duration_;

  base::WeakPtrFactory<CefCopyFrameGenerator> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(CefCopyFrameGenerator);
};

// Used to control the VSync rate in subprocesses when BeginFrame scheduling is
// enabled.
class CefBeginFrameTimer : public viz::DelayBasedTimeSourceClient {
 public:
  CefBeginFrameTimer(int frame_rate_threshold_us, const base::Closure& callback)
      : callback_(callback) {
    time_source_.reset(new viz::DelayBasedTimeSource(
        content::BrowserThread::GetTaskRunnerForThread(CEF_UIT).get()));
    time_source_->SetTimebaseAndInterval(
        base::TimeTicks(),
        base::TimeDelta::FromMicroseconds(frame_rate_threshold_us));
    time_source_->SetClient(this);
  }

  void SetActive(bool active) { time_source_->SetActive(active); }

  bool IsActive() const { return time_source_->Active(); }

  void SetFrameRateThresholdUs(int frame_rate_threshold_us) {
    time_source_->SetTimebaseAndInterval(
        base::TimeTicks::Now(),
        base::TimeDelta::FromMicroseconds(frame_rate_threshold_us));
  }

 private:
  // cc::TimerSourceClient implementation.
  void OnTimerTick() override { callback_.Run(); }

  const base::Closure callback_;
  std::unique_ptr<viz::DelayBasedTimeSource> time_source_;

  DISALLOW_COPY_AND_ASSIGN(CefBeginFrameTimer);
};

CefRenderWidgetHostViewOSR::CefRenderWidgetHostViewOSR(
    SkColor background_color,
    content::RenderWidgetHost* widget,
    CefRenderWidgetHostViewOSR* parent_host_view,
    bool is_guest_view_hack)
    : background_color_(background_color),
      frame_rate_threshold_us_(0),
#if !defined(OS_MACOSX)
      compositor_widget_(gfx::kNullAcceleratedWidget),
#endif
      software_output_device_(NULL),
      hold_resize_(false),
      pending_resize_(false),
      render_widget_host_(content::RenderWidgetHostImpl::From(widget)),
      has_parent_(parent_host_view != NULL),
      parent_host_view_(parent_host_view),
      popup_host_view_(NULL),
      child_host_view_(NULL),
      is_showing_(!render_widget_host_->is_hidden()),
      is_destroyed_(false),
      is_scroll_offset_changed_pending_(false),
      weak_ptr_factory_(this) {
  DCHECK(render_widget_host_);
  DCHECK(!render_widget_host_->GetView());

  current_device_scale_factor_ = kDefaultScaleFactor;

  if (parent_host_view_) {
    browser_impl_ = parent_host_view_->browser_impl();
    DCHECK(browser_impl_);
  } else if (content::RenderViewHost::From(render_widget_host_)) {
    // CefBrowserHostImpl might not be created at this time for popups.
    browser_impl_ = CefBrowserHostImpl::GetBrowserForHost(
        content::RenderViewHost::From(render_widget_host_));
  }

  local_surface_id_ = local_surface_id_allocator_.GenerateId();

#if !defined(OS_MACOSX)
  delegated_frame_host_ = base::MakeUnique<content::DelegatedFrameHost>(
      AllocateFrameSinkId(is_guest_view_hack), this,
      false /* enable_surface_synchronization */, false /* enable_viz */);

  root_layer_.reset(new ui::Layer(ui::LAYER_SOLID_COLOR));
#endif

  PlatformCreateCompositorWidget(is_guest_view_hack);

  bool opaque = SkColorGetA(background_color_) == SK_AlphaOPAQUE;
  GetRootLayer()->SetFillsBoundsOpaquely(opaque);
  GetRootLayer()->SetColor(background_color_);

#if !defined(OS_MACOSX)
  // On macOS the ui::Compositor is created/owned by the platform view.
  content::ImageTransportFactory* factory =
      content::ImageTransportFactory::GetInstance();
  ui::ContextFactoryPrivate* context_factory_private =
      factory->GetContextFactoryPrivate();
  compositor_.reset(
      new ui::Compositor(context_factory_private->AllocateFrameSinkId(),
                         content::GetContextFactory(), context_factory_private,
                         base::ThreadTaskRunnerHandle::Get(),
                         false /* enable_surface_synchronization */,
                         false /* enable_pixel_canvas */));
  compositor_->SetAcceleratedWidget(compositor_widget_);
  compositor_->SetDelegate(this);
  compositor_->SetRootLayer(root_layer_.get());
#endif

  if (browser_impl_.get())
    ResizeRootLayer();

  // Do this last because it may result in a call to SetNeedsBeginFrames.
  render_widget_host_->SetView(this);
}

CefRenderWidgetHostViewOSR::~CefRenderWidgetHostViewOSR() {
#if defined(OS_MACOSX)
  if (is_showing_)
    browser_compositor_->SetRenderWidgetHostIsHidden(true);
#else
  // Marking the DelegatedFrameHost as removed from the window hierarchy is
  // necessary to remove all connections to its old ui::Compositor.
  if (is_showing_)
    delegated_frame_host_->WasHidden();
  delegated_frame_host_->ResetCompositor();
#endif

  PlatformDestroyCompositorWidget();

  if (copy_frame_generator_.get())
    copy_frame_generator_.reset(NULL);

#if !defined(OS_MACOSX)
  delegated_frame_host_.reset(NULL);
  compositor_.reset(NULL);
  root_layer_.reset(NULL);
#endif

  DCHECK(parent_host_view_ == NULL);
  DCHECK(popup_host_view_ == NULL);
  DCHECK(child_host_view_ == NULL);
  DCHECK(guest_host_views_.empty());
}

// Called for full-screen widgets.
void CefRenderWidgetHostViewOSR::InitAsChild(gfx::NativeView parent_view) {
  DCHECK(parent_host_view_);
  DCHECK(browser_impl_);

  if (parent_host_view_->child_host_view_) {
    // Cancel the previous popup widget.
    parent_host_view_->child_host_view_->CancelWidget();
  }

  parent_host_view_->set_child_host_view(this);

  // The parent view should not render while the full-screen view exists.
  parent_host_view_->Hide();

  ResizeRootLayer();
  Show();
}

void CefRenderWidgetHostViewOSR::SetSize(const gfx::Size& size) {}

void CefRenderWidgetHostViewOSR::SetBounds(const gfx::Rect& rect) {}

gfx::Vector2dF CefRenderWidgetHostViewOSR::GetLastScrollOffset() const {
  return last_scroll_offset_;
}

gfx::NativeView CefRenderWidgetHostViewOSR::GetNativeView() const {
  return gfx::NativeView();
}

gfx::NativeViewAccessible
CefRenderWidgetHostViewOSR::GetNativeViewAccessible() {
  return gfx::NativeViewAccessible();
}

void CefRenderWidgetHostViewOSR::Focus() {}

bool CefRenderWidgetHostViewOSR::HasFocus() const {
  return false;
}

bool CefRenderWidgetHostViewOSR::IsSurfaceAvailableForCopy() const {
  return GetDelegatedFrameHost()->CanCopyFromCompositingSurface();
}

void CefRenderWidgetHostViewOSR::Show() {
  if (is_showing_)
    return;

  is_showing_ = true;

#if defined(OS_MACOSX)
  browser_compositor_->SetRenderWidgetHostIsHidden(false);
#else
  delegated_frame_host_->SetCompositor(compositor_.get());
  delegated_frame_host_->WasShown(ui::LatencyInfo());
#endif

  if (render_widget_host_)
    render_widget_host_->WasShown(ui::LatencyInfo());
}

void CefRenderWidgetHostViewOSR::Hide() {
  if (!is_showing_)
    return;

  if (browser_impl_.get())
    browser_impl_->CancelContextMenu();

  if (render_widget_host_)
    render_widget_host_->WasHidden();

#if defined(OS_MACOSX)
  browser_compositor_->SetRenderWidgetHostIsHidden(true);
#else
  GetDelegatedFrameHost()->WasHidden();
  GetDelegatedFrameHost()->ResetCompositor();
#endif

  is_showing_ = false;
}

bool CefRenderWidgetHostViewOSR::IsShowing() {
  return is_showing_;
}

gfx::Rect CefRenderWidgetHostViewOSR::GetViewBounds() const {
  if (IsPopupWidget())
    return popup_position_;

  if (!browser_impl_.get())
    return gfx::Rect();

  CefRect rc;
  CefRefPtr<CefRenderHandler> handler =
      browser_impl_->GetClient()->GetRenderHandler();
  if (handler.get())
    handler->GetViewRect(browser_impl_.get(), rc);
  return gfx::Rect(rc.x, rc.y, rc.width, rc.height);
}

void CefRenderWidgetHostViewOSR::SetBackgroundColor(SkColor color) {
  // The renderer will feed its color back to us with the first CompositorFrame.
  // We short-cut here to show a sensible color before that happens.
  UpdateBackgroundColorFromRenderer(color);

  DCHECK(SkColorGetA(color) == SK_AlphaOPAQUE ||
         SkColorGetA(color) == SK_AlphaTRANSPARENT);
  if (render_widget_host_) {
    render_widget_host_->SetBackgroundOpaque(SkColorGetA(color) ==
                                             SK_AlphaOPAQUE);
  }
}

SkColor CefRenderWidgetHostViewOSR::background_color() const {
  return background_color_;
}

bool CefRenderWidgetHostViewOSR::LockMouse() {
  return false;
}

void CefRenderWidgetHostViewOSR::UnlockMouse() {}

void CefRenderWidgetHostViewOSR::DidCreateNewRendererCompositorFrameSink(
    viz::mojom::CompositorFrameSinkClient* renderer_compositor_frame_sink) {
  renderer_compositor_frame_sink_ = renderer_compositor_frame_sink;
  if (GetDelegatedFrameHost()) {
    GetDelegatedFrameHost()->DidCreateNewRendererCompositorFrameSink(
        renderer_compositor_frame_sink_);
  }
}

void CefRenderWidgetHostViewOSR::SubmitCompositorFrame(
    const viz::LocalSurfaceId& local_surface_id,
    viz::CompositorFrame frame,
    viz::mojom::HitTestRegionListPtr hit_test_region_list) {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::OnSwapCompositorFrame");

  if (frame.metadata.root_scroll_offset != last_scroll_offset_) {
    last_scroll_offset_ = frame.metadata.root_scroll_offset;

    if (!is_scroll_offset_changed_pending_) {
      // Send the notification asnychronously.
      CEF_POST_TASK(
          CEF_UIT,
          base::Bind(&CefRenderWidgetHostViewOSR::OnScrollOffsetChanged,
                     weak_ptr_factory_.GetWeakPtr()));
    }
  }

  if (!frame.render_pass_list.empty()) {
    if (software_output_device_) {
      if (!begin_frame_timer_.get()) {
        // If BeginFrame scheduling is enabled SoftwareOutputDevice activity
        // will be controlled via OnSetNeedsBeginFrames. Otherwise, activate
        // the SoftwareOutputDevice now (when the first frame is generated).
        software_output_device_->SetActive(true);
      }

      // The compositor will draw directly to the SoftwareOutputDevice which
      // then calls OnPaint.
      // We would normally call BrowserCompositorMac::SubmitCompositorFrame on
      // macOS, however it contains compositor resize logic that we don't want.
      // Consequently we instead call the SwapDelegatedFrame method directly.
      GetDelegatedFrameHost()->SubmitCompositorFrame(
          local_surface_id, std::move(frame), std::move(hit_test_region_list));
    } else {
      if (!copy_frame_generator_.get()) {
        copy_frame_generator_.reset(
            new CefCopyFrameGenerator(frame_rate_threshold_us_, this));
      }

      // Determine the damage rectangle for the current frame. This is the same
      // calculation that SwapDelegatedFrame uses.
      viz::RenderPass* root_pass = frame.render_pass_list.back().get();
      gfx::Size frame_size = root_pass->output_rect.size();
      gfx::Rect damage_rect =
          gfx::ToEnclosingRect(gfx::RectF(root_pass->damage_rect));
      damage_rect.Intersect(gfx::Rect(frame_size));

      // We would normally call BrowserCompositorMac::SubmitCompositorFrame on
      // macOS, however it contains compositor resize logic that we don't want.
      // Consequently we instead call the SwapDelegatedFrame method directly.
      GetDelegatedFrameHost()->SubmitCompositorFrame(
          local_surface_id, std::move(frame), std::move(hit_test_region_list));

      // Request a copy of the last compositor frame which will eventually call
      // OnPaint asynchronously.
      copy_frame_generator_->GenerateCopyFrame(damage_rect);
    }

    return;
  }
}

void CefRenderWidgetHostViewOSR::ClearCompositorFrame() {
  GetDelegatedFrameHost()->ClearDelegatedFrame();
}

void CefRenderWidgetHostViewOSR::InitAsPopup(
    content::RenderWidgetHostView* parent_host_view,
    const gfx::Rect& pos) {
  DCHECK_EQ(parent_host_view_, parent_host_view);
  DCHECK(browser_impl_);

  if (parent_host_view_->popup_host_view_) {
    // Cancel the previous popup widget.
    parent_host_view_->popup_host_view_->CancelWidget();
  }

  parent_host_view_->set_popup_host_view(this);

  CefRefPtr<CefRenderHandler> handler =
      browser_impl_->GetClient()->GetRenderHandler();
  if (handler.get())
    handler->OnPopupShow(browser_impl_.get(), true);

  popup_position_ = pos;

  CefRect widget_pos(pos.x(), pos.y(), pos.width(), pos.height());
  if (handler.get())
    handler->OnPopupSize(browser_impl_.get(), widget_pos);

  ResizeRootLayer();
  Show();
}

void CefRenderWidgetHostViewOSR::InitAsFullscreen(
    content::RenderWidgetHostView* reference_host_view) {
  NOTREACHED() << "Fullscreen widgets are not supported in OSR";
}

// Called for the "platform view" created by WebContentsViewGuest and owned by
// RenderWidgetHostViewGuest.
void CefRenderWidgetHostViewOSR::InitAsGuest(
    content::RenderWidgetHostView* parent_host_view,
    content::RenderWidgetHostViewGuest* guest_view) {
  DCHECK_EQ(parent_host_view_, parent_host_view);
  DCHECK(browser_impl_);

  parent_host_view_->AddGuestHostView(this);
  parent_host_view_->RegisterGuestViewFrameSwappedCallback(guest_view);
}

void CefRenderWidgetHostViewOSR::UpdateCursor(
    const content::WebCursor& cursor) {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::UpdateCursor");
  if (!browser_impl_.get())
    return;

  CefRefPtr<CefRenderHandler> handler =
      browser_impl_->GetClient()->GetRenderHandler();
  if (!handler.get())
    return;

  content::CursorInfo cursor_info;
  cursor.GetCursorInfo(&cursor_info);

  const cef_cursor_type_t cursor_type =
      static_cast<cef_cursor_type_t>(cursor_info.type);
  CefCursorInfo custom_cursor_info;
  if (cursor.IsCustom()) {
    custom_cursor_info.hotspot.x = cursor_info.hotspot.x();
    custom_cursor_info.hotspot.y = cursor_info.hotspot.y();
    custom_cursor_info.image_scale_factor = cursor_info.image_scale_factor;
    custom_cursor_info.buffer = cursor_info.custom_image.getPixels();
    custom_cursor_info.size.width = cursor_info.custom_image.width();
    custom_cursor_info.size.height = cursor_info.custom_image.height();
  }

#if defined(USE_AURA)
  content::WebCursor web_cursor = cursor;

  ui::PlatformCursor platform_cursor;
  if (web_cursor.IsCustom()) {
    // |web_cursor| owns the resulting |platform_cursor|.
    platform_cursor = web_cursor.GetPlatformCursor();
  } else {
    platform_cursor = GetPlatformCursor(cursor_info.type);
  }

  handler->OnCursorChange(browser_impl_.get(), platform_cursor, cursor_type,
                          custom_cursor_info);
#elif defined(OS_MACOSX)
  // |web_cursor| owns the resulting |native_cursor|.
  content::WebCursor web_cursor = cursor;
  CefCursorHandle native_cursor = web_cursor.GetNativeCursor();
  handler->OnCursorChange(browser_impl_.get(), native_cursor, cursor_type,
                          custom_cursor_info);
#else
  // TODO(port): Implement this method to work on other platforms as part of
  // off-screen rendering support.
  NOTREACHED();
#endif
}

void CefRenderWidgetHostViewOSR::SetIsLoading(bool is_loading) {}

void CefRenderWidgetHostViewOSR::RenderProcessGone(
    base::TerminationStatus status,
    int error_code) {
  Destroy();
}

void CefRenderWidgetHostViewOSR::Destroy() {
  if (!is_destroyed_) {
    is_destroyed_ = true;

    if (has_parent_) {
      CancelWidget();
    } else {
      if (popup_host_view_)
        popup_host_view_->CancelWidget();
      if (child_host_view_)
        child_host_view_->CancelWidget();
      if (!guest_host_views_.empty()) {
        // Guest RWHVs will be destroyed when the associated RWHVGuest is
        // destroyed. This parent RWHV may be destroyed first, so disassociate
        // the guest RWHVs here without destroying them.
        for (auto guest_host_view : guest_host_views_)
          guest_host_view->parent_host_view_ = nullptr;
        guest_host_views_.clear();
      }
      Hide();
    }
  }

  delete this;
}

void CefRenderWidgetHostViewOSR::SetTooltipText(
    const base::string16& tooltip_text) {
  if (!browser_impl_.get())
    return;

  CefString tooltip(tooltip_text);
  CefRefPtr<CefDisplayHandler> handler =
      browser_impl_->GetClient()->GetDisplayHandler();
  if (handler.get()) {
    handler->OnTooltip(browser_impl_.get(), tooltip);
  }
}

gfx::Size CefRenderWidgetHostViewOSR::GetRequestedRendererSize() const {
  return GetDelegatedFrameHost()->GetRequestedRendererSize();
}

gfx::Size CefRenderWidgetHostViewOSR::GetPhysicalBackingSize() const {
  return gfx::ScaleToCeiledSize(GetRequestedRendererSize(),
                                current_device_scale_factor_);
}

void CefRenderWidgetHostViewOSR::CopyFromSurface(
    const gfx::Rect& src_subrect,
    const gfx::Size& dst_size,
    const content::ReadbackRequestCallback& callback,
    const SkColorType color_type) {
  GetDelegatedFrameHost()->CopyFromCompositingSurface(src_subrect, dst_size,
                                                      callback, color_type);
}

void CefRenderWidgetHostViewOSR::CopyFromSurfaceToVideoFrame(
    const gfx::Rect& src_subrect,
    scoped_refptr<media::VideoFrame> target,
    const base::Callback<void(const gfx::Rect&, bool)>& callback) {
  GetDelegatedFrameHost()->CopyFromCompositingSurfaceToVideoFrame(
      src_subrect, target, callback);
}

void CefRenderWidgetHostViewOSR::BeginFrameSubscription(
    std::unique_ptr<content::RenderWidgetHostViewFrameSubscriber> subscriber) {
  GetDelegatedFrameHost()->BeginFrameSubscription(std::move(subscriber));
}

void CefRenderWidgetHostViewOSR::EndFrameSubscription() {
  GetDelegatedFrameHost()->EndFrameSubscription();
}

bool CefRenderWidgetHostViewOSR::HasAcceleratedSurface(
    const gfx::Size& desired_size) {
  // CEF doesn't use GetBackingStore for accelerated pages, so it doesn't
  // matter what is returned here as GetBackingStore is the only caller of this
  // method.
  NOTREACHED();
  return false;
}

gfx::Rect CefRenderWidgetHostViewOSR::GetBoundsInRootWindow() {
  if (!browser_impl_.get())
    return gfx::Rect();

  CefRect rc;
  CefRefPtr<CefRenderHandler> handler =
      browser_impl_->client()->GetRenderHandler();
  if (handler.get() && handler->GetRootScreenRect(browser_impl_.get(), rc))
    return gfx::Rect(rc.x, rc.y, rc.width, rc.height);
  return GetViewBounds();
}

content::RenderWidgetHostImpl*
CefRenderWidgetHostViewOSR::GetRenderWidgetHostImpl() const {
  return render_widget_host_;
}

viz::SurfaceId CefRenderWidgetHostViewOSR::GetCurrentSurfaceId() const {
  return GetDelegatedFrameHost()
             ? GetDelegatedFrameHost()->GetCurrentSurfaceId()
             : viz::SurfaceId();
}

content::BrowserAccessibilityManager*
CefRenderWidgetHostViewOSR::CreateBrowserAccessibilityManager(
    content::BrowserAccessibilityDelegate* delegate,
    bool for_root_frame) {
  return NULL;
}

#if defined(TOOLKIT_VIEWS) || defined(USE_AURA)
void CefRenderWidgetHostViewOSR::ShowDisambiguationPopup(
    const gfx::Rect& rect_pixels,
    const SkBitmap& zoomed_bitmap) {}
#endif

void CefRenderWidgetHostViewOSR::ImeSetComposition(
    const CefString& text,
    const std::vector<CefCompositionUnderline>& underlines,
    const CefRange& replacement_range,
    const CefRange& selection_range) {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::ImeSetComposition");
  if (!render_widget_host_)
    return;

  std::vector<ui::ImeTextSpan> web_underlines;
  web_underlines.reserve(underlines.size());
  for (const CefCompositionUnderline& line : underlines) {
    web_underlines.push_back(ui::ImeTextSpan(
        ui::ImeTextSpan::Type::kComposition, line.range.from, line.range.to,
        line.color, line.thick ? true : false, line.background_color));
  }
  gfx::Range range(replacement_range.from, replacement_range.to);

  // Start Monitoring for composition updates before we set.
  RequestImeCompositionUpdate(true);

  render_widget_host_->ImeSetComposition(
      text, web_underlines, range, selection_range.from, selection_range.to);
}

void CefRenderWidgetHostViewOSR::ImeCommitText(
    const CefString& text,
    const CefRange& replacement_range,
    int relative_cursor_pos) {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::ImeCommitText");
  if (!render_widget_host_)
    return;

  gfx::Range range(replacement_range.from, replacement_range.to);
  render_widget_host_->ImeCommitText(text, std::vector<ui::ImeTextSpan>(),
                                     range, relative_cursor_pos);

  // Stop Monitoring for composition updates after we are done.
  RequestImeCompositionUpdate(false);
}

void CefRenderWidgetHostViewOSR::ImeFinishComposingText(bool keep_selection) {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::ImeFinishComposingText");
  if (!render_widget_host_)
    return;

  render_widget_host_->ImeFinishComposingText(keep_selection);

  // Stop Monitoring for composition updates after we are done.
  RequestImeCompositionUpdate(false);
}

void CefRenderWidgetHostViewOSR::ImeCancelComposition() {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::ImeCancelComposition");
  if (!render_widget_host_)
    return;

  render_widget_host_->ImeCancelComposition();

  // Stop Monitoring for composition updates after we are done.
  RequestImeCompositionUpdate(false);
}

void CefRenderWidgetHostViewOSR::SetNeedsBeginFrames(bool enabled) {
  SetFrameRate();

  // Start/stop the timer that sends BeginFrame requests.
  begin_frame_timer_->SetActive(enabled);
  if (software_output_device_) {
    // When the SoftwareOutputDevice is active it will call OnPaint for each
    // frame. If the SoftwareOutputDevice is deactivated while an invalidation
    // region is pending it will call OnPaint immediately.
    software_output_device_->SetActive(enabled);
  }
}

void CefRenderWidgetHostViewOSR::SetWantsAnimateOnlyBeginFrames() {
  if (GetDelegatedFrameHost()) {
    GetDelegatedFrameHost()->SetWantsAnimateOnlyBeginFrames();
  }
}

bool CefRenderWidgetHostViewOSR::TransformPointToLocalCoordSpace(
    const gfx::PointF& point,
    const viz::SurfaceId& original_surface,
    gfx::PointF* transformed_point) {
  // Transformations use physical pixels rather than DIP, so conversion
  // is necessary.
  gfx::PointF point_in_pixels =
      gfx::ConvertPointToPixel(current_device_scale_factor_, point);
  if (!GetDelegatedFrameHost()->TransformPointToLocalCoordSpace(
          point_in_pixels, original_surface, transformed_point)) {
    return false;
  }

  *transformed_point =
      gfx::ConvertPointToDIP(current_device_scale_factor_, *transformed_point);
  return true;
}

bool CefRenderWidgetHostViewOSR::TransformPointToCoordSpaceForView(
    const gfx::PointF& point,
    RenderWidgetHostViewBase* target_view,
    gfx::PointF* transformed_point) {
  if (target_view == this) {
    *transformed_point = point;
    return true;
  }

  // In TransformPointToLocalCoordSpace() there is a Point-to-Pixel conversion,
  // but it is not necessary here because the final target view is responsible
  // for converting before computing the final transform.
  return GetDelegatedFrameHost()->TransformPointToCoordSpaceForView(
      point, target_view, transformed_point);
}

std::unique_ptr<viz::SoftwareOutputDevice>
CefRenderWidgetHostViewOSR::CreateSoftwareOutputDevice(
    ui::Compositor* compositor) {
  DCHECK_EQ(GetCompositor(), compositor);
  DCHECK(!copy_frame_generator_);
  DCHECK(!software_output_device_);
  software_output_device_ = new CefSoftwareOutputDeviceOSR(
      compositor, background_color() == SK_ColorTRANSPARENT,
      base::Bind(&CefRenderWidgetHostViewOSR::OnPaint,
                 weak_ptr_factory_.GetWeakPtr()));
  return base::WrapUnique(software_output_device_);
}

#if !defined(OS_MACOSX)

ui::Layer* CefRenderWidgetHostViewOSR::DelegatedFrameHostGetLayer() const {
  return GetRootLayer();
}

bool CefRenderWidgetHostViewOSR::DelegatedFrameHostIsVisible() const {
  return !render_widget_host_->is_hidden();
}

SkColor CefRenderWidgetHostViewOSR::DelegatedFrameHostGetGutterColor() const {
  // When making an element on the page fullscreen the element's background
  // may not match the page's, so use black as the gutter color to avoid
  // flashes of brighter colors during the transition.
  if (render_widget_host_->delegate() &&
      render_widget_host_->delegate()->IsFullscreenForCurrentTab()) {
    return SK_ColorBLACK;
  }
  return background_color_;
}

gfx::Size CefRenderWidgetHostViewOSR::DelegatedFrameHostDesiredSizeInDIP()
    const {
  return GetRootLayer()->bounds().size();
}

bool CefRenderWidgetHostViewOSR::DelegatedFrameCanCreateResizeLock() const {
  return !render_widget_host_->auto_resize_enabled();
}

std::unique_ptr<content::CompositorResizeLock>
CefRenderWidgetHostViewOSR::DelegatedFrameHostCreateResizeLock() {
  HoldResize();

  const gfx::Size& desired_size = GetRootLayer()->bounds().size();
  return base::MakeUnique<content::CompositorResizeLock>(this, desired_size);
}

viz::LocalSurfaceId CefRenderWidgetHostViewOSR::GetLocalSurfaceId() const {
  return local_surface_id_;
}

void CefRenderWidgetHostViewOSR::OnBeginFrame(base::TimeTicks frame_time) {
  // TODO(cef): Maybe we can use this method in combination with
  // OnSetNeedsBeginFrames() instead of using CefBeginFrameTimer.
  // See https://codereview.chromium.org/1841083007.
}

bool CefRenderWidgetHostViewOSR::IsAutoResizeEnabled() const {
  return render_widget_host_->auto_resize_enabled();
}

void CefRenderWidgetHostViewOSR::OnFrameTokenChanged(uint32_t frame_token) {
  render_widget_host_->DidProcessFrame(frame_token);
}

std::unique_ptr<ui::CompositorLock>
CefRenderWidgetHostViewOSR::GetCompositorLock(
    ui::CompositorLockClient* client) {
  return GetCompositor()->GetCompositorLock(client);
}

void CefRenderWidgetHostViewOSR::CompositorResizeLockEnded() {
  ReleaseResize();
}

#endif  // !defined(OS_MACOSX)

bool CefRenderWidgetHostViewOSR::InstallTransparency() {
  if (background_color() == SK_ColorTRANSPARENT) {
    SetBackgroundColor(background_color());
#if defined(OS_MACOSX)
    browser_compositor_->SetBackgroundColor(background_color());
#else
    compositor_->SetBackgroundColor(background_color());
#endif
    return true;
  }
  return false;
}

void CefRenderWidgetHostViewOSR::WasResized() {
  if (hold_resize_) {
    if (!pending_resize_)
      pending_resize_ = true;
    return;
  }

  ResizeRootLayer();
  if (render_widget_host_)
    render_widget_host_->WasResized();
  GetDelegatedFrameHost()->WasResized();
}

void CefRenderWidgetHostViewOSR::GetScreenInfo(content::ScreenInfo* results) {
  if (!browser_impl_.get())
    return;

  CefScreenInfo screen_info(kDefaultScaleFactor, 0, 0, false, CefRect(),
                            CefRect());

  CefRefPtr<CefRenderHandler> handler =
      browser_impl_->client()->GetRenderHandler();
  if (handler.get() &&
      (!handler->GetScreenInfo(browser_impl_.get(), screen_info) ||
       screen_info.rect.width == 0 || screen_info.rect.height == 0 ||
       screen_info.available_rect.width == 0 ||
       screen_info.available_rect.height == 0)) {
    // If a screen rectangle was not provided, try using the view rectangle
    // instead. Otherwise, popup views may be drawn incorrectly, or not at all.
    CefRect screenRect;
    if (!handler->GetViewRect(browser_impl_.get(), screenRect)) {
      NOTREACHED();
      screenRect = CefRect();
    }

    if (screen_info.rect.width == 0 && screen_info.rect.height == 0)
      screen_info.rect = screenRect;

    if (screen_info.available_rect.width == 0 &&
        screen_info.available_rect.height == 0)
      screen_info.available_rect = screenRect;
  }

  *results = ScreenInfoFrom(screen_info);
}

void CefRenderWidgetHostViewOSR::OnScreenInfoChanged() {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::OnScreenInfoChanged");
  if (!render_widget_host_)
    return;

  // TODO(OSR): Update the backing store.

  render_widget_host_->NotifyScreenInfoChanged();
  // We might want to change the cursor scale factor here as well - see the
  // cache for the current_cursor_, as passed by UpdateCursor from the renderer
  // in the rwhv_aura (current_cursor_.SetScaleFactor)

  // Notify the guest hosts if any.
  for (auto guest_host_view : guest_host_views_)
    guest_host_view->OnScreenInfoChanged();
}

void CefRenderWidgetHostViewOSR::Invalidate(
    CefBrowserHost::PaintElementType type) {
  TRACE_EVENT1("libcef", "CefRenderWidgetHostViewOSR::Invalidate", "type",
               type);
  if (!IsPopupWidget() && type == PET_POPUP) {
    if (popup_host_view_)
      popup_host_view_->Invalidate(type);
    return;
  }

  InvalidateInternal(gfx::Rect(GetPhysicalBackingSize()));
}

void CefRenderWidgetHostViewOSR::SendKeyEvent(
    const content::NativeWebKeyboardEvent& event) {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::SendKeyEvent");
  if (render_widget_host_ && render_widget_host_->GetView()) {
    // Direct routing requires that events go directly to the View.
    render_widget_host_->ForwardKeyboardEventWithLatencyInfo(
        event, ui::LatencyInfo(event.GetType() == blink::WebInputEvent::kChar ||
                                       event.GetType() ==
                                           blink::WebInputEvent::kRawKeyDown
                                   ? ui::SourceEventType::KEY_PRESS
                                   : ui::SourceEventType::OTHER));
  }
}

void CefRenderWidgetHostViewOSR::SendMouseEvent(
    const blink::WebMouseEvent& event) {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::SendMouseEvent");
  if (!IsPopupWidget()) {
    if (browser_impl_.get() &&
        event.GetType() == blink::WebMouseEvent::kMouseDown) {
      browser_impl_->CancelContextMenu();
    }

    if (popup_host_view_) {
      if (popup_host_view_->popup_position_.Contains(
              event.PositionInWidget().x, event.PositionInWidget().y)) {
        blink::WebMouseEvent popup_event(event);
        popup_event.SetPositionInWidget(
            event.PositionInWidget().x - popup_host_view_->popup_position_.x(),
            event.PositionInWidget().y - popup_host_view_->popup_position_.y());
        popup_event.SetPositionInScreen(popup_event.PositionInWidget().x,
                                        popup_event.PositionInWidget().y);

        popup_host_view_->SendMouseEvent(popup_event);
        return;
      }
    } else if (!guest_host_views_.empty()) {
      for (auto guest_host_view : guest_host_views_) {
        if (!guest_host_view->render_widget_host_ ||
            !guest_host_view->render_widget_host_->GetView()) {
          continue;
        }
        const gfx::Rect& guest_bounds =
            guest_host_view->render_widget_host_->GetView()->GetViewBounds();
        if (guest_bounds.Contains(event.PositionInWidget().x,
                                  event.PositionInWidget().y)) {
          blink::WebMouseEvent guest_event(event);
          guest_event.SetPositionInWidget(
              event.PositionInWidget().x - guest_bounds.x(),
              event.PositionInWidget().y - guest_bounds.y());
          guest_event.SetPositionInScreen(guest_event.PositionInWidget().x,
                                          guest_event.PositionInWidget().y);

          guest_host_view->SendMouseEvent(guest_event);
          return;
        }
      }
    }
  }

  if (render_widget_host_ && render_widget_host_->GetView()) {
    // Direct routing requires that mouse events go directly to the View.
    render_widget_host_->GetView()->ProcessMouseEvent(
        event, ui::LatencyInfo(ui::SourceEventType::OTHER));
  }
}

void CefRenderWidgetHostViewOSR::SendMouseWheelEvent(
    const blink::WebMouseWheelEvent& event) {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::SendMouseWheelEvent");
  if (!IsPopupWidget()) {
    if (browser_impl_.get())
      browser_impl_->CancelContextMenu();

    if (popup_host_view_) {
      if (popup_host_view_->popup_position_.Contains(
              event.PositionInWidget().x, event.PositionInWidget().y)) {
        blink::WebMouseWheelEvent popup_event(event);
        popup_event.SetPositionInWidget(
            event.PositionInWidget().x - popup_host_view_->popup_position_.x(),
            event.PositionInWidget().y - popup_host_view_->popup_position_.y());
        popup_event.SetPositionInScreen(popup_event.PositionInWidget().x,
                                        popup_event.PositionInWidget().y);

        popup_host_view_->SendMouseWheelEvent(popup_event);
        return;
      } else {
        // Scrolling outside of the popup widget so destroy it.
        // Execute asynchronously to avoid deleting the widget from inside some
        // other callback.
        CEF_POST_TASK(
            CEF_UIT,
            base::Bind(&CefRenderWidgetHostViewOSR::CancelWidget,
                       popup_host_view_->weak_ptr_factory_.GetWeakPtr()));
      }
    } else if (!guest_host_views_.empty()) {
      for (auto guest_host_view : guest_host_views_) {
        if (!guest_host_view->render_widget_host_ ||
            !guest_host_view->render_widget_host_->GetView()) {
          continue;
        }
        const gfx::Rect& guest_bounds =
            guest_host_view->render_widget_host_->GetView()->GetViewBounds();
        if (guest_bounds.Contains(event.PositionInWidget().x,
                                  event.PositionInWidget().y)) {
          blink::WebMouseWheelEvent guest_event(event);
          guest_event.SetPositionInWidget(
              event.PositionInWidget().x - guest_bounds.x(),
              event.PositionInWidget().y - guest_bounds.y());
          guest_event.SetPositionInScreen(guest_event.PositionInWidget().x,
                                          guest_event.PositionInWidget().y);

          guest_host_view->SendMouseWheelEvent(guest_event);
          return;
        }
      }
    }
  }

  if (render_widget_host_ && render_widget_host_->GetView()) {
    // Direct routing requires that mouse events go directly to the View.
    render_widget_host_->GetView()->ProcessMouseWheelEvent(
        event, ui::LatencyInfo(ui::SourceEventType::WHEEL));
  }
}

void CefRenderWidgetHostViewOSR::SendFocusEvent(bool focus) {
  if (!render_widget_host_)
    return;

  content::RenderWidgetHostImpl* widget =
      content::RenderWidgetHostImpl::From(render_widget_host_);
  if (focus) {
    widget->GotFocus();
    widget->SetActive(true);
  } else {
    if (browser_impl_.get())
      browser_impl_->CancelContextMenu();

    widget->SetActive(false);
    widget->LostFocus();
  }
}

void CefRenderWidgetHostViewOSR::UpdateFrameRate() {
  frame_rate_threshold_us_ = 0;
  SetFrameRate();

  // Notify the guest hosts if any.
  for (auto guest_host_view : guest_host_views_)
    guest_host_view->UpdateFrameRate();
}

void CefRenderWidgetHostViewOSR::HoldResize() {
  if (!hold_resize_)
    hold_resize_ = true;
}

void CefRenderWidgetHostViewOSR::ReleaseResize() {
  if (!hold_resize_)
    return;

  hold_resize_ = false;
  if (pending_resize_) {
    pending_resize_ = false;
    CEF_POST_TASK(CEF_UIT, base::Bind(&CefRenderWidgetHostViewOSR::WasResized,
                                      weak_ptr_factory_.GetWeakPtr()));
  }
}

void CefRenderWidgetHostViewOSR::OnPaint(const gfx::Rect& damage_rect,
                                         int bitmap_width,
                                         int bitmap_height,
                                         void* bitmap_pixels) {
  TRACE_EVENT0("libcef", "CefRenderWidgetHostViewOSR::OnPaint");

  CefRefPtr<CefRenderHandler> handler =
      browser_impl_->client()->GetRenderHandler();
  if (!handler.get())
    return;

  // Don't execute WasResized while the OnPaint callback is pending.
  HoldResize();

  gfx::Rect rect_in_bitmap(0, 0, bitmap_width, bitmap_height);
  rect_in_bitmap.Intersect(damage_rect);

  CefRenderHandler::RectList rcList;
  rcList.push_back(CefRect(rect_in_bitmap.x(), rect_in_bitmap.y(),
                           rect_in_bitmap.width(), rect_in_bitmap.height()));

  handler->OnPaint(browser_impl_.get(), IsPopupWidget() ? PET_POPUP : PET_VIEW,
                   rcList, bitmap_pixels, bitmap_width, bitmap_height);

  ReleaseResize();
}

#if !defined(OS_MACOSX)

ui::Compositor* CefRenderWidgetHostViewOSR::GetCompositor() const {
  return compositor_.get();
}

ui::Layer* CefRenderWidgetHostViewOSR::GetRootLayer() const {
  return root_layer_.get();
}

content::DelegatedFrameHost* CefRenderWidgetHostViewOSR::GetDelegatedFrameHost()
    const {
  return delegated_frame_host_.get();
}

#endif  // !defined(OS_MACOSX)

void CefRenderWidgetHostViewOSR::SetFrameRate() {
  CefRefPtr<CefBrowserHostImpl> browser;
  if (parent_host_view_) {
    // Use the same frame rate as the embedding browser.
    browser = parent_host_view_->browser_impl_;
  } else {
    browser = browser_impl_;
  }
  CHECK(browser);

  // Only set the frame rate one time.
  if (frame_rate_threshold_us_ != 0)
    return;

  const int frame_rate =
      osr_util::ClampFrameRate(browser->settings().windowless_frame_rate);
  frame_rate_threshold_us_ = 1000000 / frame_rate;

  // Configure the VSync interval for the browser process.
  GetCompositor()->vsync_manager()->SetAuthoritativeVSyncInterval(
      base::TimeDelta::FromMicroseconds(frame_rate_threshold_us_));

  if (copy_frame_generator_.get()) {
    copy_frame_generator_->set_frame_rate_threshold_us(
        frame_rate_threshold_us_);
  }

  if (begin_frame_timer_.get()) {
    begin_frame_timer_->SetFrameRateThresholdUs(frame_rate_threshold_us_);
  } else {
    begin_frame_timer_.reset(new CefBeginFrameTimer(
        frame_rate_threshold_us_,
        base::Bind(&CefRenderWidgetHostViewOSR::OnBeginFrameTimerTick,
                   weak_ptr_factory_.GetWeakPtr())));
  }
}

void CefRenderWidgetHostViewOSR::SetDeviceScaleFactor() {
  float new_scale_factor = kDefaultScaleFactor;

  if (browser_impl_.get()) {
    CefScreenInfo screen_info(kDefaultScaleFactor, 0, 0, false, CefRect(),
                              CefRect());
    CefRefPtr<CefRenderHandler> handler =
        browser_impl_->client()->GetRenderHandler();
    if (handler.get() &&
        handler->GetScreenInfo(browser_impl_.get(), screen_info)) {
      new_scale_factor = screen_info.device_scale_factor;
    }
  }

  current_device_scale_factor_ = new_scale_factor;

  // Notify the guest hosts if any.
  for (auto guest_host_view : guest_host_views_) {
    content::RenderWidgetHostImpl* rwhi = guest_host_view->render_widget_host();
    if (!rwhi)
      continue;
    if (rwhi->GetView())
      rwhi->GetView()->set_current_device_scale_factor(new_scale_factor);
  }
}

void CefRenderWidgetHostViewOSR::ResizeRootLayer() {
  SetFrameRate();

  const float orgScaleFactor = current_device_scale_factor_;
  SetDeviceScaleFactor();
  const bool scaleFactorDidChange =
      (orgScaleFactor != current_device_scale_factor_);

  gfx::Size size;
  if (!IsPopupWidget())
    size = GetViewBounds().size();
  else
    size = popup_position_.size();

  if (!scaleFactorDidChange && size == GetRootLayer()->bounds().size())
    return;

  const gfx::Size& size_in_pixels =
      gfx::ConvertSizeToPixel(current_device_scale_factor_, size);

  local_surface_id_ = local_surface_id_allocator_.GenerateId();

  GetRootLayer()->SetBounds(gfx::Rect(size));
  GetCompositor()->SetScaleAndSize(current_device_scale_factor_, size_in_pixels,
                                   local_surface_id_);
  PlatformResizeCompositorWidget(size_in_pixels);
}

void CefRenderWidgetHostViewOSR::OnBeginFrameTimerTick() {
  const base::TimeTicks frame_time = base::TimeTicks::Now();
  const base::TimeDelta vsync_period =
      base::TimeDelta::FromMicroseconds(frame_rate_threshold_us_);
  SendBeginFrame(frame_time, vsync_period);
}

void CefRenderWidgetHostViewOSR::SendBeginFrame(base::TimeTicks frame_time,
                                                base::TimeDelta vsync_period) {
  TRACE_EVENT1("libcef", "CefRenderWidgetHostViewOSR::SendBeginFrame",
               "frame_time_us", frame_time.ToInternalValue());

  base::TimeTicks display_time = frame_time + vsync_period;

  // TODO(brianderson): Use adaptive draw-time estimation.
  base::TimeDelta estimated_browser_composite_time =
      base::TimeDelta::FromMicroseconds(
          (1.0f * base::Time::kMicrosecondsPerSecond) / (3.0f * 60));

  base::TimeTicks deadline = display_time - estimated_browser_composite_time;

  const viz::BeginFrameArgs& begin_frame_args = viz::BeginFrameArgs::Create(
      BEGINFRAME_FROM_HERE, begin_frame_source_.source_id(),
      begin_frame_number_, frame_time, deadline, vsync_period,
      viz::BeginFrameArgs::NORMAL);
  DCHECK(begin_frame_args.IsValid());
  begin_frame_number_++;

  if (renderer_compositor_frame_sink_)
    renderer_compositor_frame_sink_->OnBeginFrame(begin_frame_args);
}

void CefRenderWidgetHostViewOSR::CancelWidget() {
  if (render_widget_host_)
    render_widget_host_->LostCapture();

  Hide();

  if (IsPopupWidget() && browser_impl_.get()) {
    CefRefPtr<CefRenderHandler> handler =
        browser_impl_->client()->GetRenderHandler();
    if (handler.get())
      handler->OnPopupShow(browser_impl_.get(), false);
    browser_impl_ = NULL;
  }

  if (parent_host_view_) {
    if (parent_host_view_->popup_host_view_ == this) {
      parent_host_view_->set_popup_host_view(NULL);
    } else if (parent_host_view_->child_host_view_ == this) {
      parent_host_view_->set_child_host_view(NULL);

      // Start rendering the parent view again.
      parent_host_view_->Show();
    } else {
      parent_host_view_->RemoveGuestHostView(this);
    }
    parent_host_view_ = NULL;
  }

  if (render_widget_host_ && !is_destroyed_) {
    is_destroyed_ = true;

    // Don't delete the RWHI manually while owned by a scoped_ptr in RVHI. This
    // matches a CHECK() in RenderWidgetHostImpl::Destroy().
    const bool also_delete = !render_widget_host_->owner_delegate();

    // Results in a call to Destroy().
    render_widget_host_->ShutdownAndDestroyWidget(also_delete);
  }
}

void CefRenderWidgetHostViewOSR::OnScrollOffsetChanged() {
  if (browser_impl_.get()) {
    CefRefPtr<CefRenderHandler> handler =
        browser_impl_->client()->GetRenderHandler();
    if (handler.get()) {
      handler->OnScrollOffsetChanged(browser_impl_.get(),
                                     last_scroll_offset_.x(),
                                     last_scroll_offset_.y());
    }
  }
  is_scroll_offset_changed_pending_ = false;
}

void CefRenderWidgetHostViewOSR::AddGuestHostView(
    CefRenderWidgetHostViewOSR* guest_host) {
  guest_host_views_.insert(guest_host);
}

void CefRenderWidgetHostViewOSR::RemoveGuestHostView(
    CefRenderWidgetHostViewOSR* guest_host) {
  guest_host_views_.erase(guest_host);
}

void CefRenderWidgetHostViewOSR::RegisterGuestViewFrameSwappedCallback(
    content::RenderWidgetHostViewGuest* guest_host_view) {
  guest_host_view->RegisterFrameSwappedCallback(
      base::MakeUnique<base::Closure>(base::Bind(
          &CefRenderWidgetHostViewOSR::OnGuestViewFrameSwapped,
          weak_ptr_factory_.GetWeakPtr(), base::Unretained(guest_host_view))));
  guest_host_view->set_current_device_scale_factor(
      current_device_scale_factor_);
}

void CefRenderWidgetHostViewOSR::OnGuestViewFrameSwapped(
    content::RenderWidgetHostViewGuest* guest_host_view) {
  InvalidateInternal(gfx::ConvertRectToPixel(current_device_scale_factor_,
                                             guest_host_view->GetViewBounds()));

  RegisterGuestViewFrameSwappedCallback(guest_host_view);
}

void CefRenderWidgetHostViewOSR::InvalidateInternal(
    const gfx::Rect& bounds_in_pixels) {
  if (software_output_device_) {
    software_output_device_->OnPaint(bounds_in_pixels);
  } else if (copy_frame_generator_.get()) {
    copy_frame_generator_->GenerateCopyFrame(bounds_in_pixels);
  }
}

void CefRenderWidgetHostViewOSR::RequestImeCompositionUpdate(
    bool start_monitoring) {
  if (!render_widget_host_)
    return;
  render_widget_host_->RequestCompositionUpdates(false, start_monitoring);
}

void CefRenderWidgetHostViewOSR::ImeCompositionRangeChanged(
    const gfx::Range& range,
    const std::vector<gfx::Rect>& character_bounds) {
  if (browser_impl_.get()) {
    CefRange cef_range(range.start(), range.end());
    CefRenderHandler::RectList rcList;

    for (size_t i = 0; i < character_bounds.size(); ++i) {
      rcList.push_back(CefRect(character_bounds[i].x(), character_bounds[i].y(),
                               character_bounds[i].width(),
                               character_bounds[i].height()));
    }

    CefRefPtr<CefRenderHandler> handler =
        browser_impl_->GetClient()->GetRenderHandler();
    if (handler.get()) {
      handler->OnImeCompositionRangeChanged(browser_impl_->GetBrowser(),
                                            cef_range, rcList);
    }
  }
}

viz::FrameSinkId CefRenderWidgetHostViewOSR::AllocateFrameSinkId(
    bool is_guest_view_hack) {
  // GuestViews have two RenderWidgetHostViews and so we need to make sure
  // we don't have FrameSinkId collisions.
  // The FrameSinkId generated here must be unique with FrameSinkId allocated
  // in ContextFactoryPrivate.
  content::ImageTransportFactory* factory =
      content::ImageTransportFactory::GetInstance();
  return is_guest_view_hack
             ? factory->GetContextFactoryPrivate()->AllocateFrameSinkId()
             : viz::FrameSinkId(base::checked_cast<uint32_t>(
                                    render_widget_host_->GetProcess()->GetID()),
                                base::checked_cast<uint32_t>(
                                    render_widget_host_->GetRoutingID()));
}

void CefRenderWidgetHostViewOSR::UpdateBackgroundColorFromRenderer(
    SkColor color) {
  if (color == background_color())
    return;
  background_color_ = color;

  bool opaque = SkColorGetA(color) == SK_AlphaOPAQUE;
  GetRootLayer()->SetFillsBoundsOpaquely(opaque);
  GetRootLayer()->SetColor(color);
}
