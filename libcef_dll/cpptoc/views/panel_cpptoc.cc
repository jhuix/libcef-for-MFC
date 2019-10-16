// Copyright (c) 2018 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=e3f8d600b53a96cd0aebe4a65e90b9dcedfce54d$
//

#include "libcef_dll/cpptoc/views/panel_cpptoc.h"
#include "libcef_dll/cpptoc/views/box_layout_cpptoc.h"
#include "libcef_dll/cpptoc/views/browser_view_cpptoc.h"
#include "libcef_dll/cpptoc/views/button_cpptoc.h"
#include "libcef_dll/cpptoc/views/fill_layout_cpptoc.h"
#include "libcef_dll/cpptoc/views/layout_cpptoc.h"
#include "libcef_dll/cpptoc/views/scroll_view_cpptoc.h"
#include "libcef_dll/cpptoc/views/textfield_cpptoc.h"
#include "libcef_dll/cpptoc/views/view_cpptoc.h"
#include "libcef_dll/cpptoc/views/window_cpptoc.h"
#include "libcef_dll/ctocpp/views/panel_delegate_ctocpp.h"
#include "libcef_dll/ctocpp/views/view_delegate_ctocpp.h"

// GLOBAL FUNCTIONS - Body may be edited by hand.

CEF_EXPORT cef_panel_t* cef_panel_create(cef_panel_delegate_t* delegate) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: delegate

  // Execute
  CefRefPtr<CefPanel> _retval =
      CefPanel::CreatePanel(CefPanelDelegateCToCpp::Wrap(delegate));

  // Return type: refptr_same
  return CefPanelCppToC::Wrap(_retval);
}

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

struct _cef_window_t* CEF_CALLBACK panel_as_window(struct _cef_panel_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefWindow> _retval = CefPanelCppToC::Get(self)->AsWindow();

  // Return type: refptr_same
  return CefWindowCppToC::Wrap(_retval);
}

cef_fill_layout_t* CEF_CALLBACK
panel_set_to_fill_layout(struct _cef_panel_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefFillLayout> _retval =
      CefPanelCppToC::Get(self)->SetToFillLayout();

  // Return type: refptr_same
  return CefFillLayoutCppToC::Wrap(_retval);
}

cef_box_layout_t* CEF_CALLBACK
panel_set_to_box_layout(struct _cef_panel_t* self,
                        const struct _cef_box_layout_settings_t* settings) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;
  // Verify param: settings; type: struct_byref_const
  DCHECK(settings);
  if (!settings)
    return NULL;

  // Translate param: settings; type: struct_byref_const
  CefBoxLayoutSettings settingsObj;
  if (settings)
    settingsObj.Set(*settings, false);

  // Execute
  CefRefPtr<CefBoxLayout> _retval =
      CefPanelCppToC::Get(self)->SetToBoxLayout(settingsObj);

  // Return type: refptr_same
  return CefBoxLayoutCppToC::Wrap(_retval);
}

cef_layout_t* CEF_CALLBACK panel_get_layout(struct _cef_panel_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefLayout> _retval = CefPanelCppToC::Get(self)->GetLayout();

  // Return type: refptr_same
  return CefLayoutCppToC::Wrap(_retval);
}

void CEF_CALLBACK panel_layout(struct _cef_panel_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(self)->Layout();
}

void CEF_CALLBACK panel_add_child_view(struct _cef_panel_t* self,
                                       struct _cef_view_t* view) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: view; type: refptr_same
  DCHECK(view);
  if (!view)
    return;

  // Execute
  CefPanelCppToC::Get(self)->AddChildView(CefViewCppToC::Unwrap(view));
}

void CEF_CALLBACK panel_add_child_view_at(struct _cef_panel_t* self,
                                          struct _cef_view_t* view,
                                          int index) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: view; type: refptr_same
  DCHECK(view);
  if (!view)
    return;
  // Verify param: index; type: simple_byval
  DCHECK_GE(index, 0);
  if (index < 0)
    return;

  // Execute
  CefPanelCppToC::Get(self)->AddChildViewAt(CefViewCppToC::Unwrap(view), index);
}

