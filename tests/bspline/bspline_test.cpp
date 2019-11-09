//
// Created by denn nevera on 2019-09-06.
//

#include "gtest/gtest.h"
#include "dehancer/math.hpp"
#include "../common/matlab_utils.hpp"

#include <memory>

std::vector<dehancer::math::float2> points = {
//        {0,0},
//        {0.1,0.2},
//        {0.2,0.4},
//        {0.5,0.7},
//        {0.9,0.5},
//        {1,0.3}

        {0,     0},
        {0,     0},
        {0.8,   0.65},
        {0.98,  0.98},
        {1,     1},
        {1,     1}

//        {0,     0},
//        {0,     0},
//        {0.01,  0.01},
//        {0.2,   0.35},
//        {1,     1},
//        {1,     1}

};

class ExposureSpline: public dehancer::spline::CatmulRom {
public:
public:
    using dehancer::spline::CatmulRom::CatmulRom;
    ExposureSpline(const std::vector<dehancer::math::float2>& controls) :
            dehancer::spline::CatmulRom(controls, 256, 0.5) {}
};


TEST(Interpolation, CatmulRomTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    auto spline = ExposureSpline(points);

    matlab::utils::print(spline,1);
}
