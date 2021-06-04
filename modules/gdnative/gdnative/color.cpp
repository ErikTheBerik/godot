/*************************************************************************/
/*  color.cpp                                                            */
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

#include "gdnative/color.h"

#include "core/math/color.h"

static_assert(sizeof(godot_color) == sizeof(Color), "Color size mismatch");

#ifdef __cplusplus
extern "C" {
#endif

<<<<<<< HEAD
static_assert(sizeof(godot_color) == sizeof(Color), "Color size mismatch");

void GDAPI godot_color_new_rgba(godot_color *r_dest, const godot_real p_r, const godot_real p_g, const godot_real p_b, const godot_real p_a) {

	Color *dest = (Color *)r_dest;
	*dest = Color(p_r, p_g, p_b, p_a);
}

void GDAPI godot_color_new_rgb(godot_color *r_dest, const godot_real p_r, const godot_real p_g, const godot_real p_b) {

	Color *dest = (Color *)r_dest;
	*dest = Color(p_r, p_g, p_b);
}

godot_real godot_color_get_r(const godot_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->r;
}

void godot_color_set_r(godot_color *p_self, const godot_real val) {
	Color *self = (Color *)p_self;
	self->r = val;
}

godot_real godot_color_get_g(const godot_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->g;
=======
void GDAPI godot_color_new(godot_color *p_self) {
	memnew_placement(p_self, Color);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
}

void GDAPI godot_color_new_copy(godot_color *r_dest, const godot_color *p_src) {
	memnew_placement(r_dest, Color(*(Color *)p_src));
}

float GDAPI *godot_color_operator_index(godot_color *p_self, godot_int p_index) {
	Color *self = (Color *)p_self;
	return (float *)&self->operator[](p_index);
}

const float GDAPI *godot_color_operator_index_const(const godot_color *p_self, godot_int p_index) {
	const Color *self = (const Color *)p_self;
	return (const float *)&self->operator[](p_index);
}

#ifdef __cplusplus
}
#endif
