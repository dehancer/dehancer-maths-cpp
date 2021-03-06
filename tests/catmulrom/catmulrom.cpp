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

//        {0,     0},
//        {0.8,   0.6},
//        {0.95,  0.95},
//        {1,     1}

        {0,     0},
        {0.01,  0.01},
        {0.02,  0.02},
        {0.2,   0.35},
        {0.8,   0.8},
        {0.9,   0.9},
        {0.99,  0.99},
        {1,     1}

};

class ExposureCatmulRom: public dehancer::spline::CatmulRom {
public:
public:
    using dehancer::spline::CatmulRom::CatmulRom;
    ExposureCatmulRom(const std::vector<dehancer::math::float2>& controls) :
            dehancer::spline::CatmulRom(controls,256,0.7) {}
};


TEST(Interpolation, CatmulRomTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    auto spline = ExposureCatmulRom(points);

    matlab::utils::print(spline,1);
}
