/*************************************************************************/
/*  fbx_mesh_data.h                                                      */
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

#ifndef FBX_MESH_DATA_H
#define FBX_MESH_DATA_H

<<<<<<< HEAD
#include "core/hash_map.h"
#include "scene/3d/mesh_instance.h"
=======
#include "core/templates/hash_map.h"
#include "core/templates/local_vector.h"
#include "core/templates/ordered_hash_map.h"
#include "editor/import/resource_importer_scene.h"
#include "editor/import/scene_importer_mesh_node_3d.h"
#include "scene/3d/mesh_instance_3d.h"
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
#include "scene/resources/surface_tool.h"

#include "fbx_bone.h"
#include "fbx_parser/FBXMeshGeometry.h"
#include "import_state.h"
#include "tools/import_utils.h"

<<<<<<< HEAD
=======
struct FBXNode;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
struct FBXMeshData;
struct FBXBone;
struct ImportState;

<<<<<<< HEAD
=======
typedef int Vertex;
typedef int SurfaceId;
typedef int PolygonId;
typedef int DataIndex;

struct SurfaceData {
	Ref<SurfaceTool> surface_tool;
	OrderedHashMap<Vertex, int> lookup_table; // proposed fix is to replace lookup_table[vertex_id] to give the position of the vertices_map[int] index.
	LocalVector<Vertex> vertices_map; // this must be ordered the same as insertion <-- slow to do find() operation.
	Ref<Material> material;
	HashMap<PolygonId, Vector<DataIndex>> surface_polygon_vertex;
	Array morphs;
};

>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
struct VertexWeightMapping {
	Vector<real_t> weights;
	Vector<int> bones;
	// This extra vector is used because the bone id is computed in a second step.
	// TODO Get rid of this extra step is a good idea.
<<<<<<< HEAD
	Vector<Ref<FBXBone> > bones_ref;
=======
	Vector<Ref<FBXBone>> bones_ref;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
};

template <class T>
struct VertexData {
	int polygon_index;
	T data;
};

// Caches mesh information and instantiates meshes for you using helper functions.
struct FBXMeshData : Reference {
	struct MorphVertexData {
		// TODO we have only these??
		/// Each element is a vertex. Not supposed to be void.
		Vector<Vector3> vertices;
		/// Each element is a vertex. Not supposed to be void.
		Vector<Vector3> normals;
	};

<<<<<<< HEAD
=======
	// FIXME: remove this is a hack for testing only
	mutable const FBXDocParser::MeshGeometry *mesh_geometry = nullptr;

	Ref<FBXNode> mesh_node = nullptr;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	/// vertex id, Weight Info
	/// later: perf we can use array here
	HashMap<int, VertexWeightMapping> vertex_weights;

	// translate fbx mesh data from document context to FBX Mesh Geometry Context
	bool valid_weight_indexes = false;

<<<<<<< HEAD
	MeshInstance *create_fbx_mesh(const ImportState &state, const FBXDocParser::MeshGeometry *mesh_geometry, const FBXDocParser::Model *model, bool use_compression);
=======
	EditorSceneImporterMeshNode3D *create_fbx_mesh(const ImportState &state, const FBXDocParser::MeshGeometry *p_mesh_geometry, const FBXDocParser::Model *model, bool use_compression);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	void gen_weight_info(Ref<SurfaceTool> st, int vertex_id) const;

	/* mesh maximum weight count */
	bool valid_weight_count = false;
	int max_weight_count = 0;
	uint64_t armature_id = 0;
	bool valid_armature_id = false;
<<<<<<< HEAD
	MeshInstance *godot_mesh_instance = nullptr;

private:
	void sanitize_vertex_weights();
=======
	EditorSceneImporterMeshNode3D *godot_mesh_instance = nullptr;

private:
	void sanitize_vertex_weights(const ImportState &state);
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	/// Make sure to reorganize the vertices so that the correct UV is taken.
	/// This step is needed because differently from the normal, that can be
	/// combined, the UV may need its own triangle because sometimes they have
	/// really different UV for the same vertex but different polygon.
	/// This function make sure to add another vertex for those UVS.
	void reorganize_vertices(
			std::vector<int> &r_polygon_indices,
			std::vector<Vector3> &r_vertices,
			HashMap<int, Vector3> &r_normals,
			HashMap<int, Vector2> &r_uv_1,
			HashMap<int, Vector2> &r_uv_2,
			HashMap<int, Color> &r_color,
			HashMap<String, MorphVertexData> &r_morphs,
<<<<<<< HEAD
			HashMap<int, HashMap<int, Vector3> > &r_normals_raw,
			HashMap<int, HashMap<int, Vector2> > &r_uv_1_raw,
			HashMap<int, HashMap<int, Vector2> > &r_uv_2_raw);

