# Copyright (c) 2018 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.
#
# ---------------------------------------------------------------------------
#
# This file was generated by the CEF translator tool and should not edited
# by hand. See the translator.README.txt file in the tools directory for
# more information.
#
# $hash=bede6f61d0f5b45669b8e924144e4200c41f869b$
#

{
  'variables': {
    'autogen_cpp_includes': [
      'include/cef_accessibility_handler.h',
      'include/cef_app.h',
      'include/cef_auth_callback.h',
      'include/cef_browser.h',
      'include/cef_browser_process_handler.h',
      'include/cef_callback.h',
      'include/cef_client.h',
      'include/cef_command_line.h',
      'include/cef_context_menu_handler.h',
      'include/cef_cookie.h',
      'include/cef_crash_util.h',
      'include/cef_dialog_handler.h',
      'include/cef_display_handler.h',
      'include/cef_dom.h',
      'include/cef_download_handler.h',
      'include/cef_download_item.h',
      'include/cef_drag_data.h',
      'include/cef_drag_handler.h',
      'include/cef_extension.h',
      'include/cef_extension_handler.h',
      'include/cef_file_util.h',
      'include/cef_find_handler.h',
      'include/cef_focus_handler.h',
      'include/cef_frame.h',
      'include/cef_image.h',
      'include/cef_jsdialog_handler.h',
      'include/cef_keyboard_handler.h',
      'include/cef_life_span_handler.h',
      'include/cef_load_handler.h',
      'include/cef_menu_model.h',
      'include/cef_menu_model_delegate.h',
      'include/cef_navigation_entry.h',
      'include/cef_origin_whitelist.h',
      'include/cef_parser.h',
      'include/cef_path_util.h',
      'include/cef_print_handler.h',
      'include/cef_print_settings.h',
      'include/cef_process_message.h',
      'include/cef_process_util.h',
      'include/cef_render_handler.h',
      'include/cef_render_process_handler.h',
      'include/cef_request.h',
      'include/cef_request_context.h',
      'include/cef_request_context_handler.h',
      'include/cef_request_handler.h',
      'include/cef_resource_bundle.h',
      'include/cef_resource_bundle_handler.h',
      'include/cef_resource_handler.h',
      'include/cef_response.h',
      'include/cef_response_filter.h',
      'include/cef_scheme.h',
      'include/cef_server.h',
      'include/cef_ssl_info.h',
      'include/cef_ssl_status.h',
      'include/cef_stream.h',
      'include/cef_string_visitor.h',
      'include/cef_task.h',
      'include/cef_thread.h',
      'include/cef_trace.h',
      'include/cef_urlrequest.h',
      'include/cef_v8.h',
      'include/cef_values.h',
      'include/cef_waitable_event.h',
      'include/cef_web_plugin.h',
      'include/cef_x509_certificate.h',
      'include/cef_xml_reader.h',
      'include/cef_zip_reader.h',
      'include/test/cef_test_helpers.h',
      'include/test/cef_translator_test.h',
      'include/views/cef_box_layout.h',
      'include/views/cef_browser_view.h',
      'include/views/cef_browser_view_delegate.h',
      'include/views/cef_button.h',
      'include/views/cef_button_delegate.h',
      'include/views/cef_display.h',
      'include/views/cef_fill_layout.h',
      'include/views/cef_label_button.h',
      'include/views/cef_layout.h',
      'include/views/cef_menu_button.h',
      'include/views/cef_menu_button_delegate.h',
      'include/views/cef_panel.h',
      'include/views/cef_panel_delegate.h',
      'include/views/cef_scroll_view.h',
      'include/views/cef_textfield.h',
      'include/views/cef_textfield_delegate.h',
      'include/views/cef_view.h',
      'include/views/cef_view_delegate.h',
      'include/views/cef_window.h',
      'include/views/cef_window_delegate.h',
    ],
    'autogen_capi_includes': [
      'include/capi/cef_accessibility_handler_capi.h',
      'include/capi/cef_app_capi.h',
      'include/capi/cef_auth_callback_capi.h',
      'include/capi/cef_browser_capi.h',
      'include/capi/cef_browser_process_handler_capi.h',
      'include/capi/cef_callback_capi.h',
      'include/capi/cef_client_capi.h',
      'include/capi/cef_command_line_capi.h',
      'include/capi/cef_context_menu_handler_capi.h',
      'include/capi/cef_cookie_capi.h',
      'include/capi/cef_crash_util_capi.h',
      'include/capi/cef_dialog_handler_capi.h',
      'include/capi/cef_display_handler_capi.h',
      'include/capi/cef_dom_capi.h',
      'include/capi/cef_download_handler_capi.h',
      'include/capi/cef_download_item_capi.h',
      'include/capi/cef_drag_data_capi.h',
      'include/capi/cef_drag_handler_capi.h',
      'include/capi/cef_extension_capi.h',
      'include/capi/cef_extension_handler_capi.h',
      'include/capi/cef_file_util_capi.h',
      'include/capi/cef_find_handler_capi.h',
      'include/capi/cef_focus_handler_capi.h',
      'include/capi/cef_frame_capi.h',
      'include/capi/cef_image_capi.h',
      'include/capi/cef_jsdialog_handler_capi.h',
      'include/capi/cef_keyboard_handler_capi.h',
      'include/capi/cef_life_span_handler_capi.h',
      'include/capi/cef_load_handler_capi.h',
      'include/capi/cef_menu_model_capi.h',
      'include/capi/cef_menu_model_delegate_capi.h',
      'include/capi/cef_navigation_entry_capi.h',
      'include/capi/cef_origin_whitelist_capi.h',
      'include/capi/cef_parser_capi.h',
      'include/capi/cef_path_util_capi.h',
      'include/capi/cef_print_handler_capi.h',
      'include/capi/cef_print_settings_capi.h',
      'include/capi/cef_process_message_capi.h',
      'include/capi/cef_process_util_capi.h',
      'include/capi/cef_render_handler_capi.h',
      'include/capi/cef_render_process_handler_capi.h',
      'include/capi/cef_request_capi.h',
      'include/capi/cef_request_context_capi.h',
      'include/capi/cef_request_context_handler_capi.h',
      'include/capi/cef_request_handler_capi.h',
      'include/capi/cef_resource_bundle_capi.h',
      'include/capi/cef_resource_bundle_handler_capi.h',
      'include/capi/cef_resource_handler_capi.h',
      'include/capi/cef_response_capi.h',
      'include/capi/cef_response_filter_capi.h',
      'include/capi/cef_scheme_capi.h',
      'include/capi/cef_server_capi.h',
      'include/capi/cef_ssl_info_capi.h',
      'include/capi/cef_ssl_status_capi.h',
      'include/capi/cef_stream_capi.h',
      'include/capi/cef_string_visitor_capi.h',
      'include/capi/cef_task_capi.h',
      'include/capi/cef_thread_capi.h',
      'include/capi/cef_trace_capi.h',
      'include/capi/cef_urlrequest_capi.h',
      'include/capi/cef_v8_capi.h',
      'include/capi/cef_values_capi.h',
      'include/capi/cef_waitable_event_capi.h',
      'include/capi/cef_web_plugin_capi.h',
      'include/capi/cef_x509_certificate_capi.h',
      'include/capi/cef_xml_reader_capi.h',
      'include/capi/cef_zip_reader_capi.h',
      'include/capi/test/cef_test_helpers_capi.h',
      'include/capi/test/cef_translator_test_capi.h',
      'include/capi/views/cef_box_layout_capi.h',
      'include/capi/views/cef_browser_view_capi.h',
      'include/capi/views/cef_browser_view_delegate_capi.h',
      'include/capi/views/cef_button_capi.h',
      'include/capi/views/cef_button_delegate_capi.h',
      'include/capi/views/cef_display_capi.h',
      'include/capi/views/cef_fill_layout_capi.h',
      'include/capi/views/cef_label_button_capi.h',
      'include/capi/views/cef_layout_capi.h',
      'include/capi/views/cef_menu_button_capi.h',
      'include/capi/views/cef_menu_button_delegate_capi.h',
      'include/capi/views/cef_panel_capi.h',
      'include/capi/views/cef_panel_delegate_capi.h',
      'include/capi/views/cef_scroll_view_capi.h',
      'include/capi/views/cef_textfield_capi.h',
      'include/capi/views/cef_textfield_delegate_capi.h',
      'include/capi/views/cef_view_capi.h',
      'include/capi/views/cef_view_delegate_capi.h',
      'include/capi/views/cef_window_capi.h',
      'include/capi/views/cef_window_delegate_capi.h',
    ],
    'autogen_library_side': [
      'libcef_dll/ctocpp/accessibility_handler_ctocpp.cc',
      'libcef_dll/ctocpp/accessibility_handler_ctocpp.h',
      'libcef_dll/ctocpp/app_ctocpp.cc',
      'libcef_dll/ctocpp/app_ctocpp.h',
      'libcef_dll/cpptoc/auth_callback_cpptoc.cc',
      'libcef_dll/cpptoc/auth_callback_cpptoc.h',
      'libcef_dll/cpptoc/before_download_callback_cpptoc.cc',
      'libcef_dll/cpptoc/before_download_callback_cpptoc.h',
      'libcef_dll/cpptoc/binary_value_cpptoc.cc',
      'libcef_dll/cpptoc/binary_value_cpptoc.h',
      'libcef_dll/cpptoc/views/box_layout_cpptoc.cc',
      'libcef_dll/cpptoc/views/box_layout_cpptoc.h',
      'libcef_dll/cpptoc/browser_cpptoc.cc',
      'libcef_dll/cpptoc/browser_cpptoc.h',
      'libcef_dll/cpptoc/browser_host_cpptoc.cc',
      'libcef_dll/cpptoc/browser_host_cpptoc.h',
      'libcef_dll/ctocpp/browser_process_handler_ctocpp.cc',
      'libcef_dll/ctocpp/browser_process_handler_ctocpp.h',
      'libcef_dll/cpptoc/views/browser_view_cpptoc.cc',
      'libcef_dll/cpptoc/views/browser_view_cpptoc.h',
      'libcef_dll/ctocpp/views/browser_view_delegate_ctocpp.cc',
      'libcef_dll/ctocpp/views/browser_view_delegate_ctocpp.h',
      'libcef_dll/cpptoc/views/button_cpptoc.cc',
      'libcef_dll/cpptoc/views/button_cpptoc.h',
      'libcef_dll/ctocpp/views/button_delegate_ctocpp.cc',
      'libcef_dll/ctocpp/views/button_delegate_ctocpp.h',
      'libcef_dll/cpptoc/callback_cpptoc.cc',
      'libcef_dll/cpptoc/callback_cpptoc.h',
      'libcef_dll/ctocpp/client_ctocpp.cc',
      'libcef_dll/ctocpp/client_ctocpp.h',
      'libcef_dll/cpptoc/command_line_cpptoc.cc',
      'libcef_dll/cpptoc/command_line_cpptoc.h',
      'libcef_dll/ctocpp/completion_callback_ctocpp.cc',
      'libcef_dll/ctocpp/completion_callback_ctocpp.h',
      'libcef_dll/ctocpp/context_menu_handler_ctocpp.cc',
      'libcef_dll/ctocpp/context_menu_handler_ctocpp.h',
      'libcef_dll/cpptoc/context_menu_params_cpptoc.cc',
      'libcef_dll/cpptoc/context_menu_params_cpptoc.h',
      'libcef_dll/cpptoc/cookie_manager_cpptoc.cc',
      'libcef_dll/cpptoc/cookie_manager_cpptoc.h',
      'libcef_dll/ctocpp/cookie_visitor_ctocpp.cc',
      'libcef_dll/ctocpp/cookie_visitor_ctocpp.h',
      'libcef_dll/cpptoc/domdocument_cpptoc.cc',
      'libcef_dll/cpptoc/domdocument_cpptoc.h',
      'libcef_dll/cpptoc/domnode_cpptoc.cc',
      'libcef_dll/cpptoc/domnode_cpptoc.h',
      'libcef_dll/ctocpp/domvisitor_ctocpp.cc',
      'libcef_dll/ctocpp/domvisitor_ctocpp.h',
      'libcef_dll/ctocpp/delete_cookies_callback_ctocpp.cc',
      'libcef_dll/ctocpp/delete_cookies_callback_ctocpp.h',
      'libcef_dll/ctocpp/dialog_handler_ctocpp.cc',
      'libcef_dll/ctocpp/dialog_handler_ctocpp.h',
      'libcef_dll/cpptoc/dictionary_value_cpptoc.cc',
      'libcef_dll/cpptoc/dictionary_value_cpptoc.h',
      'libcef_dll/cpptoc/views/display_cpptoc.cc',
      'libcef_dll/cpptoc/views/display_cpptoc.h',
      'libcef_dll/ctocpp/display_handler_ctocpp.cc',
      'libcef_dll/ctocpp/display_handler_ctocpp.h',
      'libcef_dll/ctocpp/download_handler_ctocpp.cc',
      'libcef_dll/ctocpp/download_handler_ctocpp.h',
      'libcef_dll/ctocpp/download_image_callback_ctocpp.cc',
      'libcef_dll/ctocpp/download_image_callback_ctocpp.h',
      'libcef_dll/cpptoc/download_item_cpptoc.cc',
      'libcef_dll/cpptoc/download_item_cpptoc.h',
      'libcef_dll/cpptoc/download_item_callback_cpptoc.cc',
      'libcef_dll/cpptoc/download_item_callback_cpptoc.h',
      'libcef_dll/cpptoc/drag_data_cpptoc.cc',
      'libcef_dll/cpptoc/drag_data_cpptoc.h',
      'libcef_dll/ctocpp/drag_handler_ctocpp.cc',
      'libcef_dll/ctocpp/drag_handler_ctocpp.h',
      'libcef_dll/ctocpp/end_tracing_callback_ctocpp.cc',
      'libcef_dll/ctocpp/end_tracing_callback_ctocpp.h',
      'libcef_dll/cpptoc/extension_cpptoc.cc',
      'libcef_dll/cpptoc/extension_cpptoc.h',
      'libcef_dll/ctocpp/extension_handler_ctocpp.cc',
      'libcef_dll/ctocpp/extension_handler_ctocpp.h',
      'libcef_dll/cpptoc/file_dialog_callback_cpptoc.cc',
      'libcef_dll/cpptoc/file_dialog_callback_cpptoc.h',
      'libcef_dll/cpptoc/views/fill_layout_cpptoc.cc',
      'libcef_dll/cpptoc/views/fill_layout_cpptoc.h',
      'libcef_dll/ctocpp/find_handler_ctocpp.cc',
      'libcef_dll/ctocpp/find_handler_ctocpp.h',
      'libcef_dll/ctocpp/focus_handler_ctocpp.cc',
      'libcef_dll/ctocpp/focus_handler_ctocpp.h',
      'libcef_dll/cpptoc/frame_cpptoc.cc',
      'libcef_dll/cpptoc/frame_cpptoc.h',
      'libcef_dll/cpptoc/get_extension_resource_callback_cpptoc.cc',
      'libcef_dll/cpptoc/get_extension_resource_callback_cpptoc.h',
      'libcef_dll/cpptoc/image_cpptoc.cc',
      'libcef_dll/cpptoc/image_cpptoc.h',
      'libcef_dll/cpptoc/jsdialog_callback_cpptoc.cc',
      'libcef_dll/cpptoc/jsdialog_callback_cpptoc.h',
      'libcef_dll/ctocpp/jsdialog_handler_ctocpp.cc',
      'libcef_dll/ctocpp/jsdialog_handler_ctocpp.h',
      'libcef_dll/ctocpp/keyboard_handler_ctocpp.cc',
      'libcef_dll/ctocpp/keyboard_handler_ctocpp.h',
      'libcef_dll/cpptoc/views/label_button_cpptoc.cc',
      'libcef_dll/cpptoc/views/label_button_cpptoc.h',
      'libcef_dll/cpptoc/views/layout_cpptoc.cc',
      'libcef_dll/cpptoc/views/layout_cpptoc.h',
      'libcef_dll/ctocpp/life_span_handler_ctocpp.cc',
      'libcef_dll/ctocpp/life_span_handler_ctocpp.h',
      'libcef_dll/cpptoc/list_value_cpptoc.cc',
      'libcef_dll/cpptoc/list_value_cpptoc.h',
      'libcef_dll/ctocpp/load_handler_ctocpp.cc',
      'libcef_dll/ctocpp/load_handler_ctocpp.h',
      'libcef_dll/cpptoc/views/menu_button_cpptoc.cc',
      'libcef_dll/cpptoc/views/menu_button_cpptoc.h',
      'libcef_dll/ctocpp/views/menu_button_delegate_ctocpp.cc',
      'libcef_dll/ctocpp/views/menu_button_delegate_ctocpp.h',
      'libcef_dll/cpptoc/views/menu_button_pressed_lock_cpptoc.cc',
      'libcef_dll/cpptoc/views/menu_button_pressed_lock_cpptoc.h',
      'libcef_dll/cpptoc/menu_model_cpptoc.cc',
      'libcef_dll/cpptoc/menu_model_cpptoc.h',
      'libcef_dll/ctocpp/menu_model_delegate_ctocpp.cc',
      'libcef_dll/ctocpp/menu_model_delegate_ctocpp.h',
      'libcef_dll/cpptoc/navigation_entry_cpptoc.cc',
      'libcef_dll/cpptoc/navigation_entry_cpptoc.h',
      'libcef_dll/ctocpp/navigation_entry_visitor_ctocpp.cc',
      'libcef_dll/ctocpp/navigation_entry_visitor_ctocpp.h',
      'libcef_dll/cpptoc/views/panel_cpptoc.cc',
      'libcef_dll/cpptoc/views/panel_cpptoc.h',
      'libcef_dll/ctocpp/views/panel_delegate_ctocpp.cc',
      'libcef_dll/ctocpp/views/panel_delegate_ctocpp.h',
      'libcef_dll/ctocpp/pdf_print_callback_ctocpp.cc',
      'libcef_dll/ctocpp/pdf_print_callback_ctocpp.h',
      'libcef_dll/cpptoc/post_data_cpptoc.cc',
      'libcef_dll/cpptoc/post_data_cpptoc.h',
      'libcef_dll/cpptoc/post_data_element_cpptoc.cc',
      'libcef_dll/cpptoc/post_data_element_cpptoc.h',
      'libcef_dll/cpptoc/print_dialog_callback_cpptoc.cc',
      'libcef_dll/cpptoc/print_dialog_callback_cpptoc.h',
      'libcef_dll/ctocpp/print_handler_ctocpp.cc',
      'libcef_dll/ctocpp/print_handler_ctocpp.h',
      'libcef_dll/cpptoc/print_job_callback_cpptoc.cc',
      'libcef_dll/cpptoc/print_job_callback_cpptoc.h',
      'libcef_dll/cpptoc/print_settings_cpptoc.cc',
      'libcef_dll/cpptoc/print_settings_cpptoc.h',
      'libcef_dll/cpptoc/process_message_cpptoc.cc',
      'libcef_dll/cpptoc/process_message_cpptoc.h',
      'libcef_dll/ctocpp/read_handler_ctocpp.cc',
      'libcef_dll/ctocpp/read_handler_ctocpp.h',
      'libcef_dll/ctocpp/register_cdm_callback_ctocpp.cc',
      'libcef_dll/ctocpp/register_cdm_callback_ctocpp.h',
      'libcef_dll/ctocpp/render_handler_ctocpp.cc',
      'libcef_dll/ctocpp/render_handler_ctocpp.h',
      'libcef_dll/ctocpp/render_process_handler_ctocpp.cc',
      'libcef_dll/ctocpp/render_process_handler_ctocpp.h',
      'libcef_dll/cpptoc/request_cpptoc.cc',
      'libcef_dll/cpptoc/request_cpptoc.h',
      'libcef_dll/cpptoc/request_callback_cpptoc.cc',
      'libcef_dll/cpptoc/request_callback_cpptoc.h',
      'libcef_dll/cpptoc/request_context_cpptoc.cc',
      'libcef_dll/cpptoc/request_context_cpptoc.h',
      'libcef_dll/ctocpp/request_context_handler_ctocpp.cc',
      'libcef_dll/ctocpp/request_context_handler_ctocpp.h',
      'libcef_dll/ctocpp/request_handler_ctocpp.cc',
      'libcef_dll/ctocpp/request_handler_ctocpp.h',
      'libcef_dll/ctocpp/resolve_callback_ctocpp.cc',
      'libcef_dll/ctocpp/resolve_callback_ctocpp.h',
      'libcef_dll/cpptoc/resource_bundle_cpptoc.cc',
      'libcef_dll/cpptoc/resource_bundle_cpptoc.h',
      'libcef_dll/ctocpp/resource_bundle_handler_ctocpp.cc',
      'libcef_dll/ctocpp/resource_bundle_handler_ctocpp.h',
      'libcef_dll/ctocpp/resource_handler_ctocpp.cc',
      'libcef_dll/ctocpp/resource_handler_ctocpp.h',
      'libcef_dll/cpptoc/response_cpptoc.cc',
      'libcef_dll/cpptoc/response_cpptoc.h',
      'libcef_dll/ctocpp/response_filter_ctocpp.cc',
      'libcef_dll/ctocpp/response_filter_ctocpp.h',
      'libcef_dll/cpptoc/run_context_menu_callback_cpptoc.cc',
      'libcef_dll/cpptoc/run_context_menu_callback_cpptoc.h',
      'libcef_dll/ctocpp/run_file_dialog_callback_ctocpp.cc',
      'libcef_dll/ctocpp/run_file_dialog_callback_ctocpp.h',
      'libcef_dll/cpptoc/sslinfo_cpptoc.cc',
      'libcef_dll/cpptoc/sslinfo_cpptoc.h',
      'libcef_dll/cpptoc/sslstatus_cpptoc.cc',
      'libcef_dll/cpptoc/sslstatus_cpptoc.h',
      'libcef_dll/ctocpp/scheme_handler_factory_ctocpp.cc',
      'libcef_dll/ctocpp/scheme_handler_factory_ctocpp.h',
      'libcef_dll/cpptoc/scheme_registrar_cpptoc.cc',
      'libcef_dll/cpptoc/scheme_registrar_cpptoc.h',
      'libcef_dll/cpptoc/views/scroll_view_cpptoc.cc',
      'libcef_dll/cpptoc/views/scroll_view_cpptoc.h',
      'libcef_dll/cpptoc/select_client_certificate_callback_cpptoc.cc',
      'libcef_dll/cpptoc/select_client_certificate_callback_cpptoc.h',
      'libcef_dll/cpptoc/server_cpptoc.cc',
      'libcef_dll/cpptoc/server_cpptoc.h',
      'libcef_dll/ctocpp/server_handler_ctocpp.cc',
      'libcef_dll/ctocpp/server_handler_ctocpp.h',
      'libcef_dll/ctocpp/set_cookie_callback_ctocpp.cc',
      'libcef_dll/ctocpp/set_cookie_callback_ctocpp.h',
      'libcef_dll/cpptoc/stream_reader_cpptoc.cc',
      'libcef_dll/cpptoc/stream_reader_cpptoc.h',
      'libcef_dll/cpptoc/stream_writer_cpptoc.cc',
      'libcef_dll/cpptoc/stream_writer_cpptoc.h',
      'libcef_dll/ctocpp/string_visitor_ctocpp.cc',
      'libcef_dll/ctocpp/string_visitor_ctocpp.h',
      'libcef_dll/ctocpp/task_ctocpp.cc',
      'libcef_dll/ctocpp/task_ctocpp.h',
      'libcef_dll/cpptoc/task_runner_cpptoc.cc',
      'libcef_dll/cpptoc/task_runner_cpptoc.h',
      'libcef_dll/cpptoc/views/textfield_cpptoc.cc',
      'libcef_dll/cpptoc/views/textfield_cpptoc.h',
      'libcef_dll/ctocpp/views/textfield_delegate_ctocpp.cc',
      'libcef_dll/ctocpp/views/textfield_delegate_ctocpp.h',
      'libcef_dll/cpptoc/thread_cpptoc.cc',
      'libcef_dll/cpptoc/thread_cpptoc.h',
      'libcef_dll/cpptoc/test/translator_test_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_cpptoc.h',
      'libcef_dll/ctocpp/test/translator_test_ref_ptr_client_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_ref_ptr_client_ctocpp.h',
      'libcef_dll/ctocpp/test/translator_test_ref_ptr_client_child_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_ref_ptr_client_child_ctocpp.h',
      'libcef_dll/cpptoc/test/translator_test_ref_ptr_library_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_ref_ptr_library_cpptoc.h',
      'libcef_dll/cpptoc/test/translator_test_ref_ptr_library_child_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_ref_ptr_library_child_cpptoc.h',
      'libcef_dll/cpptoc/test/translator_test_ref_ptr_library_child_child_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_ref_ptr_library_child_child_cpptoc.h',
      'libcef_dll/ctocpp/test/translator_test_scoped_client_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_scoped_client_ctocpp.h',
      'libcef_dll/ctocpp/test/translator_test_scoped_client_child_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_scoped_client_child_ctocpp.h',
      'libcef_dll/cpptoc/test/translator_test_scoped_library_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_scoped_library_cpptoc.h',
      'libcef_dll/cpptoc/test/translator_test_scoped_library_child_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_scoped_library_child_cpptoc.h',
      'libcef_dll/cpptoc/test/translator_test_scoped_library_child_child_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_scoped_library_child_child_cpptoc.h',
      'libcef_dll/cpptoc/urlrequest_cpptoc.cc',
      'libcef_dll/cpptoc/urlrequest_cpptoc.h',
      'libcef_dll/ctocpp/urlrequest_client_ctocpp.cc',
      'libcef_dll/ctocpp/urlrequest_client_ctocpp.h',
      'libcef_dll/ctocpp/v8accessor_ctocpp.cc',
      'libcef_dll/ctocpp/v8accessor_ctocpp.h',
      'libcef_dll/cpptoc/v8context_cpptoc.cc',
      'libcef_dll/cpptoc/v8context_cpptoc.h',
      'libcef_dll/cpptoc/v8exception_cpptoc.cc',
      'libcef_dll/cpptoc/v8exception_cpptoc.h',
      'libcef_dll/ctocpp/v8handler_ctocpp.cc',
      'libcef_dll/ctocpp/v8handler_ctocpp.h',
      'libcef_dll/ctocpp/v8interceptor_ctocpp.cc',
      'libcef_dll/ctocpp/v8interceptor_ctocpp.h',
      'libcef_dll/cpptoc/v8stack_frame_cpptoc.cc',
      'libcef_dll/cpptoc/v8stack_frame_cpptoc.h',
      'libcef_dll/cpptoc/v8stack_trace_cpptoc.cc',
      'libcef_dll/cpptoc/v8stack_trace_cpptoc.h',
      'libcef_dll/cpptoc/v8value_cpptoc.cc',
      'libcef_dll/cpptoc/v8value_cpptoc.h',
      'libcef_dll/cpptoc/value_cpptoc.cc',
      'libcef_dll/cpptoc/value_cpptoc.h',
      'libcef_dll/cpptoc/views/view_cpptoc.cc',
      'libcef_dll/cpptoc/views/view_cpptoc.h',
      'libcef_dll/ctocpp/views/view_delegate_ctocpp.cc',
      'libcef_dll/ctocpp/views/view_delegate_ctocpp.h',
      'libcef_dll/cpptoc/waitable_event_cpptoc.cc',
      'libcef_dll/cpptoc/waitable_event_cpptoc.h',
      'libcef_dll/cpptoc/web_plugin_info_cpptoc.cc',
      'libcef_dll/cpptoc/web_plugin_info_cpptoc.h',
      'libcef_dll/ctocpp/web_plugin_info_visitor_ctocpp.cc',
      'libcef_dll/ctocpp/web_plugin_info_visitor_ctocpp.h',
      'libcef_dll/ctocpp/web_plugin_unstable_callback_ctocpp.cc',
      'libcef_dll/ctocpp/web_plugin_unstable_callback_ctocpp.h',
      'libcef_dll/cpptoc/views/window_cpptoc.cc',
      'libcef_dll/cpptoc/views/window_cpptoc.h',
      'libcef_dll/ctocpp/views/window_delegate_ctocpp.cc',
      'libcef_dll/ctocpp/views/window_delegate_ctocpp.h',
      'libcef_dll/ctocpp/write_handler_ctocpp.cc',
      'libcef_dll/ctocpp/write_handler_ctocpp.h',
      'libcef_dll/cpptoc/x509cert_principal_cpptoc.cc',
      'libcef_dll/cpptoc/x509cert_principal_cpptoc.h',
      'libcef_dll/cpptoc/x509certificate_cpptoc.cc',
      'libcef_dll/cpptoc/x509certificate_cpptoc.h',
      'libcef_dll/cpptoc/xml_reader_cpptoc.cc',
      'libcef_dll/cpptoc/xml_reader_cpptoc.h',
      'libcef_dll/cpptoc/zip_reader_cpptoc.cc',
      'libcef_dll/cpptoc/zip_reader_cpptoc.h',
    ],
    'autogen_client_side': [
      'libcef_dll/cpptoc/accessibility_handler_cpptoc.cc',
      'libcef_dll/cpptoc/accessibility_handler_cpptoc.h',
      'libcef_dll/cpptoc/app_cpptoc.cc',
      'libcef_dll/cpptoc/app_cpptoc.h',
      'libcef_dll/ctocpp/auth_callback_ctocpp.cc',
      'libcef_dll/ctocpp/auth_callback_ctocpp.h',
      'libcef_dll/ctocpp/before_download_callback_ctocpp.cc',
      'libcef_dll/ctocpp/before_download_callback_ctocpp.h',
      'libcef_dll/ctocpp/binary_value_ctocpp.cc',
      'libcef_dll/ctocpp/binary_value_ctocpp.h',
      'libcef_dll/ctocpp/views/box_layout_ctocpp.cc',
      'libcef_dll/ctocpp/views/box_layout_ctocpp.h',
      'libcef_dll/ctocpp/browser_ctocpp.cc',
      'libcef_dll/ctocpp/browser_ctocpp.h',
      'libcef_dll/ctocpp/browser_host_ctocpp.cc',
      'libcef_dll/ctocpp/browser_host_ctocpp.h',
      'libcef_dll/cpptoc/browser_process_handler_cpptoc.cc',
      'libcef_dll/cpptoc/browser_process_handler_cpptoc.h',
      'libcef_dll/ctocpp/views/browser_view_ctocpp.cc',
      'libcef_dll/ctocpp/views/browser_view_ctocpp.h',
      'libcef_dll/cpptoc/views/browser_view_delegate_cpptoc.cc',
      'libcef_dll/cpptoc/views/browser_view_delegate_cpptoc.h',
      'libcef_dll/ctocpp/views/button_ctocpp.cc',
      'libcef_dll/ctocpp/views/button_ctocpp.h',
      'libcef_dll/cpptoc/views/button_delegate_cpptoc.cc',
      'libcef_dll/cpptoc/views/button_delegate_cpptoc.h',
      'libcef_dll/ctocpp/callback_ctocpp.cc',
      'libcef_dll/ctocpp/callback_ctocpp.h',
      'libcef_dll/cpptoc/client_cpptoc.cc',
      'libcef_dll/cpptoc/client_cpptoc.h',
      'libcef_dll/ctocpp/command_line_ctocpp.cc',
      'libcef_dll/ctocpp/command_line_ctocpp.h',
      'libcef_dll/cpptoc/completion_callback_cpptoc.cc',
      'libcef_dll/cpptoc/completion_callback_cpptoc.h',
      'libcef_dll/cpptoc/context_menu_handler_cpptoc.cc',
      'libcef_dll/cpptoc/context_menu_handler_cpptoc.h',
      'libcef_dll/ctocpp/context_menu_params_ctocpp.cc',
      'libcef_dll/ctocpp/context_menu_params_ctocpp.h',
      'libcef_dll/ctocpp/cookie_manager_ctocpp.cc',
      'libcef_dll/ctocpp/cookie_manager_ctocpp.h',
      'libcef_dll/cpptoc/cookie_visitor_cpptoc.cc',
      'libcef_dll/cpptoc/cookie_visitor_cpptoc.h',
      'libcef_dll/ctocpp/domdocument_ctocpp.cc',
      'libcef_dll/ctocpp/domdocument_ctocpp.h',
      'libcef_dll/ctocpp/domnode_ctocpp.cc',
      'libcef_dll/ctocpp/domnode_ctocpp.h',
      'libcef_dll/cpptoc/domvisitor_cpptoc.cc',
      'libcef_dll/cpptoc/domvisitor_cpptoc.h',
      'libcef_dll/cpptoc/delete_cookies_callback_cpptoc.cc',
      'libcef_dll/cpptoc/delete_cookies_callback_cpptoc.h',
      'libcef_dll/cpptoc/dialog_handler_cpptoc.cc',
      'libcef_dll/cpptoc/dialog_handler_cpptoc.h',
      'libcef_dll/ctocpp/dictionary_value_ctocpp.cc',
      'libcef_dll/ctocpp/dictionary_value_ctocpp.h',
      'libcef_dll/ctocpp/views/display_ctocpp.cc',
      'libcef_dll/ctocpp/views/display_ctocpp.h',
      'libcef_dll/cpptoc/display_handler_cpptoc.cc',
      'libcef_dll/cpptoc/display_handler_cpptoc.h',
      'libcef_dll/cpptoc/download_handler_cpptoc.cc',
      'libcef_dll/cpptoc/download_handler_cpptoc.h',
      'libcef_dll/cpptoc/download_image_callback_cpptoc.cc',
      'libcef_dll/cpptoc/download_image_callback_cpptoc.h',
      'libcef_dll/ctocpp/download_item_ctocpp.cc',
      'libcef_dll/ctocpp/download_item_ctocpp.h',
      'libcef_dll/ctocpp/download_item_callback_ctocpp.cc',
      'libcef_dll/ctocpp/download_item_callback_ctocpp.h',
      'libcef_dll/ctocpp/drag_data_ctocpp.cc',
      'libcef_dll/ctocpp/drag_data_ctocpp.h',
      'libcef_dll/cpptoc/drag_handler_cpptoc.cc',
      'libcef_dll/cpptoc/drag_handler_cpptoc.h',
      'libcef_dll/cpptoc/end_tracing_callback_cpptoc.cc',
      'libcef_dll/cpptoc/end_tracing_callback_cpptoc.h',
      'libcef_dll/ctocpp/extension_ctocpp.cc',
      'libcef_dll/ctocpp/extension_ctocpp.h',
      'libcef_dll/cpptoc/extension_handler_cpptoc.cc',
      'libcef_dll/cpptoc/extension_handler_cpptoc.h',
      'libcef_dll/ctocpp/file_dialog_callback_ctocpp.cc',
      'libcef_dll/ctocpp/file_dialog_callback_ctocpp.h',
      'libcef_dll/ctocpp/views/fill_layout_ctocpp.cc',
      'libcef_dll/ctocpp/views/fill_layout_ctocpp.h',
      'libcef_dll/cpptoc/find_handler_cpptoc.cc',
      'libcef_dll/cpptoc/find_handler_cpptoc.h',
      'libcef_dll/cpptoc/focus_handler_cpptoc.cc',
      'libcef_dll/cpptoc/focus_handler_cpptoc.h',
      'libcef_dll/ctocpp/frame_ctocpp.cc',
      'libcef_dll/ctocpp/frame_ctocpp.h',
      'libcef_dll/ctocpp/get_extension_resource_callback_ctocpp.cc',
      'libcef_dll/ctocpp/get_extension_resource_callback_ctocpp.h',
      'libcef_dll/ctocpp/image_ctocpp.cc',
      'libcef_dll/ctocpp/image_ctocpp.h',
      'libcef_dll/ctocpp/jsdialog_callback_ctocpp.cc',
      'libcef_dll/ctocpp/jsdialog_callback_ctocpp.h',
      'libcef_dll/cpptoc/jsdialog_handler_cpptoc.cc',
      'libcef_dll/cpptoc/jsdialog_handler_cpptoc.h',
      'libcef_dll/cpptoc/keyboard_handler_cpptoc.cc',
      'libcef_dll/cpptoc/keyboard_handler_cpptoc.h',
      'libcef_dll/ctocpp/views/label_button_ctocpp.cc',
      'libcef_dll/ctocpp/views/label_button_ctocpp.h',
      'libcef_dll/ctocpp/views/layout_ctocpp.cc',
      'libcef_dll/ctocpp/views/layout_ctocpp.h',
      'libcef_dll/cpptoc/life_span_handler_cpptoc.cc',
      'libcef_dll/cpptoc/life_span_handler_cpptoc.h',
      'libcef_dll/ctocpp/list_value_ctocpp.cc',
      'libcef_dll/ctocpp/list_value_ctocpp.h',
      'libcef_dll/cpptoc/load_handler_cpptoc.cc',
      'libcef_dll/cpptoc/load_handler_cpptoc.h',
      'libcef_dll/ctocpp/views/menu_button_ctocpp.cc',
      'libcef_dll/ctocpp/views/menu_button_ctocpp.h',
      'libcef_dll/cpptoc/views/menu_button_delegate_cpptoc.cc',
      'libcef_dll/cpptoc/views/menu_button_delegate_cpptoc.h',
      'libcef_dll/ctocpp/views/menu_button_pressed_lock_ctocpp.cc',
      'libcef_dll/ctocpp/views/menu_button_pressed_lock_ctocpp.h',
      'libcef_dll/ctocpp/menu_model_ctocpp.cc',
      'libcef_dll/ctocpp/menu_model_ctocpp.h',
      'libcef_dll/cpptoc/menu_model_delegate_cpptoc.cc',
      'libcef_dll/cpptoc/menu_model_delegate_cpptoc.h',
      'libcef_dll/ctocpp/navigation_entry_ctocpp.cc',
      'libcef_dll/ctocpp/navigation_entry_ctocpp.h',
      'libcef_dll/cpptoc/navigation_entry_visitor_cpptoc.cc',
      'libcef_dll/cpptoc/navigation_entry_visitor_cpptoc.h',
      'libcef_dll/ctocpp/views/panel_ctocpp.cc',
      'libcef_dll/ctocpp/views/panel_ctocpp.h',
      'libcef_dll/cpptoc/views/panel_delegate_cpptoc.cc',
      'libcef_dll/cpptoc/views/panel_delegate_cpptoc.h',
      'libcef_dll/cpptoc/pdf_print_callback_cpptoc.cc',
      'libcef_dll/cpptoc/pdf_print_callback_cpptoc.h',
      'libcef_dll/ctocpp/post_data_ctocpp.cc',
      'libcef_dll/ctocpp/post_data_ctocpp.h',
      'libcef_dll/ctocpp/post_data_element_ctocpp.cc',
      'libcef_dll/ctocpp/post_data_element_ctocpp.h',
      'libcef_dll/ctocpp/print_dialog_callback_ctocpp.cc',
      'libcef_dll/ctocpp/print_dialog_callback_ctocpp.h',
      'libcef_dll/cpptoc/print_handler_cpptoc.cc',
      'libcef_dll/cpptoc/print_handler_cpptoc.h',
      'libcef_dll/ctocpp/print_job_callback_ctocpp.cc',
      'libcef_dll/ctocpp/print_job_callback_ctocpp.h',
      'libcef_dll/ctocpp/print_settings_ctocpp.cc',
      'libcef_dll/ctocpp/print_settings_ctocpp.h',
      'libcef_dll/ctocpp/process_message_ctocpp.cc',
      'libcef_dll/ctocpp/process_message_ctocpp.h',
      'libcef_dll/cpptoc/read_handler_cpptoc.cc',
      'libcef_dll/cpptoc/read_handler_cpptoc.h',
      'libcef_dll/cpptoc/register_cdm_callback_cpptoc.cc',
      'libcef_dll/cpptoc/register_cdm_callback_cpptoc.h',
      'libcef_dll/cpptoc/render_handler_cpptoc.cc',
      'libcef_dll/cpptoc/render_handler_cpptoc.h',
      'libcef_dll/cpptoc/render_process_handler_cpptoc.cc',
      'libcef_dll/cpptoc/render_process_handler_cpptoc.h',
      'libcef_dll/ctocpp/request_ctocpp.cc',
      'libcef_dll/ctocpp/request_ctocpp.h',
      'libcef_dll/ctocpp/request_callback_ctocpp.cc',
      'libcef_dll/ctocpp/request_callback_ctocpp.h',
      'libcef_dll/ctocpp/request_context_ctocpp.cc',
      'libcef_dll/ctocpp/request_context_ctocpp.h',
      'libcef_dll/cpptoc/request_context_handler_cpptoc.cc',
      'libcef_dll/cpptoc/request_context_handler_cpptoc.h',
      'libcef_dll/cpptoc/request_handler_cpptoc.cc',
      'libcef_dll/cpptoc/request_handler_cpptoc.h',
      'libcef_dll/cpptoc/resolve_callback_cpptoc.cc',
      'libcef_dll/cpptoc/resolve_callback_cpptoc.h',
      'libcef_dll/ctocpp/resource_bundle_ctocpp.cc',
      'libcef_dll/ctocpp/resource_bundle_ctocpp.h',
      'libcef_dll/cpptoc/resource_bundle_handler_cpptoc.cc',
      'libcef_dll/cpptoc/resource_bundle_handler_cpptoc.h',
      'libcef_dll/cpptoc/resource_handler_cpptoc.cc',
      'libcef_dll/cpptoc/resource_handler_cpptoc.h',
      'libcef_dll/ctocpp/response_ctocpp.cc',
      'libcef_dll/ctocpp/response_ctocpp.h',
      'libcef_dll/cpptoc/response_filter_cpptoc.cc',
      'libcef_dll/cpptoc/response_filter_cpptoc.h',
      'libcef_dll/ctocpp/run_context_menu_callback_ctocpp.cc',
      'libcef_dll/ctocpp/run_context_menu_callback_ctocpp.h',
      'libcef_dll/cpptoc/run_file_dialog_callback_cpptoc.cc',
      'libcef_dll/cpptoc/run_file_dialog_callback_cpptoc.h',
      'libcef_dll/ctocpp/sslinfo_ctocpp.cc',
      'libcef_dll/ctocpp/sslinfo_ctocpp.h',
      'libcef_dll/ctocpp/sslstatus_ctocpp.cc',
      'libcef_dll/ctocpp/sslstatus_ctocpp.h',
      'libcef_dll/cpptoc/scheme_handler_factory_cpptoc.cc',
      'libcef_dll/cpptoc/scheme_handler_factory_cpptoc.h',
      'libcef_dll/ctocpp/scheme_registrar_ctocpp.cc',
      'libcef_dll/ctocpp/scheme_registrar_ctocpp.h',
      'libcef_dll/ctocpp/views/scroll_view_ctocpp.cc',
      'libcef_dll/ctocpp/views/scroll_view_ctocpp.h',
      'libcef_dll/ctocpp/select_client_certificate_callback_ctocpp.cc',
      'libcef_dll/ctocpp/select_client_certificate_callback_ctocpp.h',
      'libcef_dll/ctocpp/server_ctocpp.cc',
      'libcef_dll/ctocpp/server_ctocpp.h',
      'libcef_dll/cpptoc/server_handler_cpptoc.cc',
      'libcef_dll/cpptoc/server_handler_cpptoc.h',
      'libcef_dll/cpptoc/set_cookie_callback_cpptoc.cc',
      'libcef_dll/cpptoc/set_cookie_callback_cpptoc.h',
      'libcef_dll/ctocpp/stream_reader_ctocpp.cc',
      'libcef_dll/ctocpp/stream_reader_ctocpp.h',
      'libcef_dll/ctocpp/stream_writer_ctocpp.cc',
      'libcef_dll/ctocpp/stream_writer_ctocpp.h',
      'libcef_dll/cpptoc/string_visitor_cpptoc.cc',
      'libcef_dll/cpptoc/string_visitor_cpptoc.h',
      'libcef_dll/cpptoc/task_cpptoc.cc',
      'libcef_dll/cpptoc/task_cpptoc.h',
      'libcef_dll/ctocpp/task_runner_ctocpp.cc',
      'libcef_dll/ctocpp/task_runner_ctocpp.h',
      'libcef_dll/ctocpp/views/textfield_ctocpp.cc',
      'libcef_dll/ctocpp/views/textfield_ctocpp.h',
      'libcef_dll/cpptoc/views/textfield_delegate_cpptoc.cc',
      'libcef_dll/cpptoc/views/textfield_delegate_cpptoc.h',
      'libcef_dll/ctocpp/thread_ctocpp.cc',
      'libcef_dll/ctocpp/thread_ctocpp.h',
      'libcef_dll/ctocpp/test/translator_test_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_ctocpp.h',
      'libcef_dll/cpptoc/test/translator_test_ref_ptr_client_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_ref_ptr_client_cpptoc.h',
      'libcef_dll/cpptoc/test/translator_test_ref_ptr_client_child_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_ref_ptr_client_child_cpptoc.h',
      'libcef_dll/ctocpp/test/translator_test_ref_ptr_library_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_ref_ptr_library_ctocpp.h',
      'libcef_dll/ctocpp/test/translator_test_ref_ptr_library_child_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_ref_ptr_library_child_ctocpp.h',
      'libcef_dll/ctocpp/test/translator_test_ref_ptr_library_child_child_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_ref_ptr_library_child_child_ctocpp.h',
      'libcef_dll/cpptoc/test/translator_test_scoped_client_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_scoped_client_cpptoc.h',
      'libcef_dll/cpptoc/test/translator_test_scoped_client_child_cpptoc.cc',
      'libcef_dll/cpptoc/test/translator_test_scoped_client_child_cpptoc.h',
      'libcef_dll/ctocpp/test/translator_test_scoped_library_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_scoped_library_ctocpp.h',
      'libcef_dll/ctocpp/test/translator_test_scoped_library_child_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_scoped_library_child_ctocpp.h',
      'libcef_dll/ctocpp/test/translator_test_scoped_library_child_child_ctocpp.cc',
      'libcef_dll/ctocpp/test/translator_test_scoped_library_child_child_ctocpp.h',
      'libcef_dll/ctocpp/urlrequest_ctocpp.cc',
      'libcef_dll/ctocpp/urlrequest_ctocpp.h',
      'libcef_dll/cpptoc/urlrequest_client_cpptoc.cc',
      'libcef_dll/cpptoc/urlrequest_client_cpptoc.h',
      'libcef_dll/cpptoc/v8accessor_cpptoc.cc',
      'libcef_dll/cpptoc/v8accessor_cpptoc.h',
      'libcef_dll/ctocpp/v8context_ctocpp.cc',
      'libcef_dll/ctocpp/v8context_ctocpp.h',
      'libcef_dll/ctocpp/v8exception_ctocpp.cc',
      'libcef_dll/ctocpp/v8exception_ctocpp.h',
      'libcef_dll/cpptoc/v8handler_cpptoc.cc',
      'libcef_dll/cpptoc/v8handler_cpptoc.h',
      'libcef_dll/cpptoc/v8interceptor_cpptoc.cc',
      'libcef_dll/cpptoc/v8interceptor_cpptoc.h',
      'libcef_dll/ctocpp/v8stack_frame_ctocpp.cc',
      'libcef_dll/ctocpp/v8stack_frame_ctocpp.h',
      'libcef_dll/ctocpp/v8stack_trace_ctocpp.cc',
      'libcef_dll/ctocpp/v8stack_trace_ctocpp.h',
      'libcef_dll/ctocpp/v8value_ctocpp.cc',
      'libcef_dll/ctocpp/v8value_ctocpp.h',
      'libcef_dll/ctocpp/value_ctocpp.cc',
      'libcef_dll/ctocpp/value_ctocpp.h',
      'libcef_dll/ctocpp/views/view_ctocpp.cc',
      'libcef_dll/ctocpp/views/view_ctocpp.h',
      'libcef_dll/cpptoc/views/view_delegate_cpptoc.cc',
      'libcef_dll/cpptoc/views/view_delegate_cpptoc.h',
      'libcef_dll/ctocpp/waitable_event_ctocpp.cc',
      'libcef_dll/ctocpp/waitable_event_ctocpp.h',
      'libcef_dll/ctocpp/web_plugin_info_ctocpp.cc',
      'libcef_dll/ctocpp/web_plugin_info_ctocpp.h',
      'libcef_dll/cpptoc/web_plugin_info_visitor_cpptoc.cc',
      'libcef_dll/cpptoc/web_plugin_info_visitor_cpptoc.h',
      'libcef_dll/cpptoc/web_plugin_unstable_callback_cpptoc.cc',
      'libcef_dll/cpptoc/web_plugin_unstable_callback_cpptoc.h',
      'libcef_dll/ctocpp/views/window_ctocpp.cc',
      'libcef_dll/ctocpp/views/window_ctocpp.h',
      'libcef_dll/cpptoc/views/window_delegate_cpptoc.cc',
      'libcef_dll/cpptoc/views/window_delegate_cpptoc.h',
      'libcef_dll/cpptoc/write_handler_cpptoc.cc',
      'libcef_dll/cpptoc/write_handler_cpptoc.h',
      'libcef_dll/ctocpp/x509cert_principal_ctocpp.cc',
      'libcef_dll/ctocpp/x509cert_principal_ctocpp.h',
      'libcef_dll/ctocpp/x509certificate_ctocpp.cc',
      'libcef_dll/ctocpp/x509certificate_ctocpp.h',
      'libcef_dll/ctocpp/xml_reader_ctocpp.cc',
      'libcef_dll/ctocpp/xml_reader_ctocpp.h',
      'libcef_dll/ctocpp/zip_reader_ctocpp.cc',
      'libcef_dll/ctocpp/zip_reader_ctocpp.h',
    ],
  },
}
