//
// Created by denn nevera on 2019-08-15.
//

#include "dehancer/interpolator.hpp"

namespace dehancer {

    namespace math {

        namespace protocol {

            std::ostream& operator<<(std::ostream &os,
                                     const dehancer::math::protocol::Interpolator::__controls__ &controls) {
                for (auto &v: controls.value) {
                    os << v.t();
                }
                return os;
            }

            std::vector<float2>& Interpolator::__controls__::operator = (const std::vector<float2>& vec) {
                value = vec;
                if (on_update) {
                    on_update(value);
                }
                return value;
            }

            Interpolator::__controls__::operator std::vector<float2>() const {
                return value;
            }

            float2& Interpolator::__controls__::operator[](int index) {

                int _index = index;

                if (value.empty()) {
                    value.push_back({0,0});
                    _index = 0;
                }

                if (_index<0) _index = 0;

                if (index>=value.size()) _index = value.size()-1;

                if (on_update) {
                    //auto_lf([this](){on_update(value);});
                    auto guard = make_scope_guard([this](){
                        std::cout << " ... on update 0 = \n";
                        on_update(value);
                    });
                    std::cout << " ... on update 1 = \n";
                    return value[_index];
                }
                std::cout << " ... on update 1 = \n";
                return value[_index];
            }

            float2 Interpolator::__controls__::operator[](int index) const {
                if (value.empty()) return {0,0};
                if (index<0) return value[0];
                if (index>=value.size()) return value[value.size()-1];
                return value[index];
            }

            Interpolator::Interpolator(size_t resolution):resolution_(resolution)
            {
                controls.on_update = [](const std::vector<float2>& cnts) {
                    std::cout << " ... on update = \n";
                    for (auto &v: cnts) {
                        std::cout << v.t() << ", ";
                    }
                    std::cout << std::endl;
                };
            }

            Interpolator::~Interpolator(){}

            float Interpolator::linear(float x) const {

                auto tm = indices(x);
                auto k1 = std::get<0>(tm);
                auto k2 = std::get<1>(tm);

                auto P0 = this->controls[k1];
                auto P1 = this->controls[k2];

                auto d = P1.x - P0.x;
                auto t = d == 0 ? 0 : (x-P0.x)/d;

                return (1 - t) * P0.y + t * P1.y;
            }

            std::tuple<std::size_t,std::size_t> Interpolator::indices(float x) const {
                return Interpolator::indices(controls,x);
            }

            Bounds Interpolator::get_bounds() const {
                return {{0,0},{1,1}};
            }

            optional<float> Interpolator::test_bounds(float x) const {
                auto bounds = get_bounds();
                if (bounds.left.x>x)  { return make_optional(bounds.left.y); }
                if (bounds.right.x<x) { return make_optional(bounds.right.y); }
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

                    if (controls[i].x > x ) { right = i; }
                    else                    { left  = i; }
                }

                return std::make_tuple(left,right);
            }
        }
    }

    namespace spline {

        float Linear::value(float x) const {
            auto y = test_bounds(x);
            if (y)                                   return *y;
            if (controls.size()<minimum_controls())  return x;
            return linear(x);
        }

        size_t Linear::minimum_controls() const {
            return 1;
        }
    }
}
