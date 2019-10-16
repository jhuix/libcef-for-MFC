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
// $hash=0642f7c3dbcf13d133f806853d31edd4102d7d84$
//

#ifndef CEF_LIBCEF_DLL_CPPTOC_SSLSTATUS_CPPTOC_H_
#define CEF_LIBCEF_DLL_CPPTOC_SSLSTATUS_CPPTOC_H_
#pragma once

#if !defined(BUILDING_CEF_SHARED)
#error This file can be included DLL-side only
#endif

#include "include/capi/cef_ssl_status_capi.h"
#include "include/cef_ssl_status.h"
#include "libcef_dll/cpptoc/cpptoc_ref_counted.h"

// Wrap a C++ class with a C structure.
// This class may be instantiated and accessed DLL-side only.
class CefSSLStatusCppToC : public CefCppToCRefCounted<CefSSLStatusCppToC,
                                                      CefSSLStatus,
                                                      cef_sslstatus_t> {
 public:
  CefSSLStatusCppToC();
};

#endif  // CEF_LIBCEF_DLL_CPPTOC_SSLSTATUS_CPPTOC_H_
