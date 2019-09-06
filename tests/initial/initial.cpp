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

    dehancer::observable::Array<dehancer::math::float2> array;

    array.on_update = [](const std::vector<dehancer::math::float2>& vector){
        std::cout << vector << std::endl;
    };

    array[0] = {1,42};
    array[0] = {42,1};

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

    f.x()  = 10;
    f.y() /= 2 + f.y();
    std::cout << "Armadillo vector: \n" << f.t() << std::endl;

    auto a = f.t()*A;

    std::cout << "Armadillo multiple: \n" << a << std::endl;

    dehancer::math::float3 f3 = {1,2,1};

    f3.x = 2;
    f3.y = 1;

    std::cout << "Armadillo f3: \n" << f3 << std::endl;

    auto a3x3 = f3*f3.t();

    std::cout << "Armadillo multiple 3x3: \n" << a3x3 << std::endl;

}