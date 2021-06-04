/*************************************************************************/
/*  pivot_transform.cpp                                                  */
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

#include "pivot_transform.h"

#include "tools/import_utils.h"

void PivotTransform::ReadTransformChain() {
<<<<<<< HEAD
	const FBXDocParser::PropertyTable *props = fbx_model->Props();
=======
	const FBXDocParser::PropertyTable *props = fbx_model;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	const FBXDocParser::Model::RotOrder &rot = fbx_model->RotationOrder();
	const FBXDocParser::TransformInheritance &inheritType = fbx_model->InheritType();
	inherit_type = inheritType; // copy the inherit type we need it in the second step.
	print_verbose("Model: " + String(fbx_model->Name().c_str()) + " Has inherit type: " + itos(fbx_model->InheritType()));
	bool ok = false;
	raw_pre_rotation = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "PreRotation", ok));
	if (ok) {
		pre_rotation = ImportUtils::EulerToQuaternion(rot, ImportUtils::deg2rad(raw_pre_rotation));
		print_verbose("valid pre_rotation: " + raw_pre_rotation + " euler conversion: " + (pre_rotation.get_euler() * (180 / Math_PI)));
	}
	raw_post_rotation = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "PostRotation", ok));
	if (ok) {
		post_rotation = ImportUtils::EulerToQuaternion(FBXDocParser::Model::RotOrder_EulerXYZ, ImportUtils::deg2rad(raw_post_rotation));
		print_verbose("valid post_rotation: " + raw_post_rotation + " euler conversion: " + (pre_rotation.get_euler() * (180 / Math_PI)));
	}
	const Vector3 &RotationPivot = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "RotationPivot", ok));
	if (ok) {
		rotation_pivot = ImportUtils::FixAxisConversions(RotationPivot);
	}
	const Vector3 &RotationOffset = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "RotationOffset", ok));
	if (ok) {
		rotation_offset = ImportUtils::FixAxisConversions(RotationOffset);
	}
	const Vector3 &ScalingOffset = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "ScalingOffset", ok));
	if (ok) {
		scaling_offset = ImportUtils::FixAxisConversions(ScalingOffset);
	}
	const Vector3 &ScalingPivot = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "ScalingPivot", ok));
	if (ok) {
		scaling_pivot = ImportUtils::FixAxisConversions(ScalingPivot);
	}
	const Vector3 &Translation = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "Lcl Translation", ok));
	if (ok) {
		translation = ImportUtils::FixAxisConversions(Translation);
	}
	raw_rotation = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "Lcl Rotation", ok));
	if (ok) {
		rotation = ImportUtils::EulerToQuaternion(rot, ImportUtils::deg2rad(raw_rotation));
	}
	const Vector3 &Scaling = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "Lcl Scaling", ok));
	if (ok) {
		scaling = Scaling;
<<<<<<< HEAD
=======
	} else {
		scaling = Vector3(1, 1, 1);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	}
	const Vector3 &GeometricScaling = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "GeometricScaling", ok));
	if (ok) {
		geometric_scaling = GeometricScaling;
<<<<<<< HEAD
	}
	const Vector3 &GeometricRotation = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "GeometricRotation", ok));
	if (ok) {
		geometric_rotation = ImportUtils::EulerToQuaternion(rot, ImportUtils::deg2rad(GeometricRotation));
	}
	const Vector3 &GeometricTranslation = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "GeometricTranslation", ok));
	if (ok) {
		geometric_translation = ImportUtils::FixAxisConversions(GeometricTranslation);
	}
}

