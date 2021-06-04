/*************************************************************************/
/*  rid.cpp                                                              */
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

#include "gdnative/rid.h"

#include "core/os/memory.h"
#include "core/templates/rid.h"

static_assert(sizeof(godot_rid) == sizeof(RID), "RID size mismatch");

#ifdef __cplusplus
extern "C" {
#endif

<<<<<<< HEAD
static_assert(sizeof(godot_rid) == sizeof(RID), "RID size mismatch");

void GDAPI godot_rid_new(godot_rid *r_dest) {
	RID *dest = (RID *)r_dest;
	memnew_placement(dest, RID);
}

godot_int GDAPI godot_rid_get_id(const godot_rid *p_self) {
	const RID *self = (const RID *)p_self;
	return self->get_id();
}

void GDAPI godot_rid_new_with_resource(godot_rid *r_dest, const godot_object *p_from) {
	const Resource *res_from = Object::cast_to<Resource>((Object *)p_from);
	godot_rid_new(r_dest);
	if (res_from) {
		RID *dest = (RID *)r_dest;
		*dest = RID(res_from->get_rid());
	}
}

godot_bool GDAPI godot_rid_operator_equal(const godot_rid *p_self, const godot_rid *p_b) {
	const RID *self = (const RID *)p_self;
	const RID *b = (const RID *)p_b;
	return *self == *b;
=======
void GDAPI godot_rid_new(godot_rid *p_self) {
	memnew_placement(p_self, RID);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
}

void GDAPI godot_rid_new_copy(godot_rid *r_dest, const godot_rid *p_src) {
	memnew_placement(r_dest, RID(*(RID *)p_src));
}

#ifdef __cplusplus
}
#endif
