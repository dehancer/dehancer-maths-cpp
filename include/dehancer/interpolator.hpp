//
// Created by denn nevera on 2019-08-15.
//

#pragma once

#include <vector>
#include <armadillo>
#include <iostream>
#include <memory>

#include "dehancer/vectors.hpp"
#include "dehancer/optional.hpp"

namespace dehancer{

    namespace math {

        using namespace tl;

        struct Bounds {
            float2 left;
            float2 right;
        };

        namespace protocol {

            class Interpolator {
            public:

                /***
                 * Control points
                 */
                struct __controls__
                {
                private:
                    std::vector<float2> value;
                public:

                    std::vector<float2>& operator= (const std::vector<float2>& vec) { return (value = vec); }
                    operator std::vector<float2>() const { return value; }
                    float2& operator[] (int index);
                    float2  operator[] (int index) const;
                    size_t  size() const { return value.size(); }
                    friend std::ostream& operator<<(std::ostream& os, const __controls__ & controls);
                } controls;

                /***
                 * Interpolation resolution
                 */
                DEFINE_READONLY_PROPERTY(resolution,
                                         size_t, Interpolator,
                                         { return self->resolution_; } // getter
                );

                /**
                 * Interpolation precision step
                 */
                DEFINE_READONLY_PROPERTY(step,
                                         float, Interpolator,
                                         { return 1.0f/self->resolution_; } // getter
                );

                /***
                 * Lerp value
                 * @param x - current "time"
                 * @return interpolated value
                 */
                virtual float value(float x) const = 0;

                /***
                 * Get linear interpolation for the x "time"
                 * @param x - "time"
                 * @return interpolated value
                 */
                virtual float linear(float x) const;

                /***
                 * Test bounds for the x "time"
                 * @return return nullopt if x is within bounds or closest bound
                 */
                virtual optional<float> test_bounds(float x) const;

                /**
                 * Interpolation bounds
                 * @return by default 0,0:1,1
                 */
                virtual Bounds get_bounds() const;

                virtual size_t minimum_controls() const = 0;

                /***
                 * Get indices for the current interpolation control points
                 * @param x - "time"
                 * @return
                 */
                virtual std::tuple<std::size_t,std::size_t> indices(float x) const ;

                /***
                 * Return indices of piece on linear cut from any controls sequence
                 * @param controls - control points
                 * @param x - "time"
                 * @return start/end indices
                 */
                static std::tuple<std::size_t,std::size_t> indices(const std::vector<float2>& controls, float x);

                /***
                 * Create interpolation object
                 * @param resolution - interpolation resolution
                 */
                Interpolator(size_t resolution = 256):resolution_(resolution){};
                virtual ~Interpolator(){}

            private:
                size_t resolution_;
            };
        }

        class LinearInterpolator: public protocol::Interpolator {

        public:
            using protocol::Interpolator::Interpolator;
            virtual size_t minimum_controls() const;
            virtual float value(float x) const;
        };

    }
}

