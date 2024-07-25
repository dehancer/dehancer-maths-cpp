//
// Created by denn nevera on 2019-09-05.
//

#include "gtest/gtest.h"
#include "dehancer/math.hpp"
#include <memory>

TEST(Initial, VectorFloat2Test) {

    std::cerr << std::endl;
    std::cout << std::endl;

    std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;

    auto v = dehancer::math::float2({1,2});

    std::cout << "\nfloat2:" << std::endl;
    std::cout << v << std::endl;

    v.y() = 10;
    v.y = 11;

    std::cout << v.y() << std::endl;
    std::cout << v.y - v.x << std::endl;
}

TEST(Initial, VectorFloat3Test) {

    std::cerr << std::endl;
    std::cout << std::endl;

    std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;

    auto v = dehancer::math::float3({1,2,3});

    std::cout << "\nfloat3:" << std::endl;
    std::cout << v << std::endl;

    v.y() = 10;
    v.y = 11;
    v.z() = 1;
    v.z = 3;

    std::cout << v.y() << std::endl;
    std::cout << v.y - v.x - v.z << std::endl;

}

TEST(Initial, VectorFloat4Test) {

    std::cerr << std::endl;
    std::cout << std::endl;

    std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;

    auto v = dehancer::math::float4({1,2,3,4});

    std::cout << "\nfloat4:" << std::endl;
    std::cout << v << std::endl;

    v.y() = 10;
    v.y = 11;
    v.z() = 1;
    v.z = 3;
    v.w() = 1;
    v.w = 4;

    std::cout << v.y() << std::endl;
    std::cout << v.y - v.x - v.z - v.w << std::endl;

    std::cout <<"dot " << arma::dot(arma::eps(v - v), dehancer::math::float4(arma::fill::ones) ) << std::endl;

}