	void add_vertex(
=======
			HashMap<int, HashMap<int, Vector3>> &r_normals_raw,
			HashMap<int, HashMap<int, Color>> &r_colors_raw,
			HashMap<int, HashMap<int, Vector2>> &r_uv_1_raw,
			HashMap<int, HashMap<int, Vector2>> &r_uv_2_raw);

	void add_vertex(
			const ImportState &state,
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
			Ref<SurfaceTool> p_surface_tool,
			real_t p_scale,
			int p_vertex,
			const std::vector<Vector3> &p_vertices_position,
			const HashMap<int, Vector3> &p_normals,
			const HashMap<int, Vector2> &p_uvs_0,
			const HashMap<int, Vector2> &p_uvs_1,
			const HashMap<int, Color> &p_colors,
			const Vector3 &p_morph_value = Vector3(),
			const Vector3 &p_morph_normal = Vector3());

<<<<<<< HEAD
	void triangulate_polygon(Ref<SurfaceTool> st, Vector<int> p_polygon_vertex, Vector<int> p_surface_vertex_map, const std::vector<Vector3> &p_vertices) const;
=======
	void triangulate_polygon(SurfaceData *surface, const Vector<int> &p_polygon_vertex, const std::vector<Vector3> &p_vertices) const;
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45

	/// This function is responsible to convert the FBX polygon vertex to
	/// vertex index.
	/// The polygon vertices are stored in an array with some negative
	/// values. The negative values define the last face index.
	/// For example the following `face_array` contains two faces, the former
	/// with 3 vertices and the latter with a line:
	/// [0,2,-2,3,-5]
	/// Parsed as:
	/// [0, 2, 1, 3, 4]
	/// The negative values are computed using this formula: `(-value) - 1`
	///
<<<<<<< HEAD
	/// Returns the vertex index from the poligon vertex.
	/// Returns -1 if `p_index` is invalid.
	int get_vertex_from_polygon_vertex(const std::vector<int> &p_face_indices, int p_index) const;

	/// Retuns true if this polygon_vertex_index is the end of a new polygon.
	bool is_end_of_polygon(const std::vector<int> &p_face_indices, int p_index) const;

	/// Retuns true if this polygon_vertex_index is the begin of a new polygon.
=======
	/// Returns the vertex index from the polygon vertex.
	/// Returns -1 if `p_index` is invalid.
	int get_vertex_from_polygon_vertex(const std::vector<int> &p_face_indices, int p_index) const;

	/// Returns true if this polygon_vertex_index is the end of a new polygon.
	bool is_end_of_polygon(const std::vector<int> &p_face_indices, int p_index) const;

	/// Returns true if this polygon_vertex_index is the begin of a new polygon.
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	bool is_start_of_polygon(const std::vector<int> &p_face_indices, int p_index) const;

	/// Returns the number of polygons.
	int count_polygons(const std::vector<int> &p_face_indices) const;

<<<<<<< HEAD
	/// Used to extract data from the `MappingData` alligned with vertex.
	/// Useful to extract normal/uvs/colors/tangets/etc...
=======
	/// Used to extract data from the `MappingData` aligned with vertex.
	/// Useful to extract normal/uvs/colors/tangents/etc...
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	/// If the function fails somehow, it returns an hollow vector and print an error.
	template <class R, class T>
	HashMap<int, R> extract_per_vertex_data(
			int p_vertex_count,
			const std::vector<FBXDocParser::MeshGeometry::Edge> &p_edges,
			const std::vector<int> &p_mesh_indices,
			const FBXDocParser::MeshGeometry::MappingData<T> &p_mapping_data,
<<<<<<< HEAD
			R (*collector_function)(const Vector<VertexData<T> > *p_vertex_data, R p_fall_back),
			R p_fall_back) const;

	/// Used to extract data from the `MappingData` organized per polygon.
	/// Useful to extract the materila
=======
			R (*collector_function)(const Vector<VertexData<T>> *p_vertex_data, R p_fall_back),
			R p_fall_back) const;

	/// Used to extract data from the `MappingData` organized per polygon.
	/// Useful to extract the material
>>>>>>> 5d9cab3aeb3c62df6b7b44e6e68c0ebbb67f7a45
	/// If the function fails somehow, it returns an hollow vector and print an error.
	template <class T>
	HashMap<int, T> extract_per_polygon(
			int p_vertex_count,
			const std::vector<int> &p_face_indices,
			const FBXDocParser::MeshGeometry::MappingData<T> &p_fbx_data,
			T p_fallback_value) const;

	/// Extracts the morph data and organizes it per vertices.
	/// The returned `MorphVertexData` arrays are never something different
	/// then the `vertex_count`.
	void extract_morphs(const FBXDocParser::MeshGeometry *mesh_geometry, HashMap<String, MorphVertexData> &r_data);
};

#endif // FBX_MESH_DATA_H
