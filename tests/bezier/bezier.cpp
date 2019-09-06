//
// Created by denn nevera on 2019-09-03.
//

#include "gtest/gtest.h"
#include "dehancer/math.hpp"
#include "../common/matlab_utils.hpp"

#include <memory>

std::vector<dehancer::math::float2> points = {
        {0,0},
        {0.2,0.4},
        {0.9,0.4},
        {1,1}
};

TEST(Interpolation, BezierTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    auto spline = dehancer::spline::Bezier(points);

    matlab::utils::print(spline,1);
}


TEST(Interpolation, BezierWithControlTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    auto spline = dehancer::spline::Bezier();

    spline.controls = points;

    matlab::utils::print(spline,2);
}