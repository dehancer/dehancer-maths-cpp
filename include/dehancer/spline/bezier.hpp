//
// Created by denn nevera on 2019-09-03.
//

#pragma once

#include "dehancer/spline/matrix_based.hpp"


namespace dehancer::spline {

    class Bezier: public MatrixBased {

    public:
        using MatrixBased::MatrixBased;
        explicit Bezier(const std::vector<math::float2>& controls, size_t resolution = 256);
        [[nodiscard]] const math::float4x4& get_matrix() const override ;
    };
}


