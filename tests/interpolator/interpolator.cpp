//
// Created by denn nevera on 2019-09-01.
//

#include "gtest/gtest.h"
#include "dehancer/math.hpp"
#include <memory>

TEST(Initial, IitialTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;

    dehancer::math::LinearInterpolator linear;

    linear.controls = {{0,0},{0.1,0.2},{0.2,0.3},{0.3,0.4}, {0.5,0.8} ,{1,0.1}};

    std::cout << "Controls: \n" <<  linear.controls << std::endl;

    std::cout << "Test bounds: " << linear.test_bounds(0.5).value_or(-100) << std::endl;

    for (int i = 0; i <= linear.resolution; ++i) {
        auto x = i*linear.step;
        std::cout << "i:["<<x<<"] = " << linear.value(i*linear.step) << std::endl;
    }
}