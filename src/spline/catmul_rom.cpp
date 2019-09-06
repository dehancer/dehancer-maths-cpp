//
// Created by denn nevera on 2019-09-06.
//

#include "dehancer/spline/catmul_rom.hpp"

namespace dehancer {
    namespace spline {

        CatmulRom::CatmulRom(size_t resolution, float tension):
                MatrixBased(resolution),
                tension_(tension)
        {
            set_tension(tension_);
        }

        CatmulRom::CatmulRom(const std::vector<dehancer::math::float2> &controls, size_t resolution, float tension):
                MatrixBased(controls,resolution),
                tension_(tension)
        {
            set_tension(tension_);
            evaluate_curve();
        }

        const math::float4x4& CatmulRom::get_matrix() const {
            return matrix_;
        }

        void CatmulRom::set_tension(float tension_) {
            math::float4x4 matrix = { { 0,  1/tension_,    0,             0},
                                      {-1,  0,             1,             0},
                                      { 2, -3/tension_+1,  3/tension_-2, -1},
                                      {-1,  2/tension_-1, -2/tension_+1,  1}
            };
            matrix_ = tension_ * matrix;
        }
    }
}