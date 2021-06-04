/*************************************************************************/
/*  jni_utils.cpp                                                        */
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

#include "jni_utils.h"

jvalret _variant_to_jvalue(JNIEnv *env, Variant::Type p_type, const Variant *p_arg, bool force_jobject) {
<<<<<<< HEAD

	jvalret v;

	switch (p_type) {

		case Variant::BOOL: {

=======
	jvalret v;

	switch (p_type) {
		case Variant::BOOL: {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			if (force_jobject) {
				jclass bclass = env->FindClass("java/lang/Boolean");
				jmethodID ctor = env->GetMethodID(bclass, "<init>", "(Z)V");
				jvalue val;
				val.z = (bool)(*p_arg);
				jobject obj = env->NewObjectA(bclass, ctor, &val);
				v.val.l = obj;
				v.obj = obj;
				env->DeleteLocalRef(bclass);
			} else {
				v.val.z = *p_arg;
			};
		} break;
		case Variant::INT: {
<<<<<<< HEAD

			if (force_jobject) {

=======
			if (force_jobject) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				jclass bclass = env->FindClass("java/lang/Integer");
				jmethodID ctor = env->GetMethodID(bclass, "<init>", "(I)V");
				jvalue val;
				val.i = (int)(*p_arg);
				jobject obj = env->NewObjectA(bclass, ctor, &val);
				v.val.l = obj;
				v.obj = obj;
				env->DeleteLocalRef(bclass);

			} else {
				v.val.i = *p_arg;
			};
		} break;
<<<<<<< HEAD
		case Variant::REAL: {

			if (force_jobject) {

=======
		case Variant::FLOAT: {
			if (force_jobject) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				jclass bclass = env->FindClass("java/lang/Double");
				jmethodID ctor = env->GetMethodID(bclass, "<init>", "(D)V");
				jvalue val;
				val.d = (double)(*p_arg);
				jobject obj = env->NewObjectA(bclass, ctor, &val);
				v.val.l = obj;
				v.obj = obj;
				env->DeleteLocalRef(bclass);

			} else {
				v.val.f = *p_arg;
			};
		} break;
		case Variant::STRING: {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			String s = *p_arg;
			jstring jStr = env->NewStringUTF(s.utf8().get_data());
			v.val.l = jStr;
			v.obj = jStr;
		} break;
<<<<<<< HEAD
		case Variant::POOL_STRING_ARRAY: {

			PoolVector<String> sarray = *p_arg;
			jobjectArray arr = env->NewObjectArray(sarray.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));

			for (int j = 0; j < sarray.size(); j++) {

=======
		case Variant::PACKED_STRING_ARRAY: {
			Vector<String> sarray = *p_arg;
			jobjectArray arr = env->NewObjectArray(sarray.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));

			for (int j = 0; j < sarray.size(); j++) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
				jstring str = env->NewStringUTF(sarray[j].utf8().get_data());
				env->SetObjectArrayElement(arr, j, str);
				env->DeleteLocalRef(str);
			}
			v.val.l = arr;
			v.obj = arr;

		} break;

		case Variant::DICTIONARY: {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			Dictionary dict = *p_arg;
			jclass dclass = env->FindClass("org/godotengine/godot/Dictionary");
			jmethodID ctor = env->GetMethodID(dclass, "<init>", "()V");
			jobject jdict = env->NewObject(dclass, ctor);

			Array keys = dict.keys();

			jobjectArray jkeys = env->NewObjectArray(keys.size(), env->FindClass("java/lang/String"), env->NewStringUTF(""));
			for (int j = 0; j < keys.size(); j++) {
				jstring str = env->NewStringUTF(String(keys[j]).utf8().get_data());
				env->SetObjectArrayElement(jkeys, j, str);
				env->DeleteLocalRef(str);
			};

			jmethodID set_keys = env->GetMethodID(dclass, "set_keys", "([Ljava/lang/String;)V");
			jvalue val;
			val.l = jkeys;
			env->CallVoidMethodA(jdict, set_keys, &val);
			env->DeleteLocalRef(jkeys);

<<<<<<< HEAD
			jobjectArray jvalues = env->NewObjectArray(keys.size(), env->FindClass("java/lang/Object"), NULL);
=======
			jobjectArray jvalues = env->NewObjectArray(keys.size(), env->FindClass("java/lang/Object"), nullptr);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

			for (int j = 0; j < keys.size(); j++) {
				Variant var = dict[keys[j]];
				jvalret v = _variant_to_jvalue(env, var.get_type(), &var, true);
				env->SetObjectArrayElement(jvalues, j, v.val.l);
				if (v.obj) {
					env->DeleteLocalRef(v.obj);
				}
			};

			jmethodID set_values = env->GetMethodID(dclass, "set_values", "([Ljava/lang/Object;)V");
			val.l = jvalues;
			env->CallVoidMethodA(jdict, set_values, &val);
			env->DeleteLocalRef(jvalues);
			env->DeleteLocalRef(dclass);

			v.val.l = jdict;
			v.obj = jdict;
		} break;

<<<<<<< HEAD
		case Variant::POOL_INT_ARRAY: {

			PoolVector<int> array = *p_arg;
			jintArray arr = env->NewIntArray(array.size());
			PoolVector<int>::Read r = array.read();
			env->SetIntArrayRegion(arr, 0, array.size(), r.ptr());
=======
		case Variant::PACKED_INT32_ARRAY: {
			Vector<int> array = *p_arg;
			jintArray arr = env->NewIntArray(array.size());
			const int *r = array.ptr();
			env->SetIntArrayRegion(arr, 0, array.size(), r);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			v.val.l = arr;
			v.obj = arr;

		} break;
<<<<<<< HEAD
		case Variant::POOL_BYTE_ARRAY: {
			PoolVector<uint8_t> array = *p_arg;
			jbyteArray arr = env->NewByteArray(array.size());
			PoolVector<uint8_t>::Read r = array.read();
			env->SetByteArrayRegion(arr, 0, array.size(), reinterpret_cast<const signed char *>(r.ptr()));
=======
		case Variant::PACKED_BYTE_ARRAY: {
			Vector<uint8_t> array = *p_arg;
			jbyteArray arr = env->NewByteArray(array.size());
			const uint8_t *r = array.ptr();
			env->SetByteArrayRegion(arr, 0, array.size(), reinterpret_cast<const signed char *>(r));
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			v.val.l = arr;
			v.obj = arr;

		} break;
<<<<<<< HEAD
		case Variant::POOL_REAL_ARRAY: {

			PoolVector<float> array = *p_arg;
			jfloatArray arr = env->NewFloatArray(array.size());
			PoolVector<float>::Read r = array.read();
			env->SetFloatArrayRegion(arr, 0, array.size(), r.ptr());
=======
		case Variant::PACKED_FLOAT32_ARRAY: {
			Vector<float> array = *p_arg;
			jfloatArray arr = env->NewFloatArray(array.size());
			const float *r = array.ptr();
			env->SetFloatArrayRegion(arr, 0, array.size(), r);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			v.val.l = arr;
			v.obj = arr;

		} break;
<<<<<<< HEAD
		default: {

=======
#ifndef _MSC_VER
#warning This is missing 64 bits arrays, I have no idea how to do it in JNI
#endif

		default: {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			v.val.i = 0;
		} break;
	}
	return v;
}

String _get_class_name(JNIEnv *env, jclass cls, bool *array) {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	jclass cclass = env->FindClass("java/lang/Class");
	jmethodID getName = env->GetMethodID(cclass, "getName", "()Ljava/lang/String;");
	jstring clsName = (jstring)env->CallObjectMethod(cls, getName);

	if (array) {
		jmethodID isArray = env->GetMethodID(cclass, "isArray", "()Z");
		jboolean isarr = env->CallBooleanMethod(cls, isArray);
		(*array) = isarr ? true : false;
	}
	String name = jstring_to_string(clsName, env);
	env->DeleteLocalRef(clsName);

	return name;
}

Variant _jobject_to_variant(JNIEnv *env, jobject obj) {
<<<<<<< HEAD

	if (obj == NULL) {
=======
	if (obj == nullptr) {
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		return Variant();
	}

	jclass c = env->GetObjectClass(obj);
	bool array;
	String name = _get_class_name(env, c, &array);

	if (name == "java.lang.String") {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		return jstring_to_string((jstring)obj, env);
	};

	if (name == "[Ljava.lang.String;") {
<<<<<<< HEAD

		jobjectArray arr = (jobjectArray)obj;
		int stringCount = env->GetArrayLength(arr);
		PoolVector<String> sarr;
=======
		jobjectArray arr = (jobjectArray)obj;
		int stringCount = env->GetArrayLength(arr);
		Vector<String> sarr;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

		for (int i = 0; i < stringCount; i++) {
			jstring string = (jstring)env->GetObjectArrayElement(arr, i);
			sarr.push_back(jstring_to_string(string, env));
			env->DeleteLocalRef(string);
		}

		return sarr;
	};

	if (name == "java.lang.Boolean") {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		jmethodID boolValue = env->GetMethodID(c, "booleanValue", "()Z");
		bool ret = env->CallBooleanMethod(obj, boolValue);
		return ret;
	};

	if (name == "java.lang.Integer" || name == "java.lang.Long") {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		jclass nclass = env->FindClass("java/lang/Number");
		jmethodID longValue = env->GetMethodID(nclass, "longValue", "()J");
		jlong ret = env->CallLongMethod(obj, longValue);
		return ret;
	};

	if (name == "[I") {
<<<<<<< HEAD

		jintArray arr = (jintArray)obj;
		int fCount = env->GetArrayLength(arr);
		PoolVector<int> sarr;
		sarr.resize(fCount);

		PoolVector<int>::Write w = sarr.write();
		env->GetIntArrayRegion(arr, 0, fCount, w.ptr());
		w.release();
=======
		jintArray arr = (jintArray)obj;
		int fCount = env->GetArrayLength(arr);
		Vector<int> sarr;
		sarr.resize(fCount);

		int *w = sarr.ptrw();
		env->GetIntArrayRegion(arr, 0, fCount, w);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		return sarr;
	};

	if (name == "[B") {
<<<<<<< HEAD

		jbyteArray arr = (jbyteArray)obj;
		int fCount = env->GetArrayLength(arr);
		PoolVector<uint8_t> sarr;
		sarr.resize(fCount);

		PoolVector<uint8_t>::Write w = sarr.write();
		env->GetByteArrayRegion(arr, 0, fCount, reinterpret_cast<signed char *>(w.ptr()));
		w.release();
=======
		jbyteArray arr = (jbyteArray)obj;
		int fCount = env->GetArrayLength(arr);
		Vector<uint8_t> sarr;
		sarr.resize(fCount);

		uint8_t *w = sarr.ptrw();
		env->GetByteArrayRegion(arr, 0, fCount, reinterpret_cast<signed char *>(w));
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		return sarr;
	};

	if (name == "java.lang.Float" || name == "java.lang.Double") {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		jclass nclass = env->FindClass("java/lang/Number");
		jmethodID doubleValue = env->GetMethodID(nclass, "doubleValue", "()D");
		double ret = env->CallDoubleMethod(obj, doubleValue);
		return ret;
	};

	if (name == "[D") {
<<<<<<< HEAD

		jdoubleArray arr = (jdoubleArray)obj;
		int fCount = env->GetArrayLength(arr);
		PoolRealArray sarr;
		sarr.resize(fCount);

		PoolRealArray::Write w = sarr.write();

		for (int i = 0; i < fCount; i++) {

			double n;
			env->GetDoubleArrayRegion(arr, i, 1, &n);
			w.ptr()[i] = n;
=======
		jdoubleArray arr = (jdoubleArray)obj;
		int fCount = env->GetArrayLength(arr);
		PackedFloat32Array sarr;
		sarr.resize(fCount);

		real_t *w = sarr.ptrw();

		for (int i = 0; i < fCount; i++) {
			double n;
			env->GetDoubleArrayRegion(arr, i, 1, &n);
			w[i] = n;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		};
		return sarr;
	};

	if (name == "[F") {
<<<<<<< HEAD

		jfloatArray arr = (jfloatArray)obj;
		int fCount = env->GetArrayLength(arr);
		PoolRealArray sarr;
		sarr.resize(fCount);

		PoolRealArray::Write w = sarr.write();

		for (int i = 0; i < fCount; i++) {

			float n;
			env->GetFloatArrayRegion(arr, i, 1, &n);
			w.ptr()[i] = n;
=======
		jfloatArray arr = (jfloatArray)obj;
		int fCount = env->GetArrayLength(arr);
		PackedFloat32Array sarr;
		sarr.resize(fCount);

		real_t *w = sarr.ptrw();

		for (int i = 0; i < fCount; i++) {
			float n;
			env->GetFloatArrayRegion(arr, i, 1, &n);
			w[i] = n;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		};
		return sarr;
	};

	if (name == "[Ljava.lang.Object;") {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		jobjectArray arr = (jobjectArray)obj;
		int objCount = env->GetArrayLength(arr);
		Array varr;

		for (int i = 0; i < objCount; i++) {
			jobject jobj = env->GetObjectArrayElement(arr, i);
			Variant v = _jobject_to_variant(env, jobj);
			varr.push_back(v);
			env->DeleteLocalRef(jobj);
		}

		return varr;
	};

	if (name == "java.util.HashMap" || name == "org.godotengine.godot.Dictionary") {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		Dictionary ret;
		jclass oclass = c;
		jmethodID get_keys = env->GetMethodID(oclass, "get_keys", "()[Ljava/lang/String;");
		jobjectArray arr = (jobjectArray)env->CallObjectMethod(obj, get_keys);

<<<<<<< HEAD
		PoolStringArray keys = _jobject_to_variant(env, arr);
=======
		PackedStringArray keys = _jobject_to_variant(env, arr);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		env->DeleteLocalRef(arr);

		jmethodID get_values = env->GetMethodID(oclass, "get_values", "()[Ljava/lang/Object;");
		arr = (jobjectArray)env->CallObjectMethod(obj, get_values);

		Array vals = _jobject_to_variant(env, arr);
		env->DeleteLocalRef(arr);

		for (int i = 0; i < keys.size(); i++) {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			ret[keys[i]] = vals[i];
		};

		return ret;
	};

	env->DeleteLocalRef(c);

	return Variant();
}

Variant::Type get_jni_type(const String &p_type) {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	static struct {
		const char *name;
		Variant::Type type;
	} _type_to_vtype[] = {
		{ "void", Variant::NIL },
		{ "boolean", Variant::BOOL },
		{ "int", Variant::INT },
<<<<<<< HEAD
		{ "float", Variant::REAL },
		{ "double", Variant::REAL },
		{ "java.lang.String", Variant::STRING },
		{ "[I", Variant::POOL_INT_ARRAY },
		{ "[B", Variant::POOL_BYTE_ARRAY },
		{ "[F", Variant::POOL_REAL_ARRAY },
		{ "[Ljava.lang.String;", Variant::POOL_STRING_ARRAY },
		{ "org.godotengine.godot.Dictionary", Variant::DICTIONARY },
		{ NULL, Variant::NIL }
=======
		{ "float", Variant::FLOAT },
		{ "double", Variant::FLOAT },
		{ "java.lang.String", Variant::STRING },
		{ "[I", Variant::PACKED_INT32_ARRAY },
		{ "[B", Variant::PACKED_BYTE_ARRAY },
		{ "[F", Variant::PACKED_FLOAT32_ARRAY },
		{ "[Ljava.lang.String;", Variant::PACKED_STRING_ARRAY },
		{ "org.godotengine.godot.Dictionary", Variant::DICTIONARY },
		{ nullptr, Variant::NIL }
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	};

	int idx = 0;

	while (_type_to_vtype[idx].name) {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		if (p_type == _type_to_vtype[idx].name)
			return _type_to_vtype[idx].type;

		idx++;
	}

	return Variant::NIL;
}

const char *get_jni_sig(const String &p_type) {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	static struct {
		const char *name;
		const char *sig;
	} _type_to_vtype[] = {
		{ "void", "V" },
		{ "boolean", "Z" },
		{ "int", "I" },
		{ "float", "F" },
		{ "double", "D" },
		{ "java.lang.String", "Ljava/lang/String;" },
		{ "org.godotengine.godot.Dictionary", "Lorg/godotengine/godot/Dictionary;" },
		{ "[I", "[I" },
		{ "[B", "[B" },
		{ "[F", "[F" },
		{ "[Ljava.lang.String;", "[Ljava/lang/String;" },
<<<<<<< HEAD
		{ NULL, "V" }
=======
		{ nullptr, "V" }
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	};

	int idx = 0;

	while (_type_to_vtype[idx].name) {
<<<<<<< HEAD

=======
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
		if (p_type == _type_to_vtype[idx].name)
			return _type_to_vtype[idx].sig;

		idx++;
	}

	return "Ljava/lang/Object;";
}
