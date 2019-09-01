//
// Created by denn nevera on 2019-08-15.
//

#include "gtest/gtest.h"
#include "dehancer/interpolator.hpp"
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

};