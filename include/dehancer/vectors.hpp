//
// Created by denn nevera on 2019-09-01.
//

#pragma once

#include <armadillo>
#include "dehancer/properties.hpp"

namespace dehancer {

    namespace math {

        using float2x2 = arma::fmat::fixed<2,2>;
        using float3x3 = arma::fmat::fixed<3,3>;
        using float4x4 = arma::fmat::fixed<4,4>;

        class float2: public arma::fvec::fixed<2> {

            using armfloat2 = arma::fvec::fixed<2>;

        public:
            using armfloat2::armfloat2;

            DEFINE_PROPERTY(x,
                            float, float2,
                            { return (*self)(0) = value; }, // setter
                            { return (*self)(0); }          // getter
            );

            DEFINE_PROPERTY(y,
                            float, float2,
                            { return (*self)(1) = value; }, // setter
                            { return (*self)(1); }          // getter
            );
        };

        class float3: public arma::fvec::fixed<3> {

            using armfloat3 = arma::fvec::fixed<3>;

        public:
            using armfloat3::armfloat3;

            DEFINE_PROPERTY(x,
                            float, float3,
                            { return (*self)(0) = value; }, // setter
                            { return (*self)(0); }          // getter
            );

            DEFINE_PROPERTY(y,
                            float, float3,
                            { return (*self)(1) = value; }, // setter
                            { return (*self)(1); }          // getter
            );

            DEFINE_PROPERTY(z,
                            float, float3,
                            { return (*self)(2) = value; }, // setter
                            { return (*self)(2); }          // getter
            );

        };

        class float4: public arma::fvec::fixed<4> {

            using armfloat4 = arma::fvec::fixed<4>;

        public:
            using armfloat4::armfloat4;

            DEFINE_PROPERTY(x,
                            float, float4,
                            { return (*self)(0) = value; }, // setter
                            { return (*self)(0); }            // getter
            );

            DEFINE_PROPERTY(y,
                            float, float4,
                            { return (*self)(1) = value; }, // setter
                            { return (*self)(1); }            // getter
            );

            DEFINE_PROPERTY(z,
                            float, float4,
                            { return (*self)(2) = value; }, // setter
                            { return (*self)(2); }            // getter
            );

            DEFINE_PROPERTY(w,
                            float, float4,
                            { return (*self)(3) = value; }, // setter
                            { return (*self)(3); }            // getter
            );
        };
    }
}