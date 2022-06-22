//
// Created by denn nevera on 2019-08-15.
//

#pragma once

#include <vector>
#include <armadillo>
#include <iostream>
#include <memory>
#include <functional>

#include "dehancer/vectors.hpp"
#include "dehancer/details/optional.hpp"
#include "dehancer/scope_guard.hpp"
#include "dehancer/details/observable_array.hpp"

namespace dehancer::math {

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
                observable::Array<dehancer::math::float2> controls;

                /***
                 * Interpolation resolution
                 */
                READONLY_PROPERTY(resolution,
                                  size_t, Interpolator,
                                  { return this->resolution_; } // getter
                );

                /**
                 * Interpolation precision step
                 */
                READONLY_PROPERTY(step,
                                  float, Interpolator,
                                  { return 1.0f/this->resolution_; } // getter
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

                /***
                 * Minimal control points that must be set for the intrapolation method
                 * @return size
                 */
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
                 * Get linear interpolation for the x "time" over curve
                 * @param curve
                 * @param x
                 * @return
                 */
                static float linear(const std::vector<float2>& curve, float x);

                /***
                 * Create interpolation object
                 * @param resolution - interpolation resolution
                 */
                explicit Interpolator(size_t resolution = 256);

                explicit Interpolator(const std::vector<float2>& controls, size_t resolution = 256);

                virtual ~Interpolator() = default;

            private:
                size_t resolution_;
            };
        }
    }

