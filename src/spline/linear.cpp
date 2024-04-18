//
// Created by denn nevera on 2019-09-04.
//

#include "dehancer/spline/linear.hpp"

namespace dehancer::spline {
    float Linear::value(float x) const {
        auto y = test_bounds(x);
        if (y)                                   return *y;
        if (controls.size()<minimum_controls())  return x;
        return linear(x);
    }

    size_t Linear::minimum_controls() const {
        return 1;
    }
}