void CEF_CALLBACK panel_reorder_child_view(struct _cef_panel_t* self,
                                           struct _cef_view_t* view,
                                           int index) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: view; type: refptr_same
  DCHECK(view);
  if (!view)
    return;

  // Execute
  CefPanelCppToC::Get(self)->ReorderChildView(CefViewCppToC::Unwrap(view),
                                              index);
}

void CEF_CALLBACK panel_remove_child_view(struct _cef_panel_t* self,
                                          struct _cef_view_t* view) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: view; type: refptr_same
  DCHECK(view);
  if (!view)
    return;

  // Execute
  CefPanelCppToC::Get(self)->RemoveChildView(CefViewCppToC::Unwrap(view));
}

void CEF_CALLBACK panel_remove_all_child_views(struct _cef_panel_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(self)->RemoveAllChildViews();
}

size_t CEF_CALLBACK panel_get_child_view_count(struct _cef_panel_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  size_t _retval = CefPanelCppToC::Get(self)->GetChildViewCount();

  // Return type: simple
  return _retval;
}

struct _cef_view_t* CEF_CALLBACK
panel_get_child_view_at(struct _cef_panel_t* self, int index) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;
  // Verify param: index; type: simple_byval
  DCHECK_GE(index, 0);
  if (index < 0)
    return NULL;

  // Execute
  CefRefPtr<CefView> _retval = CefPanelCppToC::Get(self)->GetChildViewAt(index);

  // Return type: refptr_same
  return CefViewCppToC::Wrap(_retval);
}

cef_browser_view_t* CEF_CALLBACK
panel_as_browser_view(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefBrowserView> _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
          ->AsBrowserView();

  // Return type: refptr_same
  return CefBrowserViewCppToC::Wrap(_retval);
}

cef_button_t* CEF_CALLBACK panel_as_button(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefButton> _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->AsButton();

  // Return type: refptr_same
  return CefButtonCppToC::Wrap(_retval);
}

cef_panel_t* CEF_CALLBACK panel_as_panel(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefPanel> _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->AsPanel();

  // Return type: refptr_same
  return CefPanelCppToC::Wrap(_retval);
}

cef_scroll_view_t* CEF_CALLBACK panel_as_scroll_view(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefScrollView> _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->AsScrollView();

  // Return type: refptr_same
  return CefScrollViewCppToC::Wrap(_retval);
}

cef_textfield_t* CEF_CALLBACK panel_as_textfield(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefTextfield> _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->AsTextfield();

  // Return type: refptr_same
  return CefTextfieldCppToC::Wrap(_retval);
}

cef_string_userfree_t CEF_CALLBACK
panel_get_type_string(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefString _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                          ->GetTypeString();

  // Return type: string
  return _retval.DetachToUserFree();
}

cef_string_userfree_t CEF_CALLBACK panel_to_string(struct _cef_view_t* self,
                                                   int include_children) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefString _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                          ->ToString(include_children ? true : false);

  // Return type: string
  return _retval.DetachToUserFree();
}

int CEF_CALLBACK panel_is_valid(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->IsValid();

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK panel_is_attached(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->IsAttached();

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK panel_is_same(struct _cef_view_t* self,
                               struct _cef_view_t* that) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: that; type: refptr_same
  DCHECK(that);
  if (!that)
    return 0;

  // Execute
  bool _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                     ->IsSame(CefViewCppToC::Unwrap(that));

  // Return type: bool
  return _retval;
}

struct _cef_view_delegate_t* CEF_CALLBACK
panel_get_delegate(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefViewDelegate> _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->GetDelegate();

  // Return type: refptr_diff
  return CefViewDelegateCToCpp::Unwrap(_retval);
}

struct _cef_window_t* CEF_CALLBACK panel_get_window(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefWindow> _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->GetWindow();

  // Return type: refptr_same
  return CefWindowCppToC::Wrap(_retval);
}

int CEF_CALLBACK panel_get_id(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  int _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->GetID();

  // Return type: simple
  return _retval;
}

void CEF_CALLBACK panel_set_id(struct _cef_view_t* self, int id) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->SetID(id);
}

int CEF_CALLBACK panel_get_group_id(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  int _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->GetGroupID();

  // Return type: simple
  return _retval;
}

void CEF_CALLBACK panel_set_group_id(struct _cef_view_t* self, int group_id) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
      ->SetGroupID(group_id);
}

