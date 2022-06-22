//
// Created by denn nevera on 2019-09-16.
//

#include "dehancer/histogram.hpp"
#include <armadillo>

namespace dehancer::math {

        Histogram::Histogram(size_t num_channels, size_t size):
                size_({.size=size,.num_channels=num_channels}),
                channels_(num_channels)
        {
            for (int i = 0; i < size_.num_channels ; ++i) {
                channels_.resize(size);
            }
        }

        Histogram::Histogram(const std::vector<std::vector<float>>& buffer):
                size_({0,0}),
                channels_()
        {
            update(buffer);
        }

        void Histogram::update(const std::vector<std::vector<float>> &buffer) {
            channels_.resize(buffer.size());
            if (!buffer.empty()) {
                size_ = Size({.size=buffer[0].size(), .num_channels=buffer.size()});
                for (size_t i = 0; i < size_.num_channels; ++i) {
                    channels_[i] = arma::conv_to<arma::frowvec>::from(buffer[i]);
                }
            }
        }

        Channel& Channel::clamp(int index, float value) {
            if (index >= size()) return *this;
            if (index < 0 ) return *this;
            (*this)[index] = value;
            return *this;
        }

        Channel& Channel::integrate(float s) {
            Channel vec(*this);
            for (int i = 1; i < size() ; ++i) {
                vec(i) = vec(i-1) + s*(*this)(i);
            }
            *this = vec;
            return *this;
        }

        Channel& Channel::threshold(float lower, float value) {
            for (int n = 0; n < size(); ++n){
                if ((*this)[n] >= lower)
                    (*this)[n] = value;
                else
                    (*this)[n] = -value;
            }
            return *this;
        }

        template <typename T> int sign(T val) {
            return (T(0) < val) - (val < T(0));
        }

        Channel& Channel::scale(float value) {
            float max_ = this->max();
            transform([value,max_](float val){
                return val*value/max_;
            });
            return *this;
        }

        std::tuple<size_t,size_t> Channel::find_zero_crossings(size_t max_crossings) {
            size_t D = 0;
            size_t C = 0;

            auto& A = *this;

            for(size_t n = 1; n < size(); n++)
            {
                if( sign(A[n]) != sign(A[(n - 1)]) )
                {
                    D = D + 1;
                    if( D == max_crossings)
                    {
                        C = n ;
                        break;
                    }
                }
            }

            return std::make_tuple(C,D);
        }

        float Channel::higher(float clipping) {

            if (empty()) return 1;

            Channel vec(*this);

            auto ths = vec
                    .clamp(static_cast<int>(size()-1),0)
                    .integrate(1.0)
                    .scale(1.0)
                    .threshold(1.0-clipping, 1.0);

            auto [index, nums] = ths.find_zero_crossings(1);

            float high = index < size() ? static_cast<float>(index+1) : static_cast<float>(size());

            return high/static_cast<float>(size());
        }

        float Channel::lower(float clipping) {
            if (empty()) return 0;

            Channel vec(*this);

            auto ths = vec
                    .clamp(0,0)
                    .integrate(1.0)
                    .scale(1.0)
                    .threshold(clipping, 1.0);

            auto [index, nums] = ths.find_zero_crossings(1);

            float low = index > 0 ? static_cast<float>(index-1) : static_cast<float>(0);

            return low/static_cast<float>(size());

        }
    }
