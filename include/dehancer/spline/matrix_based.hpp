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

            virtual size_t minimum_controls() const;

            virtual float value(float x) const;

            virtual math::float4x4& get_matrix() const = 0;

        private:
            std::vector<math::float2> spline(math::float4 x, math::float4 y, size_t np);
            void evaluate_curve();
            void make_nps(std::vector<size_t>& nps);

            std::vector<math::float2> curve_;

            DEFINE_READONLY_PROPERTY(cpn,
                                     size_t , MatrixBased,
                                     { return self->controls.size(); } // getter
            );

            DEFINE_READONLY_PROPERTY(ni,
                                     size_t , MatrixBased,
                                     { return self->cpn - (self->minimum_controls()-1); } // getter
            );

            DEFINE_READONLY_PROPERTY(n,
                                     size_t , MatrixBased,
                                     { return self->resolution; } // getter
            );

            //
            // Points in every intervals between 1 and n-1
            //
            DEFINE_READONLY_PROPERTY(npf,
                                     size_t , MatrixBased,
                                     { return self->n/self->ni; } // getter
            );

            //
            // Points in the last interval
            //
            DEFINE_READONLY_PROPERTY(npl,
                                     size_t , MatrixBased,
                                     { return self->n - (self->npf * (self->ni - 1)); } // getter
            );
        };

    }
}