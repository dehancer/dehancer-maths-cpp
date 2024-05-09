//
// Created by denn nevera on 2019-09-03.
//
#pragma once

#include "dehancer/interpolator.hpp"
#include "dehancer/matrix.hpp"

namespace dehancer::spline {

    namespace detail {
        struct matrix_interpolator;
    }

    class MatrixBased: public math::protocol::Interpolator {

    public:
        using math::protocol::Interpolator::Interpolator;

        explicit MatrixBased(size_t resolution = 256);

        explicit MatrixBased(const std::vector<math::float2>& controls, size_t resolution = 256);

        ~MatrixBased() override = default;

        [[nodiscard]] size_t minimum_controls() const override ;

        [[nodiscard]] float value(float x) const override ;

        [[nodiscard]] virtual const math::float4x4& get_matrix() const = 0;

    protected:
        void evaluate_curve() ;

    private:
        std::vector<math::float2> curve_;
        void make_nps(std::vector<size_t>& nps) const ;
        void spline(std::vector<math::float2>& sp, const math::float4& x, const math::float4& y, size_t np) const ;
    };

}