struct _cef_view_t* CEF_CALLBACK
panel_get_parent_view(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefView> _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
          ->GetParentView();

  // Return type: refptr_same
  return CefViewCppToC::Wrap(_retval);
}

struct _cef_view_t* CEF_CALLBACK panel_get_view_for_id(struct _cef_view_t* self,
                                                       int id) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefView> _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
          ->GetViewForID(id);

  // Return type: refptr_same
  return CefViewCppToC::Wrap(_retval);
}

void CEF_CALLBACK panel_set_bounds(struct _cef_view_t* self,
                                   const cef_rect_t* bounds) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: bounds; type: simple_byref_const
  DCHECK(bounds);
  if (!bounds)
    return;

  // Translate param: bounds; type: simple_byref_const
  CefRect boundsVal = bounds ? *bounds : CefRect();

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
      ->SetBounds(boundsVal);
}

cef_rect_t CEF_CALLBACK panel_get_bounds(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return CefRect();

  // Execute
  cef_rect_t _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->GetBounds();

  // Return type: simple
  return _retval;
}

cef_rect_t CEF_CALLBACK panel_get_bounds_in_screen(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return CefRect();

  // Execute
  cef_rect_t _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                           ->GetBoundsInScreen();

  // Return type: simple
  return _retval;
}

void CEF_CALLBACK panel_set_size(struct _cef_view_t* self,
                                 const cef_size_t* size) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: size; type: simple_byref_const
  DCHECK(size);
  if (!size)
    return;

  // Translate param: size; type: simple_byref_const
  CefSize sizeVal = size ? *size : CefSize();

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->SetSize(sizeVal);
}

cef_size_t CEF_CALLBACK panel_get_size(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return CefSize();

  // Execute
  cef_size_t _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->GetSize();

  // Return type: simple
  return _retval;
}

void CEF_CALLBACK panel_set_position(struct _cef_view_t* self,
                                     const cef_point_t* position) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: position; type: simple_byref_const
  DCHECK(position);
  if (!position)
    return;

  // Translate param: position; type: simple_byref_const
  CefPoint positionVal = position ? *position : CefPoint();

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
      ->SetPosition(positionVal);
}

cef_point_t CEF_CALLBACK panel_get_position(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return CefPoint();

  // Execute
  cef_point_t _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->GetPosition();

  // Return type: simple
  return _retval;
}

cef_size_t CEF_CALLBACK panel_get_preferred_size(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return CefSize();

  // Execute
  cef_size_t _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                           ->GetPreferredSize();

  // Return type: simple
  return _retval;
}

void CEF_CALLBACK panel_size_to_preferred_size(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
      ->SizeToPreferredSize();
}

cef_size_t CEF_CALLBACK panel_get_minimum_size(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return CefSize();

  // Execute
  cef_size_t _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                           ->GetMinimumSize();

  // Return type: simple
  return _retval;
}

cef_size_t CEF_CALLBACK panel_get_maximum_size(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return CefSize();

  // Execute
  cef_size_t _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                           ->GetMaximumSize();

  // Return type: simple
  return _retval;
}

int CEF_CALLBACK panel_get_height_for_width(struct _cef_view_t* self,
                                            int width) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  int _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                    ->GetHeightForWidth(width);

  // Return type: simple
  return _retval;
}

void CEF_CALLBACK panel_invalidate_layout(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->InvalidateLayout();
}

void CEF_CALLBACK panel_set_visible(struct _cef_view_t* self, int visible) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
      ->SetVisible(visible ? true : false);
}

int CEF_CALLBACK panel_is_visible(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->IsVisible();

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK panel_is_drawn(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->IsDrawn();

  // Return type: bool
  return _retval;
}

void CEF_CALLBACK panel_set_enabled(struct _cef_view_t* self, int enabled) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
      ->SetEnabled(enabled ? true : false);
}

int CEF_CALLBACK panel_is_enabled(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->IsEnabled();

  // Return type: bool
  return _retval;
}

void CEF_CALLBACK panel_set_focusable(struct _cef_view_t* self, int focusable) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
      ->SetFocusable(focusable ? true : false);
}

int CEF_CALLBACK panel_is_focusable(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->IsFocusable();

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK panel_is_accessibility_focusable(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                     ->IsAccessibilityFocusable();

  // Return type: bool
  return _retval;
}

void CEF_CALLBACK panel_request_focus(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))->RequestFocus();
}

