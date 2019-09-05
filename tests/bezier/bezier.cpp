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

    dehancer::spline::Bezier spline({
                                            {0,0},
                                            {0.2,0.4},
                                            {0.9,0.6},
                                            {1,1}
                                    });

    std::cout << "Controls: \n" <<  spline.controls << std::endl;

    spline.evaluate_curve();

    std::cout << "! matlab script there: " << std::endl;
    std::cout << "x = [";
    for (int i = 0; i <= spline.resolution; ++i) {
        auto x = i*spline.step;
        std::cout << " " << x;
    }
    std::cout << "];"<< std::endl;

    std::cout << "y = [";
    for (int i = 0; i <= spline.resolution; ++i) {
        auto x = i*spline.step;
        std::cout << " " << spline.value(x);
    }
    std::cout << "];" << std::endl;
    std::cout << "plot(x,y);" << std::endl;
}