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
#include "dehancer/optional.hpp"
#include "dehancer/scope_guard.hpp"

namespace dehancer{

    namespace math {

        using namespace tl;

        struct Bounds {
            float2 left;
            float2 right;
        };

        namespace protocol {

            using Handler  = std::function<void(const std::vector<float2>&)>;

            struct auto_lf {
                std::function< void() > _lambda;
                template< typename RET, typename ... ARGS >
                inline auto_lf( RET F( ARGS... ),  ARGS... args ) : _lambda{ [ F, args... ] { F( args... ); } } {}
                inline auto_lf( std::function< void() >&& func ) : _lambda{ std::move( func ) } {}
                inline ~auto_lf() { _lambda(); }
            };

            class Interpolator {
            public:

                /***
                 * Control points
                 */
                struct __controls__
                {

                public:

                    Handler on_update = nullptr;

                    std::vector<float2>& operator= (const std::vector<float2>& vec);

                    operator std::vector<float2>() const;

                    float2& operator[] (int index);

                    float2  operator[] (int index) const;

                    size_t  size() const { return value.size(); }

                    friend std::ostream& operator<<(std::ostream& os, const __controls__ & controls);

                private:
                    std::vector<float2> value;

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
                 * Create interpolation object
                 * @param resolution - interpolation resolution
                 */
                Interpolator(size_t resolution = 256);

                virtual ~Interpolator();

            private:
                size_t resolution_;
            };
        }
    }

    namespace spline {

        class Linear: public math::protocol::Interpolator {

        public:
            using math::protocol::Interpolator::Interpolator;
            virtual size_t minimum_controls() const;
            virtual float value(float x) const;
        };
    }
}

