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

                DEFINE_READONLY_PROPERTY(resolution,
                                         size_t, Interpolator,
                                         { return self->resolution_; } // getter
                );

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

            DEFINE_READONLY_PROPERTY(step,
                                     float, Interpolator,
                                     { return 1.0f/self->resolution; } // getter
            );

            virtual float value(float x) const { return 0; };
        };

    }
}

