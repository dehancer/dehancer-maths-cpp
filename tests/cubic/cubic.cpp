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

std::vector<dehancer::math::float2> points2 = {
        {0,0},
        {0.1,0.2},
        {0.5,0.5},
        {0.9,0.5},
        {1,1}
};

TEST(Interpolation, CubicSplineTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    auto spline = dehancer::spline::Cubic();

    spline.controls = points;

    matlab::utils::print(spline,1);

    spline.controls = points2;

    matlab::utils::print(spline,2);

}
