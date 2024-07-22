//
// Created by denn nevera on 2019-09-01.
//

#pragma once

#include <armadillo>
#include "dehancer/properties.hpp"
#include "dehancer/details/observable_array.hpp"

namespace dehancer::math {

    /**
     * N-dimensions column float vector
     * @tparam N
     */
    template<size_t N>
    class float_vector: public arma::fvec::fixed<N> {
        using armfloatN = arma::fvec::fixed<N>;
    public:
        using armfloatN::armfloatN;
        float_vector& operator=(const observable::Aproxy<float_vector> &a) {
            *this = a.get_data(); return *this;
        }
    };

    template <typename T> class Property {
        T value;
    public:
        T & operator = (const T &i) {
            value = i; return value;
        }
        // This template class member function template serves the purpose to make
        // typing more strict. Assignment to this is only possible with exact identical types.
        // The reason why it will cause an error is temporary variable created while implicit type conversion in reference initialization.
        template <typename T2> T2 & operator = (const T2 &i) {
            T2 &guard = value;
            throw guard; // Never reached.
        }

        // Implicit conversion back to T.
        operator T const & () const {
            return value;
        }
    };

    /**
     * 2-dimensions column float vector
     */
    class float2: public float_vector<2> {

    public:

        using float_vector::float_vector;

        [[nodiscard]] float& get_x() { return (*this)[0]; };
        void set_x(float xx) { get_x() = xx; };

        [[nodiscard]] float& get_y() { return (*this)[1]; };
        void set_y(float yy) { get_y() = yy; };

        float2(const observable::Aproxy<float2> &a):float_vector(a.get_data()){};

        property<float> x {
                [this] (float v) { this->set_x(v); },   // Setter ... yes you can do this!
                [this] () -> float& {  return this->get_x(); } // Getter.
        };

        property<float> y {
                [this] (float v) { this->set_y(v); },   // Setter ... yes you can do this!
                [this] () -> float& {  return this->get_y(); } // Getter.
        };

    };

    /**
    * 3-dimensions column float vector
    */
    class float3: public float_vector<3> {

    public:
        using float_vector::float_vector;

        float& get_x() { return (*this)[0]; };
        void set_x(float xx) { get_x() = xx; };

        float& get_y() { return (*this)[1]; };
        void set_y(float xx) { get_y() = xx; };

        float& get_z() { return (*this)[2]; };
        void set_z(float xx) { get_z() = xx; };

        float3(const observable::Aproxy<float3> &a):float_vector(a.get_data()){}

        property<float> x {
                [this] (float v) { this->set_x(v); },   // Setter ... yes you can do this!
                [this] () -> float& {  return this->get_x(); } // Getter.
        };

        property<float> y {
                [this] (float v) { this->set_y(v); },   // Setter ... yes you can do this!
                [this] () -> float& {  return this->get_y(); } // Getter.
        };

        property<float> z {
                [this] (float v) { this->set_z(v); },   // Setter ... yes you can do this!
                [this] () -> float& {  return this->get_z(); } // Getter.
        };

    };

    /**
    * 4-dimensions column float vector
    */
    class float4: public float_vector<4> {

    public:
        using float_vector::float_vector;

        float& get_x() { return (*this)[0]; };
        void set_x(float xx) { get_x() = xx; };

        float& get_y() { return (*this)[1]; };
        void set_y(float xx) { get_y() = xx; };

        float& get_z() { return (*this)[2]; };
        void set_z(float xx) { get_z() = xx; };

        float& get_w() { return (*this)[3]; };
        void set_w(float xx) { get_w() = xx; };

        float4(const observable::Aproxy<float4> &a):float_vector(a.get_data()){}

        property<float> x {
                [this] (float v) { this->set_x(v); },   // Setter ... yes you can do this!
                [this] () -> float& {  return this->get_x(); } // Getter.
        };

        property<float> y {
                [this] (float v) { this->set_y(v); },   // Setter ... yes you can do this!
                [this] () -> float& {  return this->get_y(); } // Getter.
        };

        property<float> z {
                [this] (float v) { this->set_z(v); },   // Setter ... yes you can do this!
                [this] () -> float& {  return this->get_z(); } // Getter.
        };

        property<float> w {
                [this] (float v) { this->set_w(v); },   // Setter ... yes you can do this!
                [this] () -> float& {  return this->get_w(); } // Getter.
        };
    };
}