//
// Created by denn nevera on 2019-09-03.
//

#include "dehancer/spline/bezier.hpp"

namespace dehancer {
    namespace spline {

        static const math::float4x4 matrix =
                { { 1,  0,  0, 0},
                  {-3,  3,  0, 0},
                  { 3, -6,  3, 0},
                  {-1,  3, -3, 1}
                };

        Bezier::Bezier(const std::vector<dehancer::math::float2> &controls, size_t resolution):
        MatrixBased(controls,resolution) {
            evaluate_curve();
        }

        const math::float4x4& Bezier::get_matrix() const {
            return matrix;
        }
    }
}