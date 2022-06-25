//
// Created by denn nevera on 2019-09-16.
//

#pragma once

#include "armadillo"
#include <vector>
#include <tuple>

namespace dehancer::math {

        /**
         * Histogram Channel
         */
        class Channel: public arma::frowvec {
        public:
            using arma::frowvec::frowvec;

            enum class Index:int {
                red = 0,
                green = 1,
                blue = 2,
                luma = 3
            };
            
            /**
             * Integrate channel
             * @param s - scale integrated values
             * @return the channel object
             */
            Channel& integrate(float s=1.0f);

            /**
             * Calculates single-precision vector threshold with signed constant to the specified range.
             *
             * @param lower - lower threshold
             * @param value - output constant
             * @return the channel object
             */
            Channel& threshold(float lower, float value);

            /**
             * Scale channel
             * @param value - maximum value
             * @return the channel object
             */
            Channel& scale(float value);

            /**
             * Clamp value
             * @param index
             * @param value
             * @return
             */
            Channel& clamp(int index, float value);

            /**
             * Counts and finds the zero crossings in a single-precision vector.
             * @param max_crossings - maximum number of crossings to find
             * @return [index,count] - index of last crossing found and total number of zero crossings found as a tuple
             */
            std::tuple<size_t,size_t> find_zero_crossings(size_t max_crossings = 1 );

            /**
             * Get the higher clipping value
             * @return value
             */
            float higher(float clipping);

            /**
            * Get the lower clipping value
            * @return value
            */
            float lower(float clipping);
        };

        /**
         * Histogram
         */
        class Histogram {

            struct Size {
                /**
                 * Histogram length (256 by default)
                 */
                std::size_t size;
                /**
                 * Number of channels
                 */
                std::size_t num_channels;
            };

        public:

            /**
             * Create an empty histogram
             * @param num_channels - channels number
             * @param size - histogram length
             */
            explicit Histogram(size_t num_channels=4, size_t size=256);

            /**
             * Create a histogram from raw data
             * @param buffer - vectors of channels
             */
            explicit Histogram(const std::vector<std::vector<float>>& buffer);

            /**
             * Update histogram from raw buffer
             * @param buffer
             */
            void update(const std::vector<std::vector<float>>& buffer);

            /**
             * Get histogram channels as vectors
             * @return channels
             */
            [[nodiscard]] const std::vector<Channel>& get_channels() const { return channels_; };

            /**
             * Get certain channel by index
             * @param i - channel index
             * @return channel
             */
            [[nodiscard]] Channel get_channel(int i) const;
    
            /**
             * Get certain channel by named index
             * @param i
             * @return channel
             */
            [[nodiscard]] Channel get_channel(Channel::Index i) const;
    
            /**
             * Histogram size
             * @return length and number of channels
             */
            [[nodiscard]] Size get_size() const { return size_; }

        private:
            Size                 size_;
            std::vector<Channel> channels_;

        };
    }
