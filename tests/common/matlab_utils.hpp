//
// Created by denn nevera on 2019-09-06.
//

#pragma once

#include "dehancer/interpolator.hpp"

namespace matlab {
    namespace utils {
        static inline void print(const dehancer::math::protocol::Interpolator& spline, int figure = 1) {

            std::cout << std::endl;

            std::cout << "% matlab script there: " << std::endl;
            std::cout << "x = [";
            for (int i = 0; i <= spline.resolution; ++i) {
                auto x = i*spline.step;
                std::cout << " " << x;
            }
            std::cout << "];" << std::endl;

            std::cout << "y = [";
            for (int i = 0; i <= spline.resolution; ++i) {
                auto x = i*spline.step;
                std::cout << " " << spline.value(x);
            }
            std::cout << "];" << std::endl;
            std::cout << "figure("<<figure<<"); ";
            std::cout << "plot(x,y);" << std::endl;
        }
    }
}