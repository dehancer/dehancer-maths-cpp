//
// Created by denn nevera on 2019-08-15.
//

#include "dehancer/interpolator.hpp"

namespace dehancer {

    namespace math {

        namespace protocol {
            std::ostream& operator<<(std::ostream &os,
                                                  const dehancer::math::Interpolator::__controls__ &controls) {
                for (auto &v: controls.value) {
                    os << v.t();
                }
                return os;
            }

//            std::ostream& operator<<(std::ostream &os,
//                                     const dehancer::math::Interpolator::TYPE(controls)& controls) {
//                for (auto &v: controls) {
//                    os << v.t();
//                }
//                return os;
//            }
        }

    }
}
