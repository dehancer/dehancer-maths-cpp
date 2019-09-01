//
// Created by denn nevera on 2019-08-15.
//

#pragma once

#include <vector>
#include <armadillo>
#include <iostream>

#include "dehancer/vectors.hpp"

namespace dehancer{

    namespace math {

        namespace protocol {

            class Interpolator {
            public:

                class __controls__
                {
                    std::vector<float2> value;
                    friend struct Interpolator;
                public:
                    std::vector<float2>& operator= (const std::vector<float2>& vec) { return (value = vec); }
                    operator std::vector<float2>() const { return value; }
                    friend std::ostream& operator<<(std::ostream& os, const __controls__ & controls);
                } controls;

                READONLY_PROPERTY(size_t,resolution);
                GET(resolution) {
                    return resolution_;
                }

                Interpolator(size_t resolution = 256):resolution_(resolution){};
                virtual float value(float x) const = 0;
                virtual ~Interpolator(){}

            private:
                size_t resolution_;
            };
        }

        class Interpolator: public protocol::Interpolator {

        public:
            using protocol::Interpolator::Interpolator;
            READONLY_PROPERTY(size_t,step);
            GET(step) {
                return 1.0f/this->resolution;
            }
        };

    }
}

