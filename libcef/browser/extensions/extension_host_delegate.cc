// Copyright 2017 the Chromium Embedded Framework Authors. Portions copyright
// 2014 The Chromium Authors. All rights reserved. Use of this source code is
// governed by a BSD-style license that can be found in the LICENSE file.

#include "libcef/browser/extensions/extension_host_delegate.h"

#include "libcef/browser/extensions/extensions_browser_client.h"

#include "base/logging.h"

namespace extensions {

CefExtensionHostDelegate::CefExtensionHostDelegate(
    CefBrowserHostImpl* browser) {}

CefExtensionHostDelegate::~CefExtensionHostDelegate() {}

void CefExtensionHostDelegate::OnExtensionHostCreated(
    content::WebContents* web_contents) {}

void CefExtensionHostDelegate::OnRenderViewCreatedForBackgroundPage(
    ExtensionHost* host) {}

content::JavaScriptDialogManager*
CefExtensionHostDelegate::GetJavaScriptDialogManager() {
  // Never routed here from CefBrowserHostImpl.
  NOTREACHED();
  return NULL;
}

void CefExtensionHostDelegate::CreateTab(content::WebContents* web_contents,
                                         const std::string& extension_id,
                                         WindowOpenDisposition disposition,
                                         const gfx::Rect& initial_rect,
                                         bool user_gesture) {
  // TODO(cef): Add support for extensions opening popup windows.
  NOTIMPLEMENTED();
}

void CefExtensionHostDelegate::ProcessMediaAccessRequest(
    content::WebContents* web_contents,
    const content::MediaStreamRequest& request,
    const content::MediaResponseCallback& callback,
    const Extension* extension) {
  // Never routed here from CefBrowserHostImpl.
  NOTREACHED();
}

bool CefExtensionHostDelegate::CheckMediaAccessPermission(
    content::WebContents* web_contents,
    const GURL& security_origin,
    content::MediaStreamType type,
    const Extension* extension) {
  // Never routed here from CefBrowserHostImpl.
  NOTREACHED();
  return false;
}

ExtensionHostQueue* CefExtensionHostDelegate::GetExtensionHostQueue() const {
  return CefExtensionsBrowserClient::Get()->GetExtensionHostQueue();
}

}  // namespace extensions
