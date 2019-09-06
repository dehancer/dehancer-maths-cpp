//
// Created by denn nevera on 2019-09-01.
//

#include "gtest/gtest.h"
#include "dehancer/math.hpp"
#include "../common/matlab_utils.hpp"
#include <memory>

TEST(Interpolation, LinearTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;

    dehancer::spline::Linear spline;

    spline.controls = {{0,0},{0.1,0.2},{0.2,0.3},{0.3,0.4}, {0.5,0.8} ,{1,0.1}};

    spline.controls[1] = {0.1,0.25};

    std::cout << "Controls: \n" <<  spline.controls << std::endl;

    std::cout << "Test bounds: " << spline.test_bounds(0.5).value_or(-100) << std::endl;

    matlab::utils::print(spline);
}