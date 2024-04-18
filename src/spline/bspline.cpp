//
// Created by denn nevera on 2019-11-09.
//

#include "dehancer/spline/bspline.hpp"

namespace dehancer::spline {

    static  const float mul = float(1.0/6.0);

    static const math::float4x4 matrix =
            { {  1, 4, 1, 0},
              { -3, 0, 3, 0},
              {  3,-6, 3, 0},
              { -1, 3,-3, 1}
            };

    BSpline::BSpline(const std::vector<dehancer::math::float2> &controls, size_t resolution):
            MatrixBased(controls,resolution) {
        evaluate_curve();
    }

    const math::float4x4& BSpline::get_matrix() const {
        static math::float4x4 m = mul * matrix;
        return m;
    }
}
