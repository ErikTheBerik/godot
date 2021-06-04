const Preloader = /** @constructor */ function () { // eslint-disable-line no-unused-vars
<<<<<<< HEAD
	const loadXHR = function (resolve, reject, file, tracker, attempts) {
		const xhr = new XMLHttpRequest();
		tracker[file] = {
			total: 0,
			loaded: 0,
			final: false,
		};
		xhr.onerror = function () {
			if (attempts <= 1) {
				reject(new Error(`Failed loading file '${file}'`));
			} else {
				setTimeout(function () {
					loadXHR(resolve, reject, file, tracker, attempts - 1);
				}, 1000);
			}
		};
		xhr.onabort = function () {
			tracker[file].final = true;
			reject(new Error(`Loading file '${file}' was aborted.`));
		};
		xhr.onloadstart = function (ev) {
			tracker[file].total = ev.total;
			tracker[file].loaded = ev.loaded;
		};
		xhr.onprogress = function (ev) {
			tracker[file].loaded = ev.loaded;
			tracker[file].total = ev.total;
		};
		xhr.onload = function () {
			if (xhr.status >= 400) {
				if (xhr.status < 500 || attempts <= 1) {
					reject(new Error(`Failed loading file '${file}': ${xhr.statusText}`));
					xhr.abort();
				} else {
					setTimeout(function () {
						loadXHR(resolve, reject, file, tracker, attempts - 1);
					}, 1000);
				}
			} else {
				tracker[file].final = true;
				resolve(xhr);
			}
		};
		// Make request.
		xhr.open('GET', file);
		if (!file.endsWith('.js')) {
			xhr.responseType = 'arraybuffer';
		}
		xhr.send();
	};
=======
	function getTrackedResponse(response, load_status) {
		function onloadprogress(reader, controller) {
			return reader.read().then(function (result) {
				if (load_status.done) {
					return Promise.resolve();
				}
				if (result.value) {
					controller.enqueue(result.value);
					load_status.loaded += result.value.length;
				}
				if (!result.done) {
					return onloadprogress(reader, controller);
				}
				load_status.done = true;
				return Promise.resolve();
			});
		}
		const reader = response.body.getReader();
		return new Response(new ReadableStream({
			start: function (controller) {
				onloadprogress(reader, controller).then(function () {
					controller.close();
				});
			},
		}), { headers: response.headers });
	}

	function loadFetch(file, tracker, fileSize, raw) {
		tracker[file] = {
			total: fileSize || 0,
			loaded: 0,
			done: false,
		};
		return fetch(file).then(function (response) {
			if (!response.ok) {
				return Promise.reject(new Error(`Failed loading file '${file}'`));
			}
			const tr = getTrackedResponse(response, tracker[file]);
			if (raw) {
				return Promise.resolve(tr);
			}
			return tr.arrayBuffer();
		});
	}

	function retry(func, attempts = 1) {
		function onerror(err) {
			if (attempts <= 1) {
				return Promise.reject(err);
			}
			return new Promise(function (resolve, reject) {
				setTimeout(function () {
					retry(func, attempts - 1).then(resolve).catch(reject);
				}, 1000);
			});
		}
		return func().catch(onerror);
	}
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	const DOWNLOAD_ATTEMPTS_MAX = 4;
	const loadingFiles = {};
	const lastProgress = { loaded: 0, total: 0 };
	let progressFunc = null;

	const animateProgress = function () {
		let loaded = 0;
		let total = 0;
		let totalIsValid = true;
		let progressIsFinal = true;

		Object.keys(loadingFiles).forEach(function (file) {
			const stat = loadingFiles[file];
<<<<<<< HEAD
			if (!stat.final) {
=======
			if (!stat.done) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				progressIsFinal = false;
			}
			if (!totalIsValid || stat.total === 0) {
				totalIsValid = false;
				total = 0;
			} else {
				total += stat.total;
			}
			loaded += stat.loaded;
		});
		if (loaded !== lastProgress.loaded || total !== lastProgress.total) {
			lastProgress.loaded = loaded;
			lastProgress.total = total;
			if (typeof progressFunc === 'function') {
				progressFunc(loaded, total);
			}
		}
		if (!progressIsFinal) {
			requestAnimationFrame(animateProgress);
		}
	};

	this.animateProgress = animateProgress;

	this.setProgressFunc = function (callback) {
		progressFunc = callback;
	};

<<<<<<< HEAD
	this.loadPromise = function (file) {
		return new Promise(function (resolve, reject) {
			loadXHR(resolve, reject, file, loadingFiles, DOWNLOAD_ATTEMPTS_MAX);
		});
	};

	this.preloadedFiles = [];
	this.preload = function (pathOrBuffer, destPath) {
		let buffer = null;
		if (typeof pathOrBuffer === 'string') {
			const me = this;
			return this.loadPromise(pathOrBuffer).then(function (xhr) {
				me.preloadedFiles.push({
					path: destPath || pathOrBuffer,
					buffer: xhr.response,
=======
	this.loadPromise = function (file, fileSize, raw = false) {
		return retry(loadFetch.bind(null, file, loadingFiles, fileSize, raw), DOWNLOAD_ATTEMPTS_MAX);
	};

	this.preloadedFiles = [];
	this.preload = function (pathOrBuffer, destPath, fileSize) {
		let buffer = null;
		if (typeof pathOrBuffer === 'string') {
			const me = this;
			return this.loadPromise(pathOrBuffer, fileSize).then(function (buf) {
				me.preloadedFiles.push({
					path: destPath || pathOrBuffer,
					buffer: buf,
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				});
				return Promise.resolve();
			});
		} else if (pathOrBuffer instanceof ArrayBuffer) {
			buffer = new Uint8Array(pathOrBuffer);
		} else if (ArrayBuffer.isView(pathOrBuffer)) {
			buffer = new Uint8Array(pathOrBuffer.buffer);
		}
		if (buffer) {
			this.preloadedFiles.push({
				path: destPath,
				buffer: pathOrBuffer,
			});
			return Promise.resolve();
		}
		return Promise.reject(new Error('Invalid object for preloading'));
	};
};
