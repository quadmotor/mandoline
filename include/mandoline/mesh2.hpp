#pragma once
#include "mandoline/mesh.hpp"
namespace mandoline {
    template <>
        struct CutCellMesh<2>: public CutCellMeshBase<2, CutCellMesh<2>> {
            public:
                using Base = CutCellMeshBase<2,CutCellMesh<2>>;
                using Base::Base;
                using ColVecs = typename Base::ColVecs;
                using VecX = typename Base::VecX;

                int cell_size() const;
                std::array<int,2> dual_edge(int idx) const;
                int cell_index(const VecCRef&) const;
                ColVecs dual_vertices() const;
                mtao::ColVectors<int,3> faces() const;
                std::vector<int> cell(int index) const;

                int nearest_edge_index(const VecCRef&) const;
                VecX volumes() const;
                VecX dual_edge_volumes() const;
                Eigen::SparseMatrix<double> boundary(bool dirichlet_boundary) const;
                //bool is_cutface_index(int index) const { return index >= StaggeredGrid::template form_size<D>(); }
                Edges halfedges_per_edge;//halfedge indices

                mtao::geometry::mesh::HalfEdgeMesh hem;
                VecX halfedge_orientations;
                std::map<int, int> halfedge_to_edge_index;
                std::map<int,std::set<int>> cell_grid_ownership;
                std::map<int,std::set<int>> edge_grid_ownership;
                std::map<Edge, int> edge_vertices_to_edge_index;
                VecX active_cell_mask;
                Edges cut_mesh_edges;//cut edges from the input mesh. not necessary for anything really

        };
}