/*************************************************************************/
/*  jni_singleton.h                                                      */
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

#ifndef JNI_SINGLETON_H
#define JNI_SINGLETON_H

<<<<<<< HEAD
#include <core/engine.h>
#include <core/variant.h>
=======
#include <core/config/engine.h>
#include <core/variant/variant.h>
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
#ifdef ANDROID_ENABLED
#include <platform/android/jni_utils.h>
#endif

class JNISingleton : public Object {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	GDCLASS(JNISingleton, Object);

#ifdef ANDROID_ENABLED
	struct MethodData {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		jmethodID method;
		Variant::Type ret_type;
		Vector<Variant::Type> argtypes;
	};

	jobject instance;
	Map<StringName, MethodData> method_map;
#endif

public:
<<<<<<< HEAD
	virtual Variant call(const StringName &p_method, const Variant **p_args, int p_argcount, Variant::CallError &r_error) {
=======
	virtual Variant call(const StringName &p_method, const Variant **p_args, int p_argcount, Callable::CallError &r_error) override {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
#ifdef ANDROID_ENABLED
		Map<StringName, MethodData>::Element *E = method_map.find(p_method);

		// Check the method we're looking for is in the JNISingleton map and that
		// the arguments match.
		bool call_error = !E || E->get().argtypes.size() != p_argcount;
		if (!call_error) {
			for (int i = 0; i < p_argcount; i++) {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				if (!Variant::can_convert(p_args[i]->get_type(), E->get().argtypes[i])) {
					call_error = true;
					break;
				}
			}
		}

		if (call_error) {
			// The method is not in this map, defaulting to the regular instance calls.
			return Object::call(p_method, p_args, p_argcount, r_error);
		}

		ERR_FAIL_COND_V(!instance, Variant());

<<<<<<< HEAD
		r_error.error = Variant::CallError::CALL_OK;

		jvalue *v = NULL;

		if (p_argcount) {

			v = (jvalue *)alloca(sizeof(jvalue) * p_argcount);
		}

		JNIEnv *env = ThreadAndroid::get_env();
=======
		r_error.error = Callable::CallError::CALL_OK;

		jvalue *v = nullptr;

		if (p_argcount) {
			v = (jvalue *)alloca(sizeof(jvalue) * p_argcount);
		}

		JNIEnv *env = get_jni_env();
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

		int res = env->PushLocalFrame(16);

		ERR_FAIL_COND_V(res != 0, Variant());

		List<jobject> to_erase;
		for (int i = 0; i < p_argcount; i++) {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			jvalret vr = _variant_to_jvalue(env, E->get().argtypes[i], p_args[i]);
			v[i] = vr.val;
			if (vr.obj)
				to_erase.push_back(vr.obj);
		}

		Variant ret;

		switch (E->get().ret_type) {
<<<<<<< HEAD

			case Variant::NIL: {

				env->CallVoidMethodA(instance, E->get().method, v);
			} break;
			case Variant::BOOL: {

				ret = env->CallBooleanMethodA(instance, E->get().method, v) == JNI_TRUE;
			} break;
			case Variant::INT: {

				ret = env->CallIntMethodA(instance, E->get().method, v);
			} break;
			case Variant::REAL: {

				ret = env->CallFloatMethodA(instance, E->get().method, v);
			} break;
			case Variant::STRING: {

=======
			case Variant::NIL: {
				env->CallVoidMethodA(instance, E->get().method, v);
			} break;
			case Variant::BOOL: {
				ret = env->CallBooleanMethodA(instance, E->get().method, v) == JNI_TRUE;
			} break;
			case Variant::INT: {
				ret = env->CallIntMethodA(instance, E->get().method, v);
			} break;
			case Variant::FLOAT: {
				ret = env->CallFloatMethodA(instance, E->get().method, v);
			} break;
			case Variant::STRING: {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				jobject o = env->CallObjectMethodA(instance, E->get().method, v);
				ret = jstring_to_string((jstring)o, env);
				env->DeleteLocalRef(o);
			} break;
<<<<<<< HEAD
			case Variant::POOL_STRING_ARRAY: {

=======
			case Variant::PACKED_STRING_ARRAY: {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				jobjectArray arr = (jobjectArray)env->CallObjectMethodA(instance, E->get().method, v);

				ret = _jobject_to_variant(env, arr);

				env->DeleteLocalRef(arr);
			} break;
<<<<<<< HEAD
			case Variant::POOL_INT_ARRAY: {

				jintArray arr = (jintArray)env->CallObjectMethodA(instance, E->get().method, v);

				int fCount = env->GetArrayLength(arr);
				PoolVector<int> sarr;
				sarr.resize(fCount);

				PoolVector<int>::Write w = sarr.write();
				env->GetIntArrayRegion(arr, 0, fCount, w.ptr());
				w.release();
				ret = sarr;
				env->DeleteLocalRef(arr);
			} break;
			case Variant::POOL_REAL_ARRAY: {

				jfloatArray arr = (jfloatArray)env->CallObjectMethodA(instance, E->get().method, v);

				int fCount = env->GetArrayLength(arr);
				PoolVector<float> sarr;
				sarr.resize(fCount);

				PoolVector<float>::Write w = sarr.write();
				env->GetFloatArrayRegion(arr, 0, fCount, w.ptr());
				w.release();
=======
			case Variant::PACKED_INT32_ARRAY: {
				jintArray arr = (jintArray)env->CallObjectMethodA(instance, E->get().method, v);

				int fCount = env->GetArrayLength(arr);
				Vector<int> sarr;
				sarr.resize(fCount);

				int *w = sarr.ptrw();
				env->GetIntArrayRegion(arr, 0, fCount, w);
				ret = sarr;
				env->DeleteLocalRef(arr);
			} break;
			case Variant::PACKED_FLOAT32_ARRAY: {
				jfloatArray arr = (jfloatArray)env->CallObjectMethodA(instance, E->get().method, v);

				int fCount = env->GetArrayLength(arr);
				Vector<float> sarr;
				sarr.resize(fCount);

				float *w = sarr.ptrw();
				env->GetFloatArrayRegion(arr, 0, fCount, w);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				ret = sarr;
				env->DeleteLocalRef(arr);
			} break;

<<<<<<< HEAD
			case Variant::DICTIONARY: {

=======
#ifndef _MSC_VER
#warning This is missing 64 bits arrays, I have no idea how to do it in JNI
#endif
			case Variant::DICTIONARY: {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				jobject obj = env->CallObjectMethodA(instance, E->get().method, v);
				ret = _jobject_to_variant(env, obj);
				env->DeleteLocalRef(obj);

			} break;
			default: {
<<<<<<< HEAD

				env->PopLocalFrame(NULL);
=======
				env->PopLocalFrame(nullptr);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				ERR_FAIL_V(Variant());
			} break;
		}

		while (to_erase.size()) {
			env->DeleteLocalRef(to_erase.front()->get());
			to_erase.pop_front();
		}

<<<<<<< HEAD
		env->PopLocalFrame(NULL);
=======
		env->PopLocalFrame(nullptr);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

		return ret;
#else // ANDROID_ENABLED

		// Defaulting to the regular instance calls.
		return Object::call(p_method, p_args, p_argcount, r_error);
#endif
	}

#ifdef ANDROID_ENABLED
	jobject get_instance() const {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		return instance;
	}

	void set_instance(jobject p_instance) {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		instance = p_instance;
	}

	void add_method(const StringName &p_name, jmethodID p_method, const Vector<Variant::Type> &p_args, Variant::Type p_ret_type) {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		MethodData md;
		md.method = p_method;
		md.argtypes = p_args;
		md.ret_type = p_ret_type;
		method_map[p_name] = md;
	}

	void add_signal(const StringName &p_name, const Vector<Variant::Type> &p_args) {
		if (p_args.size() == 0)
			ADD_SIGNAL(MethodInfo(p_name));
		else if (p_args.size() == 1)
			ADD_SIGNAL(MethodInfo(p_name, PropertyInfo(p_args[0], "arg1")));
		else if (p_args.size() == 2)
			ADD_SIGNAL(MethodInfo(p_name, PropertyInfo(p_args[0], "arg1"), PropertyInfo(p_args[1], "arg2")));
		else if (p_args.size() == 3)
			ADD_SIGNAL(MethodInfo(p_name, PropertyInfo(p_args[0], "arg1"), PropertyInfo(p_args[1], "arg2"), PropertyInfo(p_args[2], "arg3")));
		else if (p_args.size() == 4)
			ADD_SIGNAL(MethodInfo(p_name, PropertyInfo(p_args[0], "arg1"), PropertyInfo(p_args[1], "arg2"), PropertyInfo(p_args[2], "arg3"), PropertyInfo(p_args[3], "arg4")));
		else if (p_args.size() == 5)
			ADD_SIGNAL(MethodInfo(p_name, PropertyInfo(p_args[0], "arg1"), PropertyInfo(p_args[1], "arg2"), PropertyInfo(p_args[2], "arg3"), PropertyInfo(p_args[3], "arg4"), PropertyInfo(p_args[4], "arg5")));
	}

#endif

	JNISingleton() {
#ifdef ANDROID_ENABLED
<<<<<<< HEAD
		instance = NULL;
=======
		instance = nullptr;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
#endif
	}
};

#endif // JNI_SINGLETON_H
