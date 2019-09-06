//
// Created by denn nevera on 2019-09-06.
//

#pragma once

#include "dehancer/interpolator.hpp"
#include "dehancer/vectors.hpp"

namespace dehancer {

    namespace spline {

        std::vector<math::float2> make(const math::protocol::Interpolator& interpolator);

        template<class _Tp, class ..._Args>
        std::vector<math::float2> make(_Args&& ...__args)
        {
            static_assert( std::is_constructible<_Tp, _Args...>::value, "Can't construct object in make_shared" );
            auto spline = _Tp(__args ...);
            return spline::make(spline);
        }

    }

    namespace curve {
        std::vector<float> make(const math::protocol::Interpolator& interpolator);

        template<class _Tp, class ..._Args>
        std::vector<float> make(_Args&& ...__args)
        {
            static_assert( std::is_constructible<_Tp, _Args...>::value, "Can't construct object in make_shared" );
            auto spline = _Tp(__args ...);
            return curve::make(spline);
        }
    }
}
