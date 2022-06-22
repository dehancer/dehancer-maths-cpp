//
// Created by denn nevera on 2019-09-04.
//

#pragma once

#include "dehancer/interpolator.hpp"

namespace dehancer {

    namespace spline {
        class Linear: public math::protocol::Interpolator {

        public:
            using math::protocol::Interpolator::Interpolator;

            size_t minimum_controls() const override;
            float value(float x) const override;
        };
    }
}