Transform PivotTransform::ComputeLocalTransform(Vector3 p_translation, Quat p_rotation, Vector3 p_scaling) const {
	Transform T, Roff, Rp, Soff, Sp, S;
=======
	} else {
		geometric_scaling = Vector3(1, 1, 1);
	}

	const Vector3 &GeometricRotation = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "GeometricRotation", ok));
	if (ok) {
		geometric_rotation = ImportUtils::EulerToQuaternion(rot, ImportUtils::deg2rad(GeometricRotation));
	} else {
		geometric_rotation = Quat();
	}

	const Vector3 &GeometricTranslation = ImportUtils::safe_import_vector3(FBXDocParser::PropertyGet<Vector3>(props, "GeometricTranslation", ok));
	if (ok) {
		geometric_translation = ImportUtils::FixAxisConversions(GeometricTranslation);
	} else {
		geometric_translation = Vector3(0, 0, 0);
	}

	if (geometric_rotation != Quat()) {
		print_error("geometric rotation is unsupported!");
		//CRASH_COND(true);
	}

	if (!geometric_scaling.is_equal_approx(Vector3(1, 1, 1))) {
		print_error("geometric scaling is unsupported!");
		//CRASH_COND(true);
	}

	if (!geometric_translation.is_equal_approx(Vector3(0, 0, 0))) {
		print_error("geometric translation is unsupported.");
		//CRASH_COND(true);
	}
}

Transform3D PivotTransform::ComputeLocalTransform(Vector3 p_translation, Quat p_rotation, Vector3 p_scaling) const {
	Transform3D T, Roff, Rp, Soff, Sp, S;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	// Here I assume this is the operation which needs done.
	// Its WorldTransform * V

	// Origin pivots
	T.set_origin(p_translation);
	Roff.set_origin(rotation_offset);
	Rp.set_origin(rotation_pivot);
	Soff.set_origin(scaling_offset);
	Sp.set_origin(scaling_pivot);

	// Scaling node
	S.scale(p_scaling);
	// Rotation pivots
<<<<<<< HEAD
	Transform Rpre = Transform(pre_rotation);
	Transform R = Transform(p_rotation);
	Transform Rpost = Transform(post_rotation);
=======
	Transform3D Rpre = Transform3D(pre_rotation);
	Transform3D R = Transform3D(p_rotation);
	Transform3D Rpost = Transform3D(post_rotation);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	return T * Roff * Rp * Rpre * R * Rpost.affine_inverse() * Rp.affine_inverse() * Soff * Sp * S * Sp.affine_inverse();
}

