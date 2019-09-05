//
// Created by denn nevera on 2019-09-03.
//

#include "dehancer/spline/matrix_based.hpp"

namespace dehancer {
    namespace spline {

        MatrixBased::MatrixBased(size_t resolution):
                Interpolator(resolution),
                curve_()
        {
            controls.on_update = [this](const std::vector<dehancer::math::float2>& cnts) {
                this->evaluate_curve();
            };
        }

        MatrixBased::MatrixBased(const std::vector<dehancer::math::float2> &controlsIn, size_t resolution):
                Interpolator(controlsIn, resolution),
                curve_()
        {
            controls.on_update = [this](const std::vector<dehancer::math::float2>& cnts) {
                this->evaluate_curve();
            };
        }

        float MatrixBased::value(float x) const {
            auto y = test_bounds(x);
            if (y)                                   return *y;
            if (controls.size()<minimum_controls())  return x;
            return linear(curve_,x);
        }

        size_t MatrixBased::minimum_controls() const {
            return 4;
        }

        void MatrixBased::spline(std::vector<math::float2>& sp, const math::float4& x, const math::float4& y, size_t np) const {

            arma::vec u  = arma::linspace(0,1,np);
            arma::vec u2 = arma::pow(u,2);
            arma::vec u3 = arma::pow(u,3);

            sp.clear();
            sp.resize(np);

            for (int n = 0; n < np; ++n) {

                math::float4 t = {1, static_cast<float>(u[n]), static_cast<float>(u2[n]), static_cast<float>(u3[n])};

                auto tm =  t.t() * this->get_matrix() ;

                sp[n] = {arma::dot(tm,x), arma::dot(tm,y)};
            }
        }

        void MatrixBased::make_nps(std::vector<size_t> &nps) const {

            auto cpn = controls.size();
            auto ni  = cpn - (minimum_controls()-1);
            auto npf = resolution/ni;
            auto npl = resolution - (npf * (ni - 1));

            nps.clear();
            for (int i = 0; i < ni-1 ; ++i) {
                nps.push_back(npf+1);
            }
            nps.push_back(npl+1);
            nps[0] -= 1;

        }

        void MatrixBased::evaluate_curve() {

            curve_.clear();

            std::vector<size_t> nps;
            make_nps(nps);

            size_t ii = 0;
            std::vector<math::float2> s;

            auto icount = controls.size() - (minimum_controls()-2);

            for (int i = 1; i < icount ; ++i) {

                math::float2 p0 = controls[i-1];
                math::float2 p1 = controls[i-0];
                math::float2 p2 = controls[i+1];
                math::float2 p3 = controls[i+2];

                math::float4 px({p0.x,p1.x,p2.x,p3.x});
                math::float4 py({p0.y,p1.y,p2.y,p3.y});

                spline(s, px, py, nps[ii]);

                ii += 1;

                std::copy (s.begin(), s.end(), std::back_inserter(curve_));
            }
        }
    }
}