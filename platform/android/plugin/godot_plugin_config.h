/*************************************************************************/
/*  godot_plugin_config.h                                                */
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

#ifndef GODOT_PLUGIN_CONFIG_H
#define GODOT_PLUGIN_CONFIG_H

<<<<<<< HEAD
#include "core/error_list.h"
#include "core/io/config_file.h"
#include "core/ustring.h"

static const char *PLUGIN_CONFIG_EXT = ".gdap";

static const char *CONFIG_SECTION = "config";
static const char *CONFIG_NAME_KEY = "name";
static const char *CONFIG_BINARY_TYPE_KEY = "binary_type";
static const char *CONFIG_BINARY_KEY = "binary";

static const char *DEPENDENCIES_SECTION = "dependencies";
static const char *DEPENDENCIES_LOCAL_KEY = "local";
static const char *DEPENDENCIES_REMOTE_KEY = "remote";
static const char *DEPENDENCIES_CUSTOM_MAVEN_REPOS_KEY = "custom_maven_repos";

static const char *BINARY_TYPE_LOCAL = "local";
static const char *BINARY_TYPE_REMOTE = "remote";

static const char *PLUGIN_VALUE_SEPARATOR = "|";
=======
#include "core/error/error_list.h"
#include "core/io/config_file.h"
#include "core/string/ustring.h"
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

/*
 The `config` section and fields are required and defined as follow:
- **name**: name of the plugin
- **binary_type**: can be either `local` or `remote`.  The type affects the **binary** field
- **binary**:
  - if **binary_type** is `local`, then this should be the filename of the plugin `aar` file in the `res://android/plugins` directory (e.g: `MyPlugin.aar`).
  - if **binary_type** is `remote`, then this should be a declaration for a remote gradle binary (e.g: "org.godot.example:my-plugin:0.0.0").

The `dependencies` section and fields are optional and defined as follow:
- **local**: contains a list of local `.aar` binary files the plugin depends on. The local binary dependencies must also be located in the `res://android/plugins` directory.
- **remote**: contains a list of remote binary gradle dependencies for the plugin.
- **custom_maven_repos**: contains a list of urls specifying custom maven repos required for the plugin's dependencies.

 See https://github.com/godotengine/godot/issues/38157#issuecomment-618773871
 */
<<<<<<< HEAD
struct PluginConfig {
=======
struct PluginConfigAndroid {
	inline static const char *PLUGIN_CONFIG_EXT = ".gdap";

	inline static const char *CONFIG_SECTION = "config";
	inline static const char *CONFIG_NAME_KEY = "name";
	inline static const char *CONFIG_BINARY_TYPE_KEY = "binary_type";
	inline static const char *CONFIG_BINARY_KEY = "binary";

	inline static const char *DEPENDENCIES_SECTION = "dependencies";
	inline static const char *DEPENDENCIES_LOCAL_KEY = "local";
	inline static const char *DEPENDENCIES_REMOTE_KEY = "remote";
	inline static const char *DEPENDENCIES_CUSTOM_MAVEN_REPOS_KEY = "custom_maven_repos";

	inline static const char *BINARY_TYPE_LOCAL = "local";
	inline static const char *BINARY_TYPE_REMOTE = "remote";

	inline static const char *PLUGIN_VALUE_SEPARATOR = "|";

>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	// Set to true when the config file is properly loaded.
	bool valid_config = false;
	// Unix timestamp of last change to this plugin.
	uint64_t last_updated = 0;

	// Required config section
	String name;
	String binary_type;
	String binary;

