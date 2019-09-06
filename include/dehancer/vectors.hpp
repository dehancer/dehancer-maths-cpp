//
// Created by denn nevera on 2019-09-01.
//

#pragma once

#include <armadillo>
#include "dehancer/properties.hpp"
#include "dehancer/details/observable_array.hpp"

namespace dehancer {

    namespace math {

        template<size_t N>
        class float_vector: public arma::fvec::fixed<N> {
            using armfloatN = arma::fvec::fixed<N>;
        public:
            using armfloatN::armfloatN;
            float_vector& operator=(const observable::Aproxy<float_vector> &a) {
                return *this = a.get_data();
            }
        };

        class float2: public float_vector<2> {

        public:

            using float_vector::float_vector;

            PROPERTY(x,
                     float,
                     float2,
                     { return (*this)[0];         }, // getter
                     {        (*this)[0] = value; }  // setter
            );

            PROPERTY(y,
                     float,
                     float2,
                     { return (*this)[1];         }, // getter
                     {        (*this)[1] = value; }  // setter
            );

            float2(const observable::Aproxy<float2> &a):float_vector(a.get_data()){}

        };

        class float3: public float_vector<3> {

        public:
            using float_vector::float_vector;

            PROPERTY(x,
                     float,
                     float3,
                     { return (*this)[0];         }, // getter
                     {        (*this)[0] = value; }  // setter
            );

            PROPERTY(y,
                     float,
                     float3,
                     { return (*this)[1];         }, // getter
                     {        (*this)[1] = value; }  // setter
            );

            PROPERTY(z,
                     float,
                     float3,
                     { return (*this)[2];         }, // getter
                     {        (*this)[2] = value; }  // setter
            );

            float3(const observable::Aproxy<float3> &a):float_vector(a.get_data()){}

        };

        class float4: public float_vector<4> {

        public:
            using float_vector::float_vector;

            PROPERTY(x,
                     float,
                     float4,
                     { return (*this)[0];         }, // getter
                     {        (*this)[0] = value; }  // setter
            );

            PROPERTY(y,
                     float,
                     float4,
                     { return (*this)[1];         }, // getter
                     {        (*this)[1] = value; }  // setter
            );

            PROPERTY(z,
                     float,
                     float4,
                     { return (*this)[2];         }, // getter
                     {        (*this)[2] = value; }  // setter
            );

            PROPERTY(w,
                     float,
                     float4,
                     { return (*this)[3];         }, // getter
                     {        (*this)[3] = value; }  // setter
            );

            float4(const observable::Aproxy<float3> &a):float_vector(a.get_data()){}
        };
    }
}