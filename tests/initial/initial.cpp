//
// Created by denn nevera on 2019-08-15.
//

#include "gtest/gtest.h"
#include "dehancer/math.hpp"
#include <memory>

TEST(Initial, IitialTest) {

    std::cerr << std::endl;
    std::cout << std::endl;

    std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;

    arma::mat A = { {1, 3},
                    {2, 4} };

    arma::mat B = { {5, 6},
                    {7, 8} };

    auto x = arma::solve(A,B);

    std::cout << "Armadillo equation solution: \n" << x << std::endl;

    auto invA = arma::inv(A);
    auto xx = invA*B;

    std::cout << "Armadillo equation inv solution: \n" << xx << "\n < \n"<<  (xx == x) << std::endl;

    dehancer::math::float2 f = {1,2};

    f.x  = 1;
    f.y /= 2;
    std::cout << "Armadillo vector: \n" << f.t() << std::endl;

    auto a = f.t()*A;

    std::cout << "Armadillo multiple: \n" << a << std::endl;

    dehancer::math::float3 f3 = {1,2,1};

    auto a3x3 = f3*f3.t();

    std::cout << "Armadillo multiple 3x3: \n" << a3x3 << std::endl;

}