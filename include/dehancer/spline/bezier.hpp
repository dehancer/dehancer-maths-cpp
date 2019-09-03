//
// Created by denn nevera on 2019-09-03.
//

#pragma once

#include "dehancer/spline/matrix_based.hpp"

namespace dehancer {

    namespace spline {

        class Bezier: public MatrixBased {

        public:
            using MatrixBased::MatrixBased;

            virtual math::float4x4& get_matrix() const;

        private:
            static math::float4x4 matrix_;
        };
    }
}

