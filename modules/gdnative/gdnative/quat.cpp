/*************************************************************************/
/*  quat.cpp                                                             */
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

#include "gdnative/quat.h"

#include "core/math/quat.h"

static_assert(sizeof(godot_quat) == sizeof(Quat), "Quat size mismatch");

#ifdef __cplusplus
extern "C" {
#endif

<<<<<<< HEAD
static_assert(sizeof(godot_quat) == sizeof(Quat), "Quat size mismatch");

void GDAPI godot_quat_new(godot_quat *r_dest, const godot_real p_x, const godot_real p_y, const godot_real p_z, const godot_real p_w) {

	Quat *dest = (Quat *)r_dest;
	*dest = Quat(p_x, p_y, p_z, p_w);
}

void GDAPI godot_quat_new_with_axis_angle(godot_quat *r_dest, const godot_vector3 *p_axis, const godot_real p_angle) {
	const Vector3 *axis = (const Vector3 *)p_axis;
	Quat *dest = (Quat *)r_dest;
	*dest = Quat(*axis, p_angle);
}

void GDAPI godot_quat_new_with_basis(godot_quat *r_dest, const godot_basis *p_basis) {
	const Basis *basis = (const Basis *)p_basis;
	Quat *dest = (Quat *)r_dest;
	*dest = Quat(*basis);
}

void GDAPI godot_quat_new_with_euler(godot_quat *r_dest, const godot_vector3 *p_euler) {
	const Vector3 *euler = (const Vector3 *)p_euler;
	Quat *dest = (Quat *)r_dest;
	*dest = Quat(*euler);
}

godot_real GDAPI godot_quat_get_x(const godot_quat *p_self) {
	const Quat *self = (const Quat *)p_self;
	return self->x;
=======
void GDAPI godot_quat_new(godot_quat *p_self) {
	memnew_placement(p_self, Quat);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
}

void GDAPI godot_quat_new_copy(godot_quat *r_dest, const godot_quat *p_src) {
	memnew_placement(r_dest, Quat(*(Quat *)p_src));
}

godot_real_t GDAPI *godot_quat_operator_index(godot_quat *p_self, godot_int p_index) {
	Quat *self = (Quat *)p_self;
	return (godot_real_t *)&self->operator[](p_index);
}

const godot_real_t GDAPI *godot_quat_operator_index_const(const godot_quat *p_self, godot_int p_index) {
	const Quat *self = (const Quat *)p_self;
	return (const godot_real_t *)&self->operator[](p_index);
}

#ifdef __cplusplus
}
#endif