<<<<<<< HEAD
Transform PivotTransform::ComputeGlobalTransform(Vector3 p_translation, Quat p_rotation, Vector3 p_scaling) const {
	Transform T, Roff, Rp, Soff, Sp, S;
=======
Transform3D PivotTransform::ComputeGlobalTransform(Transform3D t) const {
	Vector3 pos = t.origin;
	Vector3 scale = t.basis.get_scale();
	Quat rot = t.basis.get_rotation_quat();
	return ComputeGlobalTransform(pos, rot, scale);
}

Transform3D PivotTransform::ComputeLocalTransform(Transform3D t) const {
	Vector3 pos = t.origin;
	Vector3 scale = t.basis.get_scale();
	Quat rot = t.basis.get_rotation_quat();
	return ComputeLocalTransform(pos, rot, scale);
}

Transform3D PivotTransform::ComputeGlobalTransform(Vector3 p_translation, Quat p_rotation, Vector3 p_scaling) const {
	Transform3D T, Roff, Rp, Soff, Sp, S;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	// Here I assume this is the operation which needs done.
	// Its WorldTransform * V

	// Origin pivots
	T.set_origin(p_translation);
	Roff.set_origin(rotation_offset);
	Rp.set_origin(rotation_pivot);
	Soff.set_origin(scaling_offset);
	Sp.set_origin(scaling_pivot);

	// Scaling node
	S.scale(p_scaling);

	// Rotation pivots
<<<<<<< HEAD
	Transform Rpre = Transform(pre_rotation);
	Transform R = Transform(p_rotation);
	Transform Rpost = Transform(post_rotation);

	Transform parent_global_xform;
	Transform parent_local_scaling_m;
=======
	Transform3D Rpre = Transform3D(pre_rotation);
	Transform3D R = Transform3D(p_rotation);
	Transform3D Rpost = Transform3D(post_rotation);

	Transform3D parent_global_xform;
	Transform3D parent_local_scaling_m;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	if (parent_transform.is_valid()) {
		parent_global_xform = parent_transform->GlobalTransform;
		parent_local_scaling_m = parent_transform->Local_Scaling_Matrix;
	}

<<<<<<< HEAD
	Transform local_rotation_m, parent_global_rotation_m;
=======
	Transform3D local_rotation_m, parent_global_rotation_m;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	Quat parent_global_rotation = parent_global_xform.basis.get_rotation_quat();
	parent_global_rotation_m.basis.set_quat(parent_global_rotation);
	local_rotation_m = Rpre * R * Rpost;

	//Basis parent_global_rotation = Basis(parent_global_xform.get_basis().get_rotation_quat().normalized());

<<<<<<< HEAD
	Transform local_shear_scaling, parent_shear_scaling, parent_shear_rotation, parent_shear_translation;
=======
	Transform3D local_shear_scaling, parent_shear_scaling, parent_shear_rotation, parent_shear_translation;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	Vector3 parent_translation = parent_global_xform.get_origin();
	parent_shear_translation.origin = parent_translation;
	parent_shear_rotation = parent_shear_translation.affine_inverse() * parent_global_xform;
	parent_shear_scaling = parent_global_rotation_m.affine_inverse() * parent_shear_rotation;
	local_shear_scaling = S;

	// Inherit type handler - we don't care about T here, just reordering RSrs etc.
<<<<<<< HEAD
	Transform global_rotation_scale;
=======
	Transform3D global_rotation_scale;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	if (inherit_type == FBXDocParser::Transform_RrSs) {
		global_rotation_scale = parent_global_rotation_m * local_rotation_m * parent_shear_scaling * local_shear_scaling;
	} else if (inherit_type == FBXDocParser::Transform_RSrs) {
		global_rotation_scale = parent_global_rotation_m * parent_shear_scaling * local_rotation_m * local_shear_scaling;
	} else if (inherit_type == FBXDocParser::Transform_Rrs) {
<<<<<<< HEAD
		Transform parent_global_shear_m_noLocal = parent_shear_scaling * parent_local_scaling_m.affine_inverse();
		global_rotation_scale = parent_global_rotation_m * local_rotation_m * parent_global_shear_m_noLocal * local_shear_scaling;
	}
	Transform local_transform = T * Roff * Rp * Rpre * R * Rpost.affine_inverse() * Rp.affine_inverse() * Soff * Sp * S * Sp.affine_inverse();
	//Transform local_translation_pivoted = Transform(Basis(), LocalTransform.origin);
=======
		Transform3D parent_global_shear_m_noLocal = parent_shear_scaling * parent_local_scaling_m.affine_inverse();
		global_rotation_scale = parent_global_rotation_m * local_rotation_m * parent_global_shear_m_noLocal * local_shear_scaling;
	}
	Transform3D local_transform = T * Roff * Rp * Rpre * R * Rpost.affine_inverse() * Rp.affine_inverse() * Soff * Sp * S * Sp.affine_inverse();
	//Transform3D local_translation_pivoted = Transform3D(Basis(), LocalTransform.origin);

	ERR_FAIL_COND_V_MSG(local_transform.basis.determinant() == 0, Transform3D(), "Det == 0 prevented in scene file");
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	// manual hack to force SSC not to be compensated for - until we can handle it properly with tests
	return parent_global_xform * local_transform;
}

