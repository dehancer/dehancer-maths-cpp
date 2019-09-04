//
// Created by denn nevera on 2019-09-03.
//

#include "dehancer/spline/matrix_based.hpp"

namespace dehancer {
    namespace spline {

        MatrixBased::MatrixBased(size_t resolution):Interpolator(resolution) {
            controls.on_update = [this](const std::vector<dehancer::math::float2>& cnts) {
                std::cout << " ... on update = \n";
                for (auto &v: cnts) {
                    std::cout << v.t() << ", ";
                }
                std::cout << std::endl;

                evaluate_curve();
            };
        }

        size_t MatrixBased::minimum_controls() const {
            return 4;
        }

        float MatrixBased::value(float x) const {
            auto y = test_bounds(x);
            if (y)                                   return *y;
            if (controls.size()<minimum_controls())  return x;
            return Interpolator::linear(curve_,x);
        }

        void MatrixBased::evaluate_curve() {

            curve_.clear();

            std::vector<size_t> nps;
            make_nps(nps);

            size_t ii = 0;

            for (int i = 0; i < cpn - (minimum_controls()-2) ; ++i) {
                dehancer::math::float2 p0 = controls[i-1];
                dehancer::math::float2 p1 = controls[i-0];
                dehancer::math::float2 p2 = controls[i+1];
                dehancer::math::float2 p3 = controls[i+2];
                dehancer::math::float4 px = math::float4({p0.x,p1.x,p2.x,p3.x});
                auto py = math::float4({p0.y,p1.y,p2.y,p3.y});
                auto s = spline(px, py, nps[ii]);

                ii += 1;

                std::copy (s.begin(), s.end(), std::back_inserter(curve_));
            }
        }

        std::vector<math::float2> MatrixBased::spline(math::float4 x, math::float4 y, size_t np) {
            auto u = arma::linspace(0,1,np);
            auto u2 = u%u;
            auto u3 = u2%u;
            std::vector<math::float2> s;
            for (int n = 0; n < np; ++n) {
                math::float4 t = {1, static_cast<float>(u(n)), static_cast<float>(u2[n]), static_cast<float>(u3[n])};
                auto tm = get_matrix() * t;
                math::float2 dt = {arma::dot(tm,x), arma::dot(tm,y)};
                s.push_back(dt);
            }
            return s;
        }

        void MatrixBased::make_nps(std::vector<size_t> &nps) {
            nps.clear();
            for (int i = 0; i < ni-1 ; ++i) {
                nps.push_back(npf+1);
            }
            nps[0] -= 1;
            nps.push_back(npl+1);
        }
    }
}