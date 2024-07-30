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
            for (size_t i = 0; i <= spline.resolution; ++i) {
                auto x = (float)i*spline.step;
                std::cout << " " << x;
            }
            std::cout << "];" << std::endl;

            std::cout << "y = [";
            for (size_t i = 0; i <= spline.resolution; ++i) {
                auto x = (float)i*spline.step;
                std::cout << " " << spline.value(x);
            }
            std::cout << "];" << std::endl;
            std::cout << "figure("<<figure<<"); ";
            std::cout << "plot(x,y);" << std::endl;
        }

        static inline void print(const std::vector<dehancer::math::float2>& spline, int figure = 1) {

            std::cout << std::endl;

            std::cout << "% matlab script there: " << std::endl;
            std::cout << "x = [";
            for (auto xy: spline) {
                std::cout << " " << xy.x();
            }
            std::cout << "];" << std::endl;

            std::cout << "y = [";
            for (auto xy: spline) {
                std::cout << " " << xy.y();
            }
            std::cout << "];" << std::endl;
            std::cout << "figure("<<figure<<"); ";
            std::cout << "plot(x,y);" << std::endl;
        }

        static inline void print(const std::vector<float>& spline, int figure = 1) {

            if (spline.size()<1)
                return;

            std::cout << std::endl;

            std::cout << "% matlab script there: " << std::endl;
            std::cout << "x = [";

            auto step = float(1.0/float(spline.size()-1));
            for (size_t i = 0; i < spline.size(); ++i) {
                std::cout << " " << i*step;
            }
            std::cout << "];" << std::endl;

            std::cout << "y = [";
            for (auto y: spline) {
                std::cout << " " << y;
            }
            std::cout << "];" << std::endl;
            std::cout << "figure("<<figure<<"); ";
            std::cout << "plot(x,y);" << std::endl;
        }
    }
}