//
// Created by denn nevera on 2019-09-03.
//
#pragma once

#include "dehancer/interpolator.hpp"
#include "dehancer/matrix.hpp"

namespace dehancer {

    namespace spline {

        class MatrixBased: public math::protocol::Interpolator {

        public:
            using math::protocol::Interpolator::Interpolator;

            MatrixBased(size_t resolution = 256);
            MatrixBased(const std::vector<dehancer::math::float2>& controls, size_t resolution = 256);

            virtual size_t minimum_controls() const;

            virtual float value(float x) const;

            virtual math::float4x4& get_matrix() const = 0;

            void evaluate_curve();

        private:
            std::vector<math::float2> spline(math::float4 x, math::float4 y, size_t np);
            void make_nps(std::vector<size_t>& nps);

            std::vector<math::float2> curve_;

            READONLY_PROPERTY(cpn,
                              size_t , MatrixBased,
                              { return this->controls.size(); } // getter
            );

            READONLY_PROPERTY(ni,
                              size_t , MatrixBased,
                              { return this->cpn - (this->minimum_controls()-1); } // getter
            );

            READONLY_PROPERTY(n,
                              size_t , MatrixBased,
                              { return this->resolution; } // getter
            );

            //
            // Points in every intervals between 1 and n-1
            //
            READONLY_PROPERTY(npf,
                              size_t , MatrixBased,
                              { return this->n/this->ni; } // getter
            );

            //
            // Points in the last interval
            //
            READONLY_PROPERTY(npl,
                              size_t , MatrixBased,
                              { return this->n - (this->npf * (this->ni - 1)); } // getter
            );
        };

    }
}