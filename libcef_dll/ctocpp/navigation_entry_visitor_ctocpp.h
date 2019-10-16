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
// $hash=017f08606ea583a9c8daca2fb319ac92a61a8391$
//

#ifndef CEF_LIBCEF_DLL_CTOCPP_NAVIGATION_ENTRY_VISITOR_CTOCPP_H_
#define CEF_LIBCEF_DLL_CTOCPP_NAVIGATION_ENTRY_VISITOR_CTOCPP_H_
#pragma once

#if !defined(BUILDING_CEF_SHARED)
#error This file can be included DLL-side only
#endif

#include "include/capi/cef_browser_capi.h"
#include "include/capi/cef_client_capi.h"
#include "include/cef_browser.h"
#include "include/cef_client.h"
#include "libcef_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed DLL-side only.
class CefNavigationEntryVisitorCToCpp
    : public CefCToCppRefCounted<CefNavigationEntryVisitorCToCpp,
                                 CefNavigationEntryVisitor,
                                 cef_navigation_entry_visitor_t> {
 public:
  CefNavigationEntryVisitorCToCpp();

  // CefNavigationEntryVisitor methods.
  bool Visit(CefRefPtr<CefNavigationEntry> entry,
             bool current,
             int index,
             int total) override;
};

#endif  // CEF_LIBCEF_DLL_CTOCPP_NAVIGATION_ENTRY_VISITOR_CTOCPP_H_