	// Optional dependencies section
	Vector<String> local_dependencies;
	Vector<String> remote_dependencies;
	Vector<String> custom_maven_repos;
};

/*
 * Set of prebuilt plugins.
 * Currently unused, this is just for future reference:
 */
<<<<<<< HEAD
// static const PluginConfig MY_PREBUILT_PLUGIN = {
=======
// static const PluginConfigAndroid MY_PREBUILT_PLUGIN = {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
//	/*.valid_config =*/true,
//	/*.last_updated =*/0,
//	/*.name =*/"GodotPayment",
//	/*.binary_type =*/"local",
//	/*.binary =*/"res://android/build/libs/plugins/GodotPayment.release.aar",
//	/*.local_dependencies =*/{},
// 	/*.remote_dependencies =*/String("com.android.billingclient:billing:2.2.1").split("|"),
// 	/*.custom_maven_repos =*/{}
// };

static inline String resolve_local_dependency_path(String plugin_config_dir, String dependency_path) {
	String absolute_path;
<<<<<<< HEAD
	if (!dependency_path.empty()) {
=======
	if (!dependency_path.is_empty()) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		if (dependency_path.is_abs_path()) {
			absolute_path = ProjectSettings::get_singleton()->globalize_path(dependency_path);
		} else {
			absolute_path = plugin_config_dir.plus_file(dependency_path);
		}
	}

	return absolute_path;
}

<<<<<<< HEAD
static inline PluginConfig resolve_prebuilt_plugin(PluginConfig prebuilt_plugin, String plugin_config_dir) {
	PluginConfig resolved = prebuilt_plugin;
	resolved.binary = resolved.binary_type == BINARY_TYPE_LOCAL ? resolve_local_dependency_path(plugin_config_dir, prebuilt_plugin.binary) : prebuilt_plugin.binary;
	if (!prebuilt_plugin.local_dependencies.empty()) {
=======
static inline PluginConfigAndroid resolve_prebuilt_plugin(PluginConfigAndroid prebuilt_plugin, String plugin_config_dir) {
	PluginConfigAndroid resolved = prebuilt_plugin;
	resolved.binary = resolved.binary_type == PluginConfigAndroid::BINARY_TYPE_LOCAL ? resolve_local_dependency_path(plugin_config_dir, prebuilt_plugin.binary) : prebuilt_plugin.binary;
	if (!prebuilt_plugin.local_dependencies.is_empty()) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		resolved.local_dependencies.clear();
		for (int i = 0; i < prebuilt_plugin.local_dependencies.size(); i++) {
			resolved.local_dependencies.push_back(resolve_local_dependency_path(plugin_config_dir, prebuilt_plugin.local_dependencies[i]));
		}
	}
	return resolved;
}

<<<<<<< HEAD
static inline Vector<PluginConfig> get_prebuilt_plugins(String plugins_base_dir) {
	Vector<PluginConfig> prebuilt_plugins;
=======
static inline Vector<PluginConfigAndroid> get_prebuilt_plugins(String plugins_base_dir) {
	Vector<PluginConfigAndroid> prebuilt_plugins;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	// prebuilt_plugins.push_back(resolve_prebuilt_plugin(MY_PREBUILT_PLUGIN, plugins_base_dir));
	return prebuilt_plugins;
}

<<<<<<< HEAD
static inline bool is_plugin_config_valid(PluginConfig plugin_config) {
	bool valid_name = !plugin_config.name.empty();
	bool valid_binary_type = plugin_config.binary_type == BINARY_TYPE_LOCAL ||
							 plugin_config.binary_type == BINARY_TYPE_REMOTE;

	bool valid_binary = false;
	if (valid_binary_type) {
		valid_binary = !plugin_config.binary.empty() &&
					   (plugin_config.binary_type == BINARY_TYPE_REMOTE ||
=======
static inline bool is_plugin_config_valid(PluginConfigAndroid plugin_config) {
	bool valid_name = !plugin_config.name.is_empty();
	bool valid_binary_type = plugin_config.binary_type == PluginConfigAndroid::BINARY_TYPE_LOCAL ||
							 plugin_config.binary_type == PluginConfigAndroid::BINARY_TYPE_REMOTE;

	bool valid_binary = false;
	if (valid_binary_type) {
		valid_binary = !plugin_config.binary.is_empty() &&
					   (plugin_config.binary_type == PluginConfigAndroid::BINARY_TYPE_REMOTE ||

>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
							   FileAccess::exists(plugin_config.binary));
	}

	bool valid_local_dependencies = true;
<<<<<<< HEAD
	if (!plugin_config.local_dependencies.empty()) {
=======
	if (!plugin_config.local_dependencies.is_empty()) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		for (int i = 0; i < plugin_config.local_dependencies.size(); i++) {
			if (!FileAccess::exists(plugin_config.local_dependencies[i])) {
				valid_local_dependencies = false;
				break;
			}
		}
	}
	return valid_name && valid_binary && valid_binary_type && valid_local_dependencies;
}

<<<<<<< HEAD
static inline uint64_t get_plugin_modification_time(const PluginConfig &plugin_config, const String &config_path) {
=======
static inline uint64_t get_plugin_modification_time(const PluginConfigAndroid &plugin_config, const String &config_path) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	uint64_t last_updated = FileAccess::get_modified_time(config_path);
	last_updated = MAX(last_updated, FileAccess::get_modified_time(plugin_config.binary));

	for (int i = 0; i < plugin_config.local_dependencies.size(); i++) {
		String binary = plugin_config.local_dependencies.get(i);
		last_updated = MAX(last_updated, FileAccess::get_modified_time(binary));
	}

	return last_updated;
}

<<<<<<< HEAD
static inline PluginConfig load_plugin_config(Ref<ConfigFile> config_file, const String &path) {
	PluginConfig plugin_config = {};
=======
static inline PluginConfigAndroid load_plugin_config(Ref<ConfigFile> config_file, const String &path) {
	PluginConfigAndroid plugin_config = {};
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	if (config_file.is_valid()) {
		Error err = config_file->load(path);
		if (err == OK) {
			String config_base_dir = path.get_base_dir();

<<<<<<< HEAD
			plugin_config.name = config_file->get_value(CONFIG_SECTION, CONFIG_NAME_KEY, String());
			plugin_config.binary_type = config_file->get_value(CONFIG_SECTION, CONFIG_BINARY_TYPE_KEY, String());

			String binary_path = config_file->get_value(CONFIG_SECTION, CONFIG_BINARY_KEY, String());
			plugin_config.binary = plugin_config.binary_type == BINARY_TYPE_LOCAL ? resolve_local_dependency_path(config_base_dir, binary_path) : binary_path;

			if (config_file->has_section(DEPENDENCIES_SECTION)) {
				Vector<String> local_dependencies_paths = config_file->get_value(DEPENDENCIES_SECTION, DEPENDENCIES_LOCAL_KEY, Vector<String>());
				if (!local_dependencies_paths.empty()) {
=======
			plugin_config.name = config_file->get_value(PluginConfigAndroid::CONFIG_SECTION, PluginConfigAndroid::CONFIG_NAME_KEY, String());
			plugin_config.binary_type = config_file->get_value(PluginConfigAndroid::CONFIG_SECTION, PluginConfigAndroid::CONFIG_BINARY_TYPE_KEY, String());

			String binary_path = config_file->get_value(PluginConfigAndroid::CONFIG_SECTION, PluginConfigAndroid::CONFIG_BINARY_KEY, String());
			plugin_config.binary = plugin_config.binary_type == PluginConfigAndroid::BINARY_TYPE_LOCAL ? resolve_local_dependency_path(config_base_dir, binary_path) : binary_path;

			if (config_file->has_section(PluginConfigAndroid::DEPENDENCIES_SECTION)) {
				Vector<String> local_dependencies_paths = config_file->get_value(PluginConfigAndroid::DEPENDENCIES_SECTION, PluginConfigAndroid::DEPENDENCIES_LOCAL_KEY, Vector<String>());
				if (!local_dependencies_paths.is_empty()) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
					for (int i = 0; i < local_dependencies_paths.size(); i++) {
						plugin_config.local_dependencies.push_back(resolve_local_dependency_path(config_base_dir, local_dependencies_paths[i]));
					}
				}

<<<<<<< HEAD
				plugin_config.remote_dependencies = config_file->get_value(DEPENDENCIES_SECTION, DEPENDENCIES_REMOTE_KEY, Vector<String>());
				plugin_config.custom_maven_repos = config_file->get_value(DEPENDENCIES_SECTION, DEPENDENCIES_CUSTOM_MAVEN_REPOS_KEY, Vector<String>());
=======
				plugin_config.remote_dependencies = config_file->get_value(PluginConfigAndroid::DEPENDENCIES_SECTION, PluginConfigAndroid::DEPENDENCIES_REMOTE_KEY, Vector<String>());
				plugin_config.custom_maven_repos = config_file->get_value(PluginConfigAndroid::DEPENDENCIES_SECTION, PluginConfigAndroid::DEPENDENCIES_CUSTOM_MAVEN_REPOS_KEY, Vector<String>());
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			}

			plugin_config.valid_config = is_plugin_config_valid(plugin_config);
			plugin_config.last_updated = get_plugin_modification_time(plugin_config, path);
		}
	}

	return plugin_config;
}

<<<<<<< HEAD
static inline String get_plugins_binaries(String binary_type, Vector<PluginConfig> plugins_configs) {
	String plugins_binaries;
	if (!plugins_configs.empty()) {
		Vector<String> binaries;
		for (int i = 0; i < plugins_configs.size(); i++) {
			PluginConfig config = plugins_configs[i];
=======
static inline String get_plugins_binaries(String binary_type, Vector<PluginConfigAndroid> plugins_configs) {
	String plugins_binaries;
	if (!plugins_configs.is_empty()) {
		Vector<String> binaries;
		for (int i = 0; i < plugins_configs.size(); i++) {
			PluginConfigAndroid config = plugins_configs[i];
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			if (!config.valid_config) {
				continue;
			}

			if (config.binary_type == binary_type) {
				binaries.push_back(config.binary);
			}

<<<<<<< HEAD
			if (binary_type == BINARY_TYPE_LOCAL) {
				binaries.append_array(config.local_dependencies);
			}

			if (binary_type == BINARY_TYPE_REMOTE) {
=======
			if (binary_type == PluginConfigAndroid::BINARY_TYPE_LOCAL) {
				binaries.append_array(config.local_dependencies);
			}

			if (binary_type == PluginConfigAndroid::BINARY_TYPE_REMOTE) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				binaries.append_array(config.remote_dependencies);
			}
		}

<<<<<<< HEAD
		plugins_binaries = String(PLUGIN_VALUE_SEPARATOR).join(binaries);
=======
		plugins_binaries = String(PluginConfigAndroid::PLUGIN_VALUE_SEPARATOR).join(binaries);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	}

	return plugins_binaries;
}

<<<<<<< HEAD
static inline String get_plugins_custom_maven_repos(Vector<PluginConfig> plugins_configs) {
	String custom_maven_repos;
	if (!plugins_configs.empty()) {
		Vector<String> repos_urls;
		for (int i = 0; i < plugins_configs.size(); i++) {
			PluginConfig config = plugins_configs[i];
=======
static inline String get_plugins_custom_maven_repos(Vector<PluginConfigAndroid> plugins_configs) {
	String custom_maven_repos;
	if (!plugins_configs.is_empty()) {
		Vector<String> repos_urls;
		for (int i = 0; i < plugins_configs.size(); i++) {
			PluginConfigAndroid config = plugins_configs[i];
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			if (!config.valid_config) {
				continue;
			}

			repos_urls.append_array(config.custom_maven_repos);
		}

<<<<<<< HEAD
		custom_maven_repos = String(PLUGIN_VALUE_SEPARATOR).join(repos_urls);
=======
		custom_maven_repos = String(PluginConfigAndroid::PLUGIN_VALUE_SEPARATOR).join(repos_urls);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	}
	return custom_maven_repos;
}

<<<<<<< HEAD
static inline String get_plugins_names(Vector<PluginConfig> plugins_configs) {
	String plugins_names;
	if (!plugins_configs.empty()) {
		Vector<String> names;
		for (int i = 0; i < plugins_configs.size(); i++) {
			PluginConfig config = plugins_configs[i];
=======
static inline String get_plugins_names(Vector<PluginConfigAndroid> plugins_configs) {
	String plugins_names;
	if (!plugins_configs.is_empty()) {
		Vector<String> names;
		for (int i = 0; i < plugins_configs.size(); i++) {
			PluginConfigAndroid config = plugins_configs[i];
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			if (!config.valid_config) {
				continue;
			}

			names.push_back(config.name);
		}
<<<<<<< HEAD
		plugins_names = String(PLUGIN_VALUE_SEPARATOR).join(names);
=======
		plugins_names = String(PluginConfigAndroid::PLUGIN_VALUE_SEPARATOR).join(names);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	}

	return plugins_names;
}

#endif // GODOT_PLUGIN_CONFIG_H
