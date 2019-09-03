//
// Created by denn nevera on 2019-09-03.
//

#include "dehancer/spline/bezier.hpp"

namespace dehancer {
    namespace spline {

        math::float4x4 Bezier::matrix_ = { { 1,  0,  0, 0},
                                           {-3,  3,  0, 0},
                                           { 3, -6,  3, 0},
                                           {-1,  3, -3, 1}
        };

        math::float4x4& Bezier::get_matrix() const {
            return matrix_;
        }
    }
}