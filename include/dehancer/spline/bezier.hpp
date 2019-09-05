//
// Created by denn nevera on 2019-09-03.
//

#pragma once

#include "dehancer/spline/matrix_based.hpp"

namespace dehancer {

    namespace spline {

//        class Bezier: public MatrixBased {
//
//        public:
//            using MatrixBased::MatrixBased;
//
//            virtual math::float4x4& get_matrix() const;
//
//        private:
//            static math::float4x4 matrix_;
//        };

        class Bezier: public math::protocol::Interpolator {

        public:
            using math::protocol::Interpolator::Interpolator;

            virtual size_t minimum_controls() const;
            virtual float value(float x) const;

            void evaluate_curve();

        private:
            std::vector<math::float2> curve_;

            void make_nps(std::vector<size_t>& nps);
            void spline(std::vector<math::float2>& sp, const math::float4& x, const math::float4& y, size_t np);
        };
    }
}

