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
                [this] (float v) { this->set_x(v); },   // Setter
                [this] () -> float& {  return this->get_x(); } // Getter
        };

        property<float> y {
                [this] (float v) { this->set_y(v); },   // Setter
                [this] () -> float& {  return this->get_y(); } // Getter
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
                [this] (float v) { this->set_x(v); },   // Setter
                [this] () -> float& {  return this->get_x(); } // Getter
        };

        property<float> y {
                [this] (float v) { this->set_y(v); },   // Setter
                [this] () -> float& {  return this->get_y(); } // Getter
        };

        property<float> z {
                [this] (float v) { this->set_z(v); },   // Setter
                [this] () -> float& {  return this->get_z(); } // Getter
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
                [this] (float v) { this->set_x(v); },   // Setter
                [this] () -> float& {  return this->get_x(); } // Getter
        };

        property<float> y {
                [this] (float v) { this->set_y(v); },   // Setter
                [this] () -> float& {  return this->get_y(); } // Getter
        };

        property<float> z {
                [this] (float v) { this->set_z(v); },   // Setter
                [this] () -> float& {  return this->get_z(); } // Getter
        };

        property<float> w {
                [this] (float v) { this->set_w(v); },   // Setter
                [this] () -> float& {  return this->get_w(); } // Getter
        };
    };


    inline static float2 __attribute__((overloadable)) make_float2(float x, float y) {
        return {x, y};
    }

    inline static  float3 __attribute__((overloadable)) make_float3(float x, float y, float z) {
        return {x, y, z};
    }

    inline static  float4 __attribute__((overloadable)) make_float4(float x, float y, float z, float w) {
        return {x, y, z, w};
    }

    static inline float2 __attribute__((overloadable)) to_float2(float C) { return make_float2(C,C); }
    static inline float3 __attribute__((overloadable)) to_float3(float C) { return make_float3(C,C,C); }
    static inline float4 __attribute__((overloadable)) to_float4(float C) { return make_float4(C,C,C,C); }

    static inline float2 __attribute__((overloadable)) to_float2(int C) { return make_float2(C,C); }
    static inline float3 __attribute__((overloadable)) to_float3(int C) { return make_float3(C,C,C); }
    static inline float4 __attribute__((overloadable)) to_float4(int C) { return make_float4(C,C,C,C); }

    static inline float2 __attribute__((overloadable)) to_float2(uint C) { return make_float2(C,C); }
    static inline float3 __attribute__((overloadable)) to_float3(uint C) { return make_float3(C,C,C); }
    static inline float4 __attribute__((overloadable)) to_float4(uint C) { return make_float4(C,C,C,C); }

    static inline float4 __attribute__((overloadable)) to_float4(const float3& a, float w) {
        return make_float4(a.x, a.y, a.z, w);
    }

    static inline float3 __attribute__((overloadable)) to_float3(const float4& a) {
        return make_float3(a.x, a.y, a.z);
    }

}