//
// Created by denn nevera on 2019-09-01.
//

#pragma once

#include <armadillo>
#include "dehancer/properties.hpp"
#include "dehancer/details/observable_array.hpp"

namespace dehancer::math {

        /**
         * N-dimensions column float vector
         * @tparam N
         */
        template<size_t N>
        class float_vector: public arma::fvec::fixed<N> {
            using armfloatN = arma::fvec::fixed<N>;
        public:
            using armfloatN::armfloatN;
            float_vector& operator=(const observable::Aproxy<float_vector> &a) {
                return *this = a.get_data();
            }
        };

        /**
         * 2-dimensions column float vector
         */
        class float2: public float_vector<2> {

        public:

            using float_vector::float_vector;

            float& x() { return (*this)[0]; };
            const float& x() const { return (*this)[0]; };

            float& y() { return (*this)[1]; };
            const float& y() const { return (*this)[1]; };

            float2(const observable::Aproxy<float2> &a):float_vector(a.get_data()){}
        };

        /**
        * 3-dimensions column float vector
        */
        class float3: public float_vector<3> {

        public:
            using float_vector::float_vector;

            float& x() { return (*this)[0]; };
            const float& x() const { return (*this)[0]; };

            float& y() { return (*this)[1]; };
            const float& y() const { return (*this)[1]; };

            float& z() { return (*this)[2]; };
            const float& z() const { return (*this)[2]; };

            float3(const observable::Aproxy<float3> &a):float_vector(a.get_data()){}

        };

        /**
        * 4-dimensions column float vector
        */
        class float4: public float_vector<4> {

        public:
            using float_vector::float_vector;

            float& x() { return (*this)[0]; };
            const float& x() const { return (*this)[0]; };

            float& y() { return (*this)[1]; };
            const float& y() const { return (*this)[1]; };

            float& z() { return (*this)[2]; };
            const float& z() const { return (*this)[2]; };

            float& w() { return (*this)[3]; };
            const float& w() const { return (*this)[3]; };

            float4(const observable::Aproxy<float4> &a):float_vector(a.get_data()){}
        };
    }