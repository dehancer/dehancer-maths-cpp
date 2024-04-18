//
// Created by denn nevera on 2019-09-04.
//

#pragma once

#include "dehancer/interpolator.hpp"

namespace dehancer::spline {
    class Linear: public math::protocol::Interpolator {

    public:
        using math::protocol::Interpolator::Interpolator;
        [[nodiscard]] size_t minimum_controls() const override;
        [[nodiscard]] float value(float x) const override;
    };
}

