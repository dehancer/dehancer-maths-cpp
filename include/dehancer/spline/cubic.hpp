//
// Created by denn nevera on 2019-09-06.
//

#pragma once

#include "dehancer/interpolator.hpp"

namespace dehancer {

    namespace spline {

        class Cubic: public math::protocol::Interpolator {

        public:
            using math::protocol::Interpolator::Interpolator;

            explicit Cubic(size_t resolution = 256, float second_derivative=1);
            explicit Cubic(const std::vector<math::float2>& controls, size_t resolution = 256, float second_derivative=1);

            void  set_second_derivative(float second_derivative);
            float get_second_derivative() const { return second_derivative_;}

            size_t minimum_controls() const override ;

            float value(float x) const override ;

            ~Cubic() override = default;
            
        private:
            std::vector<float> coeffs_;
            float second_derivative_;
            void update_coeffs();
        };
    }
}
