/*************************************************************************/
/*  os_osx.h                                                             */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
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

#ifndef OS_OSX_H
#define OS_OSX_H

#include "core/input/input.h"
#include "crash_handler_osx.h"
#include "drivers/coreaudio/audio_driver_coreaudio.h"
#include "drivers/coremidi/midi_driver_coremidi.h"
#include "drivers/unix/os_unix.h"
#include "joypad_osx.h"
#include "servers/audio_server.h"

class OS_OSX : public OS_Unix {
<<<<<<< HEAD
public:
	struct KeyEvent {
		unsigned int osx_state;
		bool pressed;
		bool echo;
		bool raw;
		uint32_t scancode;
		uint32_t unicode;
	};

	struct WarpEvent {
		NSTimeInterval timestamp;
		NSPoint delta;
	};
	List<WarpEvent> warp_events;
	NSTimeInterval last_warp = 0;

	Vector<KeyEvent> key_event_buffer;
	int key_event_pos;
=======
	virtual void delete_main_loop() override;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	bool force_quit;

	JoypadOSX *joypad_osx = nullptr;

#ifdef COREAUDIO_ENABLED
	AudioDriverCoreAudio audio_driver;
#endif
#ifdef COREMIDI_ENABLED
	MIDIDriverCoreMidi midi_driver;
#endif

<<<<<<< HEAD
	InputDefault *input;
	JoypadOSX *joypad_osx;

	/* objc */

	CGEventSourceRef eventSource;

	void process_events();
	void process_key_events();

	void *framework;
	//          pthread_key_t   current;
	bool mouse_grab;
	Point2 mouse_pos;

	id delegate;
	id window_delegate;
	id window_object;
	id window_view;
	id autoreleasePool;
	id cursor;
	NSOpenGLPixelFormat *pixelFormat;
	NSOpenGLContext *context;

	Vector<Vector2> mpath;
	bool layered_window;

	CursorShape cursor_shape;
	NSCursor *cursors[CURSOR_MAX];
	Map<CursorShape, Vector<Variant> > cursors_cache;
	MouseMode mouse_mode;

	String title;
	bool minimized;
	bool maximized;
	bool zoomed;
	bool resizable;
	bool window_focused;
	bool on_top;

	Size2 window_size;
	Rect2 restore_rect;

	String open_with_filename;

	Point2 im_position;
	bool im_active;
	String im_text;
	Point2 im_selection;

	Size2 min_size;
	Size2 max_size;

	PowerOSX *power_manager;

	CrashHandler crash_handler;

	void _update_window();

	int video_driver_index;
	virtual int get_current_video_driver() const;

	struct GlobalMenuItem {
		String label;
		Variant signal;
		Variant meta;

		GlobalMenuItem() {
			//NOP
		}

		GlobalMenuItem(const String &p_label, const Variant &p_signal, const Variant &p_meta) {
			label = p_label;
			signal = p_signal;
			meta = p_meta;
		}
	};

	Map<String, Vector<GlobalMenuItem> > global_menus;
	List<String> global_menus_order;

	void _update_global_menu();

protected:
	virtual void initialize_core();
	virtual Error initialize(const VideoMode &p_desired, int p_video_driver, int p_audio_driver);
	virtual void finalize();

	virtual void set_main_loop(MainLoop *p_main_loop);
	virtual void delete_main_loop();

public:
	static OS_OSX *singleton;

	void global_menu_add_item(const String &p_menu, const String &p_label, const Variant &p_signal, const Variant &p_meta);
	void global_menu_add_separator(const String &p_menu);
	void global_menu_remove_item(const String &p_menu, int p_idx);
	void global_menu_clear(const String &p_menu);

	void wm_minimized(bool p_minimized);

	virtual String get_name() const;

	virtual void alert(const String &p_alert, const String &p_title = "ALERT!");

	virtual Error open_dynamic_library(const String p_path, void *&p_library_handle, bool p_also_set_library_path = false);

	virtual void set_cursor_shape(CursorShape p_shape);
	virtual CursorShape get_cursor_shape() const;
	virtual void set_custom_mouse_cursor(const RES &p_cursor, CursorShape p_shape, const Vector2 &p_hotspot);

	virtual void set_mouse_show(bool p_show);
	virtual void set_mouse_grab(bool p_grab);
	virtual bool is_mouse_grab_enabled() const;
	virtual void warp_mouse_position(const Point2 &p_to);
	virtual Point2 get_mouse_position() const;
	virtual int get_mouse_button_state() const;
	void update_real_mouse_position();
	virtual void set_window_title(const String &p_title);
	virtual void set_window_mouse_passthrough(const PoolVector2Array &p_region);

	virtual Size2 get_window_size() const;
	virtual Size2 get_real_window_size() const;

	virtual void set_native_icon(const String &p_filename);
	virtual void set_icon(const Ref<Image> &p_icon);

	virtual MainLoop *get_main_loop() const;

	virtual String get_config_path() const;
	virtual String get_data_path() const;
	virtual String get_cache_path() const;
	virtual String get_bundle_resource_dir() const;
	virtual String get_godot_dir_name() const;

	virtual String get_system_dir(SystemDir p_dir) const;

	virtual bool can_draw() const;

	virtual void set_clipboard(const String &p_text);
	virtual String get_clipboard() const;

	virtual void release_rendering_thread();
	virtual void make_rendering_thread();
	virtual void swap_buffers();

	Error shell_open(String p_uri);
	void push_input(const Ref<InputEvent> &p_event);

	String get_locale() const;
=======
	CrashHandler crash_handler;

	MainLoop *main_loop;

public:
	String open_with_filename;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

protected:
	virtual void initialize_core() override;
	virtual void initialize() override;
	virtual void finalize() override;

	virtual void initialize_joypads() override;

<<<<<<< HEAD
	virtual LatinKeyboardVariant get_latin_keyboard_variant() const;
	virtual int keyboard_get_layout_count() const;
	virtual int keyboard_get_current_layout() const;
	virtual void keyboard_set_current_layout(int p_index);
	virtual String keyboard_get_layout_language(int p_index) const;
	virtual String keyboard_get_layout_name(int p_index) const;
=======
	virtual void set_main_loop(MainLoop *p_main_loop) override;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

public:
	virtual String get_name() const override;

<<<<<<< HEAD
	virtual int get_screen_count() const;
	virtual int get_current_screen() const;
	virtual void set_current_screen(int p_screen);
	virtual Point2 get_screen_position(int p_screen = -1) const;
	virtual Size2 get_screen_size(int p_screen = -1) const;
	virtual int get_screen_dpi(int p_screen = -1) const;
	virtual float get_screen_scale(int p_screen = -1) const;
	virtual float get_screen_max_scale() const;
=======
	virtual Error open_dynamic_library(const String p_path, void *&p_library_handle, bool p_also_set_library_path = false) override;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	virtual MainLoop *get_main_loop() const override;

	virtual String get_config_path() const override;
	virtual String get_data_path() const override;
	virtual String get_cache_path() const override;
	virtual String get_bundle_resource_dir() const override;
	virtual String get_godot_dir_name() const override;

	virtual String get_system_dir(SystemDir p_dir) const override;

	Error shell_open(String p_uri) override;

	String get_locale() const override;

	virtual String get_executable_path() const override;

	virtual String get_unique_id() const override; //++

	virtual bool _check_internal_feature_support(const String &p_feature) override;

	void run();

	virtual void disable_crash_handler() override;
	virtual bool is_disable_crash_handler() const override;

	virtual Error move_to_trash(const String &p_path) override;

	OS_OSX();
};

#endif
