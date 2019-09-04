//
// Created by denn nevera on 2019-09-03.
//

#include "gtest/gtest.h"
#include "dehancer/math.hpp"
#include <memory>

TEST(Interpolation, BezierTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;


//    dehancer::observable::Array<dehancer::math::float2> a;
//
//    a.on_update = [](const std::vector<dehancer::math::float2>& vector){
//        std::cout << vector << std::endl;
//    };
//
//    a[0] = {1,42};
//    a[0] = {42,1};


    dehancer::spline::Bezier spline;

    spline.controls = {{0,0},{0.1,0.2},{0.2,0.3},{0.3,0.4}, {0.5,0.8} ,{1,0.1}};

    std::cout << "Controls: \n" <<  spline.controls << std::endl;

    std::cout << "Test bounds: " << spline.test_bounds(0.5).value_or(-100) << std::endl;

    for (int i = 0; i <= spline.resolution; ++i) {
        auto x = i*spline.step;
        std::cout << "i:["<<x<<"] = " << spline.value(i*spline.step) << std::endl;
    }
}