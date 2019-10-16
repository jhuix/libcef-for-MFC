// Copyright 2017 The Chromium Embedded Framework Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CEF_LIBCEF_BROWSER_VIEWS_BROWSER_PLATFORM_DELEGATE_BACKGROUND_H_
#define CEF_LIBCEF_BROWSER_VIEWS_BROWSER_PLATFORM_DELEGATE_BACKGROUND_H_

#include "libcef/browser/browser_platform_delegate.h"
#include "libcef/browser/native/browser_platform_delegate_native.h"

// Implementation of browser functionality for background script hosts.
class CefBrowserPlatformDelegateBackground
    : public CefBrowserPlatformDelegate,
      public CefBrowserPlatformDelegateNative::WindowlessHandler {
 public:
  // Platform-specific behaviors will be delegated to |native_delegate|.
  CefBrowserPlatformDelegateBackground(
      std::unique_ptr<CefBrowserPlatformDelegateNative> native_delegate);

  // CefBrowserPlatformDelegate methods:
  bool CreateHostWindow() override;
  void CloseHostWindow() override;
  CefWindowHandle GetHostWindowHandle() const override;
  SkColor GetBackgroundColor() const override;
  void WasResized() override;
  void SendKeyEvent(const content::NativeWebKeyboardEvent& event) override;
  void SendMouseEvent(const blink::WebMouseEvent& event) override;
  void SendMouseWheelEvent(const blink::WebMouseWheelEvent& event) override;
  void SendFocusEvent(bool setFocus) override;
  gfx::Point GetScreenPoint(const gfx::Point& view) const override;
  void ViewText(const std::string& text) override;
  void HandleKeyboardEvent(
      const content::NativeWebKeyboardEvent& event) override;
  void HandleExternalProtocol(const GURL& url) override;
  void TranslateKeyEvent(content::NativeWebKeyboardEvent& result,
                         const CefKeyEvent& key_event) const override;
  void TranslateClickEvent(blink::WebMouseEvent& result,
                           const CefMouseEvent& mouse_event,
                           CefBrowserHost::MouseButtonType type,
                           bool mouseUp,
                           int clickCount) const override;
  void TranslateMoveEvent(blink::WebMouseEvent& result,
                          const CefMouseEvent& mouse_event,
                          bool mouseLeave) const override;
  void TranslateWheelEvent(blink::WebMouseWheelEvent& result,
                           const CefMouseEvent& mouse_event,
                           int deltaX,
                           int deltaY) const override;
  CefEventHandle GetEventHandle(
      const content::NativeWebKeyboardEvent& event) const override;
  std::unique_ptr<CefFileDialogRunner> CreateFileDialogRunner() override;
  std::unique_ptr<CefJavaScriptDialogRunner> CreateJavaScriptDialogRunner()
      override;
  std::unique_ptr<CefMenuRunner> CreateMenuRunner() override;
  bool IsWindowless() const override;
  bool IsViewsHosted() const override;

  // CefBrowserPlatformDelegateNative::WindowlessHandler methods:
  CefWindowHandle GetParentWindowHandle() const override;
  gfx::Point GetParentScreenPoint(const gfx::Point& view) const override;

 private:
  std::unique_ptr<CefBrowserPlatformDelegateNative> native_delegate_;
};

#endif  // CEF_LIBCEF_BROWSER_VIEWS_BROWSER_PLATFORM_DELEGATE_BACKGROUND_H_
