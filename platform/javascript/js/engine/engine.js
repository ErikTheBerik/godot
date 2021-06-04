<<<<<<< HEAD
const Engine = (function () {
	const preloader = new Preloader();

	let wasmExt = '.wasm';
	let unloadAfterInit = true;
	let loadPath = '';
	let loadPromise = null;
	let initPromise = null;
	let stderr = null;
	let stdout = null;
	let progressFunc = null;

	function load(basePath) {
		if (loadPromise == null) {
			loadPath = basePath;
			loadPromise = preloader.loadPromise(basePath + wasmExt);
			preloader.setProgressFunc(progressFunc);
			requestAnimationFrame(preloader.animateProgress);
		}
		return loadPromise;
	}

	function unload() {
		loadPromise = null;
	}

	/** @constructor */
	function Engine() { // eslint-disable-line no-shadow
		this.canvas = null;
		this.executableName = '';
		this.rtenv = null;
		this.customLocale = null;
		this.resizeCanvasOnStart = false;
		this.onExecute = null;
		this.onExit = null;
		this.persistentPaths = ['/userfs'];
	}

	Engine.prototype.init = /** @param {string=} basePath */ function (basePath) {
		if (initPromise) {
			return initPromise;
		}
		if (loadPromise == null) {
			if (!basePath) {
				initPromise = Promise.reject(new Error('A base path must be provided when calling `init` and the engine is not loaded.'));
				return initPromise;
			}
			load(basePath);
		}
		let config = {};
		if (typeof stdout === 'function') {
			config.print = stdout;
		}
		if (typeof stderr === 'function') {
			config.printErr = stderr;
		}
		const me = this;
		initPromise = new Promise(function (resolve, reject) {
			config['locateFile'] = Utils.createLocateRewrite(loadPath);
			config['instantiateWasm'] = Utils.createInstantiatePromise(loadPromise);
			Godot(config).then(function (module) {
				module['initFS'](me.persistentPaths).then(function (fs_err) {
					me.rtenv = module;
					if (unloadAfterInit) {
						unload();
					}
					resolve();
					config = null;
				});
			});
		});
		return initPromise;
	};

	/** @type {function(string, string):Object} */
	Engine.prototype.preloadFile = function (file, path) {
		return preloader.preload(file, path);
	};

	/** @type {function(...string):Object} */
	Engine.prototype.start = function () {
		// Start from arguments.
		const args = [];
		for (let i = 0; i < arguments.length; i++) {
			args.push(arguments[i]);
		}
		const me = this;
		return me.init().then(function () {
			if (!me.rtenv) {
				return Promise.reject(new Error('The engine must be initialized before it can be started'));
			}

			if (!(me.canvas instanceof HTMLCanvasElement)) {
				me.canvas = Utils.findCanvas();
				if (!me.canvas) {
					return Promise.reject(new Error('No canvas found in page'));
				}
			}

			// Canvas can grab focus on click, or key events won't work.
			if (me.canvas.tabIndex < 0) {
				me.canvas.tabIndex = 0;
			}

			// Disable right-click context menu.
			me.canvas.addEventListener('contextmenu', function (ev) {
				ev.preventDefault();
			}, false);

			// Until context restoration is implemented warn the user of context loss.
			me.canvas.addEventListener('webglcontextlost', function (ev) {
				alert('WebGL context lost, please reload the page'); // eslint-disable-line no-alert
				ev.preventDefault();
			}, false);

			// Browser locale, or custom one if defined.
			let locale = me.customLocale;
			if (!locale) {
				locale = navigator.languages ? navigator.languages[0] : navigator.language;
				locale = locale.split('.')[0];
			}
			// Emscripten configuration.
			me.rtenv['thisProgram'] = me.executableName;
			me.rtenv['noExitRuntime'] = true;
			// Godot configuration.
			me.rtenv['initConfig']({
				'resizeCanvasOnStart': me.resizeCanvasOnStart,
				'canvas': me.canvas,
				'locale': locale,
				'onExecute': function (p_args) {
					if (me.onExecute) {
						me.onExecute(p_args);
						return 0;
					}
					return 1;
				},
				'onExit': function (p_code) {
					me.rtenv['deinitFS']();
					if (me.onExit) {
						me.onExit(p_code);
					}
					me.rtenv = null;
				},
			});

			return new Promise(function (resolve, reject) {
				preloader.preloadedFiles.forEach(function (file) {
					me.rtenv['copyToFS'](file.path, file.buffer);
				});
				preloader.preloadedFiles.length = 0; // Clear memory
				me.rtenv['callMain'](args);
				initPromise = null;
				resolve();
			});
		});
	};

	Engine.prototype.startGame = function (execName, mainPack, extraArgs) {
		// Start and init with execName as loadPath if not inited.
		this.executableName = execName;
		const me = this;
		return Promise.all([
			this.init(execName),
			this.preloadFile(mainPack, mainPack),
		]).then(function () {
			let args = ['--main-pack', mainPack];
			if (extraArgs) {
				args = args.concat(extraArgs);
			}
			return me.start.apply(me, args);
		});
	};

	Engine.prototype.setWebAssemblyFilenameExtension = function (override) {
		if (String(override).length === 0) {
			throw new Error('Invalid WebAssembly filename extension override');
		}
		wasmExt = String(override);
	};

	Engine.prototype.setUnloadAfterInit = function (enabled) {
		unloadAfterInit = enabled;
	};

	Engine.prototype.setCanvas = function (canvasElem) {
		this.canvas = canvasElem;
	};

	Engine.prototype.setCanvasResizedOnStart = function (enabled) {
		this.resizeCanvasOnStart = enabled;
	};

	Engine.prototype.setLocale = function (locale) {
		this.customLocale = locale;
	};

	Engine.prototype.setExecutableName = function (newName) {
		this.executableName = newName;
	};

	Engine.prototype.setProgressFunc = function (func) {
		progressFunc = func;
	};

	Engine.prototype.setStdoutFunc = function (func) {
		const print = function (text) {
			let msg = text;
			if (arguments.length > 1) {
				msg = Array.prototype.slice.call(arguments).join(' ');
			}
			func(msg);
		};
		if (this.rtenv) {
			this.rtenv.print = print;
		}
		stdout = print;
	};

	Engine.prototype.setStderrFunc = function (func) {
		const printErr = function (text) {
			let msg = text;
			if (arguments.length > 1) {
				msg = Array.prototype.slice.call(arguments).join(' ');
			}
			func(msg);
		};
		if (this.rtenv) {
			this.rtenv.printErr = printErr;
		}
		stderr = printErr;
	};

	Engine.prototype.setOnExecute = function (onExecute) {
		this.onExecute = onExecute;
	};

	Engine.prototype.setOnExit = function (onExit) {
		this.onExit = onExit;
	};

	Engine.prototype.copyToFS = function (path, buffer) {
		if (this.rtenv == null) {
			throw new Error('Engine must be inited before copying files');
		}
		this.rtenv['copyToFS'](path, buffer);
	};

	Engine.prototype.setPersistentPaths = function (persistentPaths) {
		this.persistentPaths = persistentPaths;
	};

	Engine.prototype.requestQuit = function () {
		if (this.rtenv) {
			this.rtenv['request_quit']();
		}
	};

	// Closure compiler exported engine methods.
	/** @export */
	Engine['isWebGLAvailable'] = Utils.isWebGLAvailable;
	Engine['load'] = load;
	Engine['unload'] = unload;
	Engine.prototype['init'] = Engine.prototype.init;
	Engine.prototype['preloadFile'] = Engine.prototype.preloadFile;
	Engine.prototype['start'] = Engine.prototype.start;
	Engine.prototype['startGame'] = Engine.prototype.startGame;
	Engine.prototype['setWebAssemblyFilenameExtension'] = Engine.prototype.setWebAssemblyFilenameExtension;
	Engine.prototype['setUnloadAfterInit'] = Engine.prototype.setUnloadAfterInit;
	Engine.prototype['setCanvas'] = Engine.prototype.setCanvas;
	Engine.prototype['setCanvasResizedOnStart'] = Engine.prototype.setCanvasResizedOnStart;
	Engine.prototype['setLocale'] = Engine.prototype.setLocale;
	Engine.prototype['setExecutableName'] = Engine.prototype.setExecutableName;
	Engine.prototype['setProgressFunc'] = Engine.prototype.setProgressFunc;
	Engine.prototype['setStdoutFunc'] = Engine.prototype.setStdoutFunc;
	Engine.prototype['setStderrFunc'] = Engine.prototype.setStderrFunc;
	Engine.prototype['setOnExecute'] = Engine.prototype.setOnExecute;
	Engine.prototype['setOnExit'] = Engine.prototype.setOnExit;
	Engine.prototype['copyToFS'] = Engine.prototype.copyToFS;
	Engine.prototype['setPersistentPaths'] = Engine.prototype.setPersistentPaths;
	Engine.prototype['requestQuit'] = Engine.prototype.requestQuit;
	return Engine;
=======
/**
 * Projects exported for the Web expose the :js:class:`Engine` class to the JavaScript environment, that allows
 * fine control over the engine's start-up process.
 *
 * This API is built in an asynchronous manner and requires basic understanding
 * of `Promises <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Using_promises>`__.
 *
 * @module Engine
 * @header HTML5 shell class reference
 */
const Engine = (function () {
	const preloader = new Preloader();

	let loadPromise = null;
	let loadPath = '';
	let initPromise = null;

	/**
	 * @classdesc The ``Engine`` class provides methods for loading and starting exported projects on the Web. For default export
	 * settings, this is already part of the exported HTML page. To understand practical use of the ``Engine`` class,
	 * see :ref:`Custom HTML page for Web export <doc_customizing_html5_shell>`.
	 *
	 * @description Create a new Engine instance with the given configuration.
	 *
	 * @global
	 * @constructor
	 * @param {EngineConfig} initConfig The initial config for this instance.
	 */
	function Engine(initConfig) { // eslint-disable-line no-shadow
		this.config = new InternalConfig(initConfig);
		this.rtenv = null;
	}

	/**
	 * Load the engine from the specified base path.
	 *
	 * @param {string} basePath Base path of the engine to load.
	 * @param {number=} [size=0] The file size if known.
	 * @returns {Promise} A Promise that resolves once the engine is loaded.
	 *
	 * @function Engine.load
	 */
	Engine.load = function (basePath, size) {
		if (loadPromise == null) {
			loadPath = basePath;
			loadPromise = preloader.loadPromise(`${loadPath}.wasm`, size, true);
			requestAnimationFrame(preloader.animateProgress);
		}
		return loadPromise;
	};

	/**
	 * Unload the engine to free memory.
	 *
	 * This method will be called automatically depending on the configuration. See :js:attr:`unloadAfterInit`.
	 *
	 * @function Engine.unload
	 */
	Engine.unload = function () {
		loadPromise = null;
	};

	/**
	 * Check whether WebGL is available. Optionally, specify a particular version of WebGL to check for.
	 *
	 * @param {number=} [majorVersion=1] The major WebGL version to check for.
	 * @returns {boolean} If the given major version of WebGL is available.
	 * @function Engine.isWebGLAvailable
	 */
	Engine.isWebGLAvailable = function (majorVersion = 1) {
		try {
			return !!document.createElement('canvas').getContext(['webgl', 'webgl2'][majorVersion - 1]);
		} catch (e) { /* Not available */ }
		return false;
	};

	/**
	 * Safe Engine constructor, creates a new prototype for every new instance to avoid prototype pollution.
	 * @ignore
	 * @constructor
	 */
	function SafeEngine(initConfig) {
		const proto = /** @lends Engine.prototype */ {
			/**
			 * Initialize the engine instance. Optionally, pass the base path to the engine to load it,
			 * if it hasn't been loaded yet. See :js:meth:`Engine.load`.
			 *
			 * @param {string=} basePath Base path of the engine to load.
			 * @return {Promise} A ``Promise`` that resolves once the engine is loaded and initialized.
			 */
			init: function (basePath) {
				if (initPromise) {
					return initPromise;
				}
				if (loadPromise == null) {
					if (!basePath) {
						initPromise = Promise.reject(new Error('A base path must be provided when calling `init` and the engine is not loaded.'));
						return initPromise;
					}
					Engine.load(basePath, this.config.fileSizes[`${basePath}.wasm`]);
				}
				const me = this;
				function doInit(promise) {
					// Care! Promise chaining is bogus with old emscripten versions.
					// This caused a regression with the Mono build (which uses an older emscripten version).
					// Make sure to test that when refactoring.
					return new Promise(function (resolve, reject) {
						promise.then(function (response) {
							const cloned = new Response(response.clone().body, { 'headers': [['content-type', 'application/wasm']] });
							Godot(me.config.getModuleConfig(loadPath, cloned)).then(function (module) {
								const paths = me.config.persistentPaths;
								module['initFS'](paths).then(function (err) {
									me.rtenv = module;
									if (me.config.unloadAfterInit) {
										Engine.unload();
									}
									resolve();
								});
							});
						});
					});
				}
				preloader.setProgressFunc(this.config.onProgress);
				initPromise = doInit(loadPromise);
				return initPromise;
			},

			/**
			 * Load a file so it is available in the instance's file system once it runs. Must be called **before** starting the
			 * instance.
			 *
			 * If not provided, the ``path`` is derived from the URL of the loaded file.
			 *
			 * @param {string|ArrayBuffer} file The file to preload.
			 *
			 * If a ``string`` the file will be loaded from that path.
			 *
			 * If an ``ArrayBuffer`` or a view on one, the buffer will used as the content of the file.
			 *
			 * @param {string=} path Path by which the file will be accessible. Required, if ``file`` is not a string.
			 *
			 * @returns {Promise} A Promise that resolves once the file is loaded.
			 */
			preloadFile: function (file, path) {
				return preloader.preload(file, path, this.config.fileSizes[file]);
			},

			/**
			 * Start the engine instance using the given override configuration (if any).
			 * :js:meth:`startGame <Engine.prototype.startGame>` can be used in typical cases instead.
			 *
			 * This will initialize the instance if it is not initialized. For manual initialization, see :js:meth:`init <Engine.prototype.init>`.
			 * The engine must be loaded beforehand.
			 *
			 * Fails if a canvas cannot be found on the page, or not specified in the configuration.
			 *
			 * @param {EngineConfig} override An optional configuration override.
			 * @return {Promise} Promise that resolves once the engine started.
			 */
			start: function (override) {
				this.config.update(override);
				const me = this;
				return me.init().then(function () {
					if (!me.rtenv) {
						return Promise.reject(new Error('The engine must be initialized before it can be started'));
					}

					let config = {};
					try {
						config = me.config.getGodotConfig(function () {
							me.rtenv = null;
						});
					} catch (e) {
						return Promise.reject(e);
					}
					// Godot configuration.
					me.rtenv['initConfig'](config);

					// Preload GDNative libraries.
					const libs = [];
					me.config.gdnativeLibs.forEach(function (lib) {
						libs.push(me.rtenv['loadDynamicLibrary'](lib, { 'loadAsync': true }));
					});
					return Promise.all(libs).then(function () {
						return new Promise(function (resolve, reject) {
							preloader.preloadedFiles.forEach(function (file) {
								me.rtenv['copyToFS'](file.path, file.buffer);
							});
							preloader.preloadedFiles.length = 0; // Clear memory
							me.rtenv['callMain'](me.config.args);
							initPromise = null;
							resolve();
						});
					});
				});
			},

			/**
			 * Start the game instance using the given configuration override (if any).
			 *
			 * This will initialize the instance if it is not initialized. For manual initialization, see :js:meth:`init <Engine.prototype.init>`.
			 *
			 * This will load the engine if it is not loaded, and preload the main pck.
			 *
			 * This method expects the initial config (or the override) to have both the :js:attr:`executable` and :js:attr:`mainPack`
			 * properties set (normally done by the editor during export).
			 *
			 * @param {EngineConfig} override An optional configuration override.
			 * @return {Promise} Promise that resolves once the game started.
			 */
			startGame: function (override) {
				this.config.update(override);
				// Add main-pack argument.
				const exe = this.config.executable;
				const pack = this.config.mainPack || `${exe}.pck`;
				this.config.args = ['--main-pack', pack].concat(this.config.args);
				// Start and init with execName as loadPath if not inited.
				const me = this;
				return Promise.all([
					this.init(exe),
					this.preloadFile(pack, pack),
				]).then(function () {
					return me.start.apply(me);
				});
			},

			/**
			 * Create a file at the specified ``path`` with the passed as ``buffer`` in the instance's file system.
			 *
			 * @param {string} path The location where the file will be created.
			 * @param {ArrayBuffer} buffer The content of the file.
			 */
			copyToFS: function (path, buffer) {
				if (this.rtenv == null) {
					throw new Error('Engine must be inited before copying files');
				}
				this.rtenv['copyToFS'](path, buffer);
			},

			/**
			 * Request that the current instance quit.
			 *
			 * This is akin the user pressing the close button in the window manager, and will
			 * have no effect if the engine has crashed, or is stuck in a loop.
			 *
			 */
			requestQuit: function () {
				if (this.rtenv) {
					this.rtenv['request_quit']();
				}
			},
		};

		Engine.prototype = proto;
		// Closure compiler exported instance methods.
		Engine.prototype['init'] = Engine.prototype.init;
		Engine.prototype['preloadFile'] = Engine.prototype.preloadFile;
		Engine.prototype['start'] = Engine.prototype.start;
		Engine.prototype['startGame'] = Engine.prototype.startGame;
		Engine.prototype['copyToFS'] = Engine.prototype.copyToFS;
		Engine.prototype['requestQuit'] = Engine.prototype.requestQuit;
		// Also expose static methods as instance methods
		Engine.prototype['load'] = Engine.load;
		Engine.prototype['unload'] = Engine.unload;
		Engine.prototype['isWebGLAvailable'] = Engine.isWebGLAvailable;
		return new Engine(initConfig);
	}

	// Closure compiler exported static methods.
	SafeEngine['load'] = Engine.load;
	SafeEngine['unload'] = Engine.unload;
	SafeEngine['isWebGLAvailable'] = Engine.isWebGLAvailable;

	return SafeEngine;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
}());
if (typeof window !== 'undefined') {
	window['Engine'] = Engine;
}
