//
// Created by denn nevera on 2019-09-06.
//

#include "gtest/gtest.h"
#include "dehancer/math.hpp"
#include "../common/matlab_utils.hpp"

#include <memory>

std::vector<dehancer::math::float2> points = {
        {0,0},
        {0.1,0.2},
        {0.2,0.4},
        {0.5,0.7},
        {0.9,0.5},
        {1,0.3}
};

TEST(Interpolation, CatmulRomTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    auto spline = dehancer::spline::CatmulRom(points, 256, 0.5);

    matlab::utils::print(spline,1);
}
