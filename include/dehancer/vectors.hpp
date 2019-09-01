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

            PROPERTY(float,x);
            PROPERTY(float,y);

            GET(x) { return (*this)(0); }
            SET(x) { (*this)(0) = value; }

            GET(y) { return (*this)(1); }
            SET(y) { (*this)(1) = value;}
        };

        class float3: public arma::fvec::fixed<3> {

            using armfloat3 = arma::fvec::fixed<3>;

        public:
            using armfloat3::armfloat3;

            PROPERTY(float,x);
            PROPERTY(float,y);
            PROPERTY(float,z);

            GET(x) { return (*this)(0); }
            SET(x) { (*this)(0) = value; }

            GET(y) { return (*this)(1); }
            SET(y) { (*this)(1) = value;}

            GET(z) { return (*this)(2); }
            SET(z) { (*this)(2) = value;}
        };

        class float4: public arma::fvec::fixed<4> {

            using armfloat4 = arma::fvec::fixed<4>;

        public:
            using armfloat4::armfloat4;

            PROPERTY(float,x);
            PROPERTY(float,y);
            PROPERTY(float,z);
            PROPERTY(float,w);

            GET(x) { return (*this)(0); }
            SET(x) { (*this)(0) = value; }

            GET(y) { return (*this)(1); }
            SET(y) { (*this)(1) = value;}

            GET(z) { return (*this)(2); }
            SET(z) { (*this)(2) = value;}

            GET(w) { return (*this)(3); }
            SET(w) { (*this)(3) = value;}
        };
    }
}