void PivotTransform::ComputePivotTransform() {
<<<<<<< HEAD
	Transform T, Roff, Rp, Soff, Sp, S;
=======
	Transform3D T, Roff, Rp, Soff, Sp, S;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	// Here I assume this is the operation which needs done.
	// Its WorldTransform * V

	// Origin pivots
	T.set_origin(translation);
	Roff.set_origin(rotation_offset);
	Rp.set_origin(rotation_pivot);
	Soff.set_origin(scaling_offset);
	Sp.set_origin(scaling_pivot);

	// Scaling node
	if (!scaling.is_equal_approx(Vector3())) {
		S.scale(scaling);
	} else {
		S.scale(Vector3(1, 1, 1));
	}
	Local_Scaling_Matrix = S; // copy for when node / child is looking for the value of this.

	// Rotation pivots
<<<<<<< HEAD
	Transform Rpre = Transform(pre_rotation);
	Transform R = Transform(rotation);
	Transform Rpost = Transform(post_rotation);

	Transform parent_global_xform;
	Transform parent_local_scaling_m;
=======
	Transform3D Rpre = Transform3D(pre_rotation);
	Transform3D R = Transform3D(rotation);
	Transform3D Rpost = Transform3D(post_rotation);

	Transform3D parent_global_xform;
	Transform3D parent_local_scaling_m;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	if (parent_transform.is_valid()) {
		parent_global_xform = parent_transform->GlobalTransform;
		parent_local_scaling_m = parent_transform->Local_Scaling_Matrix;
	}

<<<<<<< HEAD
	Transform local_rotation_m, parent_global_rotation_m;
=======
	Transform3D local_rotation_m, parent_global_rotation_m;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	Quat parent_global_rotation = parent_global_xform.basis.get_rotation_quat();
	parent_global_rotation_m.basis.set_quat(parent_global_rotation);
	local_rotation_m = Rpre * R * Rpost;

	//Basis parent_global_rotation = Basis(parent_global_xform.get_basis().get_rotation_quat().normalized());

<<<<<<< HEAD
	Transform local_shear_scaling, parent_shear_scaling, parent_shear_rotation, parent_shear_translation;
=======
	Transform3D local_shear_scaling, parent_shear_scaling, parent_shear_rotation, parent_shear_translation;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	Vector3 parent_translation = parent_global_xform.get_origin();
	parent_shear_translation.origin = parent_translation;
	parent_shear_rotation = parent_shear_translation.affine_inverse() * parent_global_xform;
	parent_shear_scaling = parent_global_rotation_m.affine_inverse() * parent_shear_rotation;
	local_shear_scaling = S;

	// Inherit type handler - we don't care about T here, just reordering RSrs etc.
<<<<<<< HEAD
	Transform global_rotation_scale;
=======
	Transform3D global_rotation_scale;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	if (inherit_type == FBXDocParser::Transform_RrSs) {
		global_rotation_scale = parent_global_rotation_m * local_rotation_m * parent_shear_scaling * local_shear_scaling;
	} else if (inherit_type == FBXDocParser::Transform_RSrs) {
		global_rotation_scale = parent_global_rotation_m * parent_shear_scaling * local_rotation_m * local_shear_scaling;
	} else if (inherit_type == FBXDocParser::Transform_Rrs) {
<<<<<<< HEAD
		Transform parent_global_shear_m_noLocal = parent_shear_scaling * parent_local_scaling_m.inverse();
		global_rotation_scale = parent_global_rotation_m * local_rotation_m * parent_global_shear_m_noLocal * local_shear_scaling;
	}
	LocalTransform = Transform();
=======
		Transform3D parent_global_shear_m_noLocal = parent_shear_scaling * parent_local_scaling_m.inverse();
		global_rotation_scale = parent_global_rotation_m * local_rotation_m * parent_global_shear_m_noLocal * local_shear_scaling;
	}
	LocalTransform = Transform3D();
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	LocalTransform = T * Roff * Rp * Rpre * R * Rpost.affine_inverse() * Rp.affine_inverse() * Soff * Sp * S * Sp.affine_inverse();

	ERR_FAIL_COND_MSG(LocalTransform.basis.determinant() == 0, "invalid scale reset");

<<<<<<< HEAD
	Transform local_translation_pivoted = Transform(Basis(), LocalTransform.origin);
	GlobalTransform = Transform();
	//GlobalTransform = parent_global_xform * LocalTransform;
	Transform global_origin = Transform(Basis(), parent_translation);
=======
	Transform3D local_translation_pivoted = Transform3D(Basis(), LocalTransform.origin);
	GlobalTransform = Transform3D();
	//GlobalTransform = parent_global_xform * LocalTransform;
	Transform3D global_origin = Transform3D(Basis(), parent_translation);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	GlobalTransform = (global_origin * local_translation_pivoted) * global_rotation_scale;

	ImportUtils::debug_xform("local xform calculation", LocalTransform);
	print_verbose("scale of node: " + S.basis.get_scale_local());
	print_verbose("---------------------------------------------------------------");
}

void PivotTransform::Execute() {
	ReadTransformChain();
	ComputePivotTransform();

	ImportUtils::debug_xform("global xform: ", GlobalTransform);
<<<<<<< HEAD
=======

	if (LocalTransform.basis.determinant() == 0) {
		print_error("Serious det == 0!");
	}

	if (GlobalTransform.basis.determinant() == 0) {
		print_error("Serious! node has det == 0!");
	}

>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	computed_global_xform = true;
}
