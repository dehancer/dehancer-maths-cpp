//
// Created by denn nevera on 2019-09-06.
//

#include "dehancer/spline/cubic.hpp"

namespace dehancer {
    namespace spline {

        Cubic::Cubic(size_t resolution, float second_derivative):
                Interpolator(resolution),
                coeffs_(),
                second_derivative_(second_derivative)
        {
            controls.on_update = [this](const std::vector<dehancer::math::float2>& cnts) {
                this->update_coeffs();
            };
        }

        Cubic::Cubic(const std::vector<dehancer::math::float2> &controlsIn, size_t resolution, float second_derivative)
                :Interpolator(controlsIn, resolution),
                 coeffs_()
        {
            set_second_derivative(second_derivative);
            controls.on_update = [this](const std::vector<dehancer::math::float2>& cnts) {
                this->update_coeffs();
            };
        }

        size_t Cubic::minimum_controls() const { return 3; }

        void Cubic::set_second_derivative(float second_derivative) {
            second_derivative_ = second_derivative;
            update_coeffs();
        }

        float Cubic::value(float x) const {

            auto Y = test_bounds(x);
            if (Y)                                   return *Y;
            if (controls.size()<minimum_controls())  return x;

            auto tm = indices(controls,x);
            size_t i0 = std::get<0>(tm);
            size_t i1 = std::get<1>(tm);

            float h  = controls[i1].x() - controls[i0].x();
            float x0 = x - controls[i0].x();
            float x1 = controls[i1].x() - x;

            float y = powf(x1,3) * coeffs_[i0] + powf(x0, 3) * coeffs_[i1];
            y = y/6/h;
            float z = coeffs_[i0]*x1 + coeffs_[i1]*x0;
            y = y - z*h/6;
            y = y + (controls[i0].y()*x1 + controls[i1].y()*x0)/h;

            return y;
        }

        void Cubic::update_coeffs() {

            if (controls.size()<minimum_controls())  return;

            try {

                auto n = controls.size();
                auto A = arma::fmat(n,n); A.zeros();
                auto B = arma::fmat(n,1); B.zeros();

                A(0,0)     = 2;
                A(n-1,n-1) = 2;
                A(0,1)     = 1;
                A(n-1,n-2) = 1;

                B(0,0)     = 0; // the first derivative == 1

                float h1   = 0;

                for (size_t i = 1; i <n-1 ; ++i) {

                    math::float2 p0 = controls[i-1];
                    math::float2 p1 = controls[i];
                    math::float2 p2 = controls[i+1];

                    auto h0 = p1.x() - p0.x();
                         h1 = p2.x() - p1.x();
                    auto h2 = p2.x() - p0.x();

                    if (h2 == 0) {
                        A(i,i-1) = 0;
                        A(i,i+1) = 0;
                        B(i,0)   = 0;
                    }
                    else {
                        A(i,i-1) = h0/h2;
                        A(i,i+1) = h1/h2;
                        float y   = p1.y();
                        float fx0 = (h0 == 0 ? 0 : (y-p0.y())/h0);
                        float fx1 = (h1 == 0 ? 0 : (p2.y()-y)/h1);
                        B(i,0)  = 6 * (fx1 - fx0) / h2;
                    }

                    A(i,i) = 2;
                }

                math::float2 p0 = controls[n-2];
                math::float2 p1 = controls[n-1];

                B(n-1,0) = 6 * (second_derivative_-(p1.y()-p0.y())/h1)/h1;

                arma::fmat x = arma::solve(A,B);

                auto col = x.col(0);

                coeffs_.resize(n+1);

                for (size_t i = 0; i < n; ++i) {
                    coeffs_[i] = col[i];
                }

                coeffs_[n] = 0;
            }
            catch (std::logic_error &e) {
                std::cerr << "Cubic spline logic error: " <<  e.what() << std::endl;
            }
            catch (std::exception &e) {
                std::cerr << "Cubic spline error: " <<  e.what() << std::endl;
            }
            catch (...) {
                std::cerr << "Cubic spline error: " <<  "unknown..." << std::endl;
            }
        }
    }
}