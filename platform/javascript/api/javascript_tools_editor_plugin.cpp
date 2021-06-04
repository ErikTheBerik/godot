/*************************************************************************/
/*  javascript_tools_editor_plugin.cpp                                   */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
<<<<<<< HEAD
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
=======
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#if defined(TOOLS_ENABLED) && defined(JAVASCRIPT_ENABLED)
#include "javascript_tools_editor_plugin.h"

<<<<<<< HEAD
#include "core/engine.h"
#include "core/os/dir_access.h"
#include "core/os/file_access.h"
#include "core/project_settings.h"
=======
#include "core/config/engine.h"
#include "core/config/project_settings.h"
#include "core/os/dir_access.h"
#include "core/os/file_access.h"
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
#include "editor/editor_node.h"

#include <emscripten/emscripten.h>

// JavaScript functions defined in library_godot_editor_tools.js
extern "C" {
<<<<<<< HEAD
extern void godot_js_editor_download_file(const char *p_path, const char *p_name, const char *p_mime);
=======
extern int godot_js_os_download_buffer(const uint8_t *p_buf, int p_buf_size, const char *p_name, const char *p_mime);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
}

static void _javascript_editor_init_callback() {
	EditorNode::get_singleton()->add_editor_plugin(memnew(JavaScriptToolsEditorPlugin(EditorNode::get_singleton())));
}

void JavaScriptToolsEditorPlugin::initialize() {
	EditorNode::add_init_callback(_javascript_editor_init_callback);
}

JavaScriptToolsEditorPlugin::JavaScriptToolsEditorPlugin(EditorNode *p_editor) {
<<<<<<< HEAD
	Variant v;
	add_tool_menu_item("Download Project Source", this, "_download_zip", v);
=======
	add_tool_menu_item("Download Project Source", callable_mp(this, &JavaScriptToolsEditorPlugin::_download_zip));
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
}

void JavaScriptToolsEditorPlugin::_download_zip(Variant p_v) {
	if (!Engine::get_singleton() || !Engine::get_singleton()->is_editor_hint()) {
		WARN_PRINT("Project download is only available in Editor mode");
		return;
	}
	String resource_path = ProjectSettings::get_singleton()->get_resource_path();

	FileAccess *src_f;
	zlib_filefunc_def io = zipio_create_io_from_file(&src_f);
<<<<<<< HEAD
	zipFile zip = zipOpen2("/tmp/project.zip", APPEND_STATUS_CREATE, NULL, &io);
	String base_path = resource_path.substr(0, resource_path.rfind("/")) + "/";
	_zip_recursive(resource_path, base_path, zip);
	zipClose(zip, NULL);
	godot_js_editor_download_file("/tmp/project.zip", "project.zip", "application/zip");
}

void JavaScriptToolsEditorPlugin::_bind_methods() {
	ClassDB::bind_method("_download_zip", &JavaScriptToolsEditorPlugin::_download_zip);
=======
	zipFile zip = zipOpen2("/tmp/project.zip", APPEND_STATUS_CREATE, nullptr, &io);
	String base_path = resource_path.substr(0, resource_path.rfind("/")) + "/";
	_zip_recursive(resource_path, base_path, zip);
	zipClose(zip, nullptr);
	FileAccess *f = FileAccess::open("/tmp/project.zip", FileAccess::READ);
	ERR_FAIL_COND_MSG(!f, "Unable to create zip file");
	Vector<uint8_t> buf;
	buf.resize(f->get_length());
	f->get_buffer(buf.ptrw(), buf.size());
	godot_js_os_download_buffer(buf.ptr(), buf.size(), "project.zip", "application/zip");
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
}

void JavaScriptToolsEditorPlugin::_zip_file(String p_path, String p_base_path, zipFile p_zip) {
	FileAccess *f = FileAccess::open(p_path, FileAccess::READ);
	if (!f) {
		WARN_PRINT("Unable to open file for zipping: " + p_path);
		return;
	}
	Vector<uint8_t> data;
<<<<<<< HEAD
	int len = f->get_len();
=======
	uint64_t len = f->get_length();
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	data.resize(len);
	f->get_buffer(data.ptrw(), len);
	f->close();
	memdelete(f);

	String path = p_path.replace_first(p_base_path, "");
	zipOpenNewFileInZip(p_zip,
			path.utf8().get_data(),
<<<<<<< HEAD
			NULL,
			NULL,
			0,
			NULL,
			0,
			NULL,
=======
			nullptr,
			nullptr,
			0,
			nullptr,
			0,
			nullptr,
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			Z_DEFLATED,
			Z_DEFAULT_COMPRESSION);
	zipWriteInFileInZip(p_zip, data.ptr(), data.size());
	zipCloseFileInZip(p_zip);
}

void JavaScriptToolsEditorPlugin::_zip_recursive(String p_path, String p_base_path, zipFile p_zip) {
	DirAccess *dir = DirAccess::open(p_path);
	if (!dir) {
		WARN_PRINT("Unable to open dir for zipping: " + p_path);
		return;
	}
	dir->list_dir_begin();
	String cur = dir->get_next();
<<<<<<< HEAD
	while (!cur.empty()) {
=======
	while (!cur.is_empty()) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		String cs = p_path.plus_file(cur);
		if (cur == "." || cur == ".." || cur == ".import") {
			// Skip
		} else if (dir->current_is_dir()) {
			String path = cs.replace_first(p_base_path, "") + "/";
			zipOpenNewFileInZip(p_zip,
					path.utf8().get_data(),
<<<<<<< HEAD
					NULL,
					NULL,
					0,
					NULL,
					0,
					NULL,
=======
					nullptr,
					nullptr,
					0,
					nullptr,
					0,
					nullptr,
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
					Z_DEFLATED,
					Z_DEFAULT_COMPRESSION);
			zipCloseFileInZip(p_zip);
			_zip_recursive(cs, p_base_path, p_zip);
		} else {
			_zip_file(cs, p_base_path, p_zip);
		}
		cur = dir->get_next();
	}
}
#endif
