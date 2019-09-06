//
// Created by denn nevera on 2019-09-05.
//

#include "gtest/gtest.h"
#include "dehancer/math.hpp"
#include <memory>

TEST(Initial, IitialTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;

    auto v = dehancer::math::float2({1,2});

    v.y() = 10;

    std::cout << v << std::endl;
    std::cout << v.y() << std::endl;
}
