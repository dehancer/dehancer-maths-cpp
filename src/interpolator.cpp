//
// Created by denn nevera on 2019-08-15.
//

#include "dehancer/interpolator.hpp"

namespace dehancer {

    namespace math {

        namespace protocol {

            Interpolator::Interpolator(size_t resolution):resolution_(resolution){}

            Interpolator::Interpolator(const std::vector<dehancer::math::float2> &controlsIn, size_t resolution):resolution_(resolution)
            {
                controls = controlsIn;
            }

            Interpolator::~Interpolator(){}

            float Interpolator::linear(float x) const {
                return linear(controls,x);
            }

            float Interpolator::linear(const std::vector<dehancer::math::float2> &curve, float x) {
                auto tm = Interpolator::indices(curve,x);
                auto k1 = std::get<0>(tm);
                auto k2 = std::get<1>(tm);

                float2 P0 = curve[k1];
                float2 P1 = curve[k2];

                float d = P1.x() - P0.x();
                auto t = d == 0 ? 0 : (x-P0.x())/d;

                return (1 - t) * P0.y() + t * P1.y();
            }

            std::tuple<std::size_t,std::size_t> Interpolator::indices(float x) const {
                return Interpolator::indices(controls,x);
            }

            Bounds Interpolator::get_bounds() const {
                return {{0,0},{1,1}};
            }

            optional<float> Interpolator::test_bounds(float x) const {
                auto bounds = get_bounds();
                if (bounds.left.x()>x)  { return make_optional(bounds.left.y()); }
                if (bounds.right.x()<x) { return make_optional(bounds.right.y()); }
                return nullopt;
            }

            std::tuple<std::size_t,std::size_t> Interpolator::indices(
                    const std::vector<dehancer::math::float2> &controls,
                    float x)
            {
                size_t left  = 0;
                size_t right = controls.size()-1;

                while ( right-left > 1) {

                    auto i = size_t(floor(double(right+left)/2.0));

                    const float p = controls[i][0];

                    if (p > x ) { right = i; }
                    else        { left  = i; }
                }

                return std::make_tuple(left,right);
            }
        }
    }

    namespace spline {


    }
}
