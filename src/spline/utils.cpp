//
// Created by denn nevera on 2019-09-06.
//

#include "dehancer/spline/utils.hpp"

namespace dehancer {
    namespace spline {
        std::vector<math::float2> make(const math::protocol::Interpolator& interpolator){
            std::vector<math::float2> vector; vector.resize(interpolator.resolution+1);
            for (int i = 0; i <= interpolator.resolution; ++i) {
                math::float2 point;
                point.x() = i*interpolator.step;
                point.y() = interpolator.value(point.x());
                vector[i] = point;
            }
            return vector;
        }
    }

    namespace curve {
        std::vector<float> make(const math::protocol::Interpolator& interpolator){
            std::vector<float> vector; vector.resize(interpolator.resolution+1);
            for (int i = 0; i <= interpolator.resolution; ++i) {
                auto x = i*interpolator.step;
                vector[i] = interpolator.value(x);
            }
            return vector;
        }
    }
}