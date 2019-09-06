//
// Created by denn nevera on 2019-09-06.
//

#pragma once

#include "dehancer/spline/matrix_based.hpp"

namespace dehancer {

    namespace spline {

        class CatmulRom: public MatrixBased {

        public:
            using MatrixBased::MatrixBased;
            CatmulRom(size_t resolution = 256, float tension=0.5);
            CatmulRom(const std::vector<math::float2>& controls, size_t resolution = 256, float tension=0.5);
            virtual const math::float4x4& get_matrix() const override ;

            void  set_tension(float tension_);
            float get_tension() const { return tension_;}

        private:
            float tension_;
            math::float4x4 matrix_;
        };
    }
}
