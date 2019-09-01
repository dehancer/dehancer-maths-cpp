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

    dehancer::math::Interpolator linear;

    linear.controls = {{0.1,0.2},{0.2,0.3},{0.3,0.4}};

    std::cout << "Controls: \n" <<  linear.controls;

}