void CEF_CALLBACK panel_set_background_color(struct _cef_view_t* self,
                                             cef_color_t color) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
      ->SetBackgroundColor(color);
}

cef_color_t CEF_CALLBACK panel_get_background_color(struct _cef_view_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  cef_color_t _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
          ->GetBackgroundColor();

  // Return type: simple
  return _retval;
}

int CEF_CALLBACK panel_convert_point_to_screen(struct _cef_view_t* self,
                                               cef_point_t* point) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: point; type: simple_byref
  DCHECK(point);
  if (!point)
    return 0;

  // Translate param: point; type: simple_byref
  CefPoint pointVal = point ? *point : CefPoint();

  // Execute
  bool _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                     ->ConvertPointToScreen(pointVal);

  // Restore param: point; type: simple_byref
  if (point)
    *point = pointVal;

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK panel_convert_point_from_screen(struct _cef_view_t* self,
                                                 cef_point_t* point) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: point; type: simple_byref
  DCHECK(point);
  if (!point)
    return 0;

  // Translate param: point; type: simple_byref
  CefPoint pointVal = point ? *point : CefPoint();

  // Execute
  bool _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                     ->ConvertPointFromScreen(pointVal);

  // Restore param: point; type: simple_byref
  if (point)
    *point = pointVal;

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK panel_convert_point_to_window(struct _cef_view_t* self,
                                               cef_point_t* point) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: point; type: simple_byref
  DCHECK(point);
  if (!point)
    return 0;

  // Translate param: point; type: simple_byref
  CefPoint pointVal = point ? *point : CefPoint();

  // Execute
  bool _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                     ->ConvertPointToWindow(pointVal);

  // Restore param: point; type: simple_byref
  if (point)
    *point = pointVal;

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK panel_convert_point_from_window(struct _cef_view_t* self,
                                                 cef_point_t* point) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: point; type: simple_byref
  DCHECK(point);
  if (!point)
    return 0;

  // Translate param: point; type: simple_byref
  CefPoint pointVal = point ? *point : CefPoint();

  // Execute
  bool _retval = CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
                     ->ConvertPointFromWindow(pointVal);

  // Restore param: point; type: simple_byref
  if (point)
    *point = pointVal;

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK panel_convert_point_to_view(struct _cef_view_t* self,
                                             struct _cef_view_t* view,
                                             cef_point_t* point) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: view; type: refptr_same
  DCHECK(view);
  if (!view)
    return 0;
  // Verify param: point; type: simple_byref
  DCHECK(point);
  if (!point)
    return 0;

  // Translate param: point; type: simple_byref
  CefPoint pointVal = point ? *point : CefPoint();

  // Execute
  bool _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
          ->ConvertPointToView(CefViewCppToC::Unwrap(view), pointVal);

  // Restore param: point; type: simple_byref
  if (point)
    *point = pointVal;

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK panel_convert_point_from_view(struct _cef_view_t* self,
                                               struct _cef_view_t* view,
                                               cef_point_t* point) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: view; type: refptr_same
  DCHECK(view);
  if (!view)
    return 0;
  // Verify param: point; type: simple_byref
  DCHECK(point);
  if (!point)
    return 0;

  // Translate param: point; type: simple_byref
  CefPoint pointVal = point ? *point : CefPoint();

  // Execute
  bool _retval =
      CefPanelCppToC::Get(reinterpret_cast<cef_panel_t*>(self))
          ->ConvertPointFromView(CefViewCppToC::Unwrap(view), pointVal);

  // Restore param: point; type: simple_byref
  if (point)
    *point = pointVal;

  // Return type: bool
  return _retval;
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

CefPanelCppToC::CefPanelCppToC() {
  GetStruct()->as_window = panel_as_window;
  GetStruct()->set_to_fill_layout = panel_set_to_fill_layout;
  GetStruct()->set_to_box_layout = panel_set_to_box_layout;
  GetStruct()->get_layout = panel_get_layout;
  GetStruct()->layout = panel_layout;
  GetStruct()->add_child_view = panel_add_child_view;
  GetStruct()->add_child_view_at = panel_add_child_view_at;
  GetStruct()->reorder_child_view = panel_reorder_child_view;
  GetStruct()->remove_child_view = panel_remove_child_view;
  GetStruct()->remove_all_child_views = panel_remove_all_child_views;
  GetStruct()->get_child_view_count = panel_get_child_view_count;
  GetStruct()->get_child_view_at = panel_get_child_view_at;
  GetStruct()->base.as_browser_view = panel_as_browser_view;
  GetStruct()->base.as_button = panel_as_button;
  GetStruct()->base.as_panel = panel_as_panel;
  GetStruct()->base.as_scroll_view = panel_as_scroll_view;
  GetStruct()->base.as_textfield = panel_as_textfield;
  GetStruct()->base.get_type_string = panel_get_type_string;
  GetStruct()->base.to_string = panel_to_string;
  GetStruct()->base.is_valid = panel_is_valid;
  GetStruct()->base.is_attached = panel_is_attached;
  GetStruct()->base.is_same = panel_is_same;
  GetStruct()->base.get_delegate = panel_get_delegate;
  GetStruct()->base.get_window = panel_get_window;
  GetStruct()->base.get_id = panel_get_id;
  GetStruct()->base.set_id = panel_set_id;
  GetStruct()->base.get_group_id = panel_get_group_id;
  GetStruct()->base.set_group_id = panel_set_group_id;
  GetStruct()->base.get_parent_view = panel_get_parent_view;
  GetStruct()->base.get_view_for_id = panel_get_view_for_id;
  GetStruct()->base.set_bounds = panel_set_bounds;
  GetStruct()->base.get_bounds = panel_get_bounds;
  GetStruct()->base.get_bounds_in_screen = panel_get_bounds_in_screen;
  GetStruct()->base.set_size = panel_set_size;
  GetStruct()->base.get_size = panel_get_size;
  GetStruct()->base.set_position = panel_set_position;
  GetStruct()->base.get_position = panel_get_position;
  GetStruct()->base.get_preferred_size = panel_get_preferred_size;
  GetStruct()->base.size_to_preferred_size = panel_size_to_preferred_size;
  GetStruct()->base.get_minimum_size = panel_get_minimum_size;
  GetStruct()->base.get_maximum_size = panel_get_maximum_size;
  GetStruct()->base.get_height_for_width = panel_get_height_for_width;
  GetStruct()->base.invalidate_layout = panel_invalidate_layout;
  GetStruct()->base.set_visible = panel_set_visible;
  GetStruct()->base.is_visible = panel_is_visible;
  GetStruct()->base.is_drawn = panel_is_drawn;
  GetStruct()->base.set_enabled = panel_set_enabled;
  GetStruct()->base.is_enabled = panel_is_enabled;
  GetStruct()->base.set_focusable = panel_set_focusable;
  GetStruct()->base.is_focusable = panel_is_focusable;
  GetStruct()->base.is_accessibility_focusable =
      panel_is_accessibility_focusable;
  GetStruct()->base.request_focus = panel_request_focus;
  GetStruct()->base.set_background_color = panel_set_background_color;
  GetStruct()->base.get_background_color = panel_get_background_color;
  GetStruct()->base.convert_point_to_screen = panel_convert_point_to_screen;
  GetStruct()->base.convert_point_from_screen = panel_convert_point_from_screen;
  GetStruct()->base.convert_point_to_window = panel_convert_point_to_window;
  GetStruct()->base.convert_point_from_window = panel_convert_point_from_window;
  GetStruct()->base.convert_point_to_view = panel_convert_point_to_view;
  GetStruct()->base.convert_point_from_view = panel_convert_point_from_view;
}

template <>
CefRefPtr<CefPanel>
CefCppToCRefCounted<CefPanelCppToC, CefPanel, cef_panel_t>::UnwrapDerived(
    CefWrapperType type,
    cef_panel_t* s) {
  if (type == WT_WINDOW) {
    return CefWindowCppToC::Unwrap(reinterpret_cast<cef_window_t*>(s));
  }
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template <>
base::AtomicRefCount
    CefCppToCRefCounted<CefPanelCppToC, CefPanel, cef_panel_t>::DebugObjCt
        ATOMIC_DECLARATION;
#endif

template <>
CefWrapperType
    CefCppToCRefCounted<CefPanelCppToC, CefPanel, cef_panel_t>::kWrapperType =
        WT_PANEL;
