//
// Created by denn nevera on 2019-09-06.
//

#include "dehancer/spline/catmul_rom.hpp"

namespace dehancer::spline {

    CatmulRom::CatmulRom(size_t resolution, float tension):
            MatrixBased(resolution)
    {
        set_tension(tension);
    }

    CatmulRom::CatmulRom(const std::vector<dehancer::math::float2> &controls, size_t resolution, float tension):
            MatrixBased(controls,resolution)
    {
        set_tension(tension);
        evaluate_curve();
    }

    const math::float4x4& CatmulRom::get_matrix() const {
        return matrix_;
    }

    void CatmulRom::set_tension(float tension) {
        tension_ = tension;
        math::float4x4 matrix = { { 0,           1,             0,               0},
                                  {-tension_,    0,             tension_,        0},
                                  { 2*tension_,  tension_-3,    3-2*tension_,   -tension_},
                                  {-tension_,    2-tension_,    tension_-2,      tension_}
        };
        matrix_ =  matrix;
    }
}
