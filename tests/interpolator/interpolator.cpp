//
// Created by denn nevera on 2019-09-01.
//

#include "gtest/gtest.h"
#include "dehancer/math.hpp"
#include "../common/matlab_utils.hpp"
#include <memory>

dehancer::spline::Linear spline;

TEST(Interpolation, LinearTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;

    spline.controls = {{0,0},{0.1,0.2},{0.2,0.3},{0.3,0.4}, {0.5,0.7}, {0.8,0.8} ,{1,0.1}};

    spline.controls[1] = {0.1,0.25};

    std::cout << "Controls: \n" <<  spline.controls << std::endl;

    std::cout << "Test bounds: " << spline.test_bounds(0.5).value_or(-100) << std::endl;

    matlab::utils::print(spline, 1);


}

TEST(Interpolation, UtilsTest) {

    auto spline2 = dehancer::spline::make<dehancer::spline::Linear>(spline.controls, 256);

    matlab::utils::print(spline2, 2);

    auto curve = dehancer::curve::make<dehancer::spline::Linear>(spline.controls, 256);

    matlab::utils::print(curve, 3);
}

TEST(Interpolation, CubicUtilsTest) {

    auto curve1 = dehancer::spline::make<dehancer::spline::Cubic>(spline.controls, 256, 2);

    matlab::utils::print(curve1, 4);

    auto curve2 = dehancer::curve::make<dehancer::spline::Cubic>(spline.controls, 256, 1);

    matlab::utils::print(curve2, 5);
}

TEST(Interpolation, CatmulRomUtilsTest) {

    auto curve1 = dehancer::spline::make<dehancer::spline::CatmulRom>(spline.controls, 256, 0.2);

    matlab::utils::print(curve1, 6);

    auto curve2 = dehancer::curve::make<dehancer::spline::CatmulRom>(spline.controls, 256, 0.9);

    matlab::utils::print(curve2, 7);
}