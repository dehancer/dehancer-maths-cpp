//
// Created by denn nevera on 2019-09-01.
//

#pragma once

#include <armadillo>
#include <cmath>
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

        [[nodiscard]] float get_x() { return (*this)[0]; };
        [[nodiscard]] float& assign_x() { return (*this)[0]; };
        void set_x(float xx) { (*this)[0] = xx; };

        [[nodiscard]] float get_y() { return (*this)[1]; };
        [[nodiscard]] float& assign_y() { return (*this)[1]; };
        void set_y(float yy) { (*this)[1] = yy; };

        float2(const observable::Aproxy<float2> &a):float_vector(a.get_data()){};

        property<float> x {
                [this] (float v) { this->set_x(v); },     // Setter
                [this] () -> float {  return this->get_x(); },    // Getter
                [this] () -> float& {  return this->assign_x(); } // Assigner
        };

        property<float> y {
                [this] (float v) { this->set_y(v); },   // Setter
                [this] () -> float {  return this->get_y(); }, // Getter
                [this] () -> float& {  return this->assign_y(); } // Assigner
        };

    };

    /**
    * 3-dimensions column float vector
    */
    class float3: public float_vector<3> {

    public:
        using float_vector::float_vector;

        float get_x() { return (*this)[0]; };
        void set_x(float xx) { (*this)[0] = xx; };
        [[nodiscard]] float& assign_x() { return (*this)[0]; };

        float get_y() { return (*this)[1]; };
        void set_y(float xx) { (*this)[1] = xx; };
        [[nodiscard]] float& assign_y() { return (*this)[1]; };

        float get_z() { return (*this)[2]; };
        void set_z(float xx) { (*this)[2] = xx; };
        [[nodiscard]] float& assign_z() { return (*this)[2]; };

        float3(const observable::Aproxy<float3> &a):float_vector(a.get_data()){}

        property<float> x {
                [this] (float v) { this->set_x(v); },     // Setter
                [this] () -> float {  return this->get_x(); },    // Getter
                [this] () -> float& {  return this->assign_x(); } // Assigner
        };

        property<float> y {
                [this] (float v) { this->set_y(v); },   // Setter
                [this] () -> float {  return this->get_y(); }, // Getter
                [this] () -> float& {  return this->assign_y(); } // Assigner
        };

        property<float> z {
                [this] (float v) { this->set_z(v); },   // Setter
                [this] () -> float {  return this->get_z(); }, // Getter
                [this] () -> float& {  return this->assign_z(); } // Assigner
        };

    };

    /**
    * 4-dimensions column float vector
    */
    class float4: public float_vector<4> {

    public:
        using float_vector::float_vector;

        float get_x() { return (*this)[0]; };
        void set_x(float xx) { (*this)[0] = xx; };
        [[nodiscard]] float& assign_x() { return (*this)[0]; };

        float get_y() { return (*this)[1]; };
        void set_y(float xx) { (*this)[1] = xx; };
        [[nodiscard]] float& assign_y() { return (*this)[1]; };

        float get_z() { return (*this)[2]; };
        void set_z(float xx) { (*this)[2] = xx; };
        [[nodiscard]] float& assign_z() { return (*this)[2]; };

        float get_w() { return (*this)[3]; };
        void set_w(float xx) { (*this)[3] = xx; };
        [[nodiscard]] float& assign_w() { return (*this)[3]; };

        float4(const observable::Aproxy<float4> &a):float_vector(a.get_data()){}

        property<float> x {
                [this] (float v) { this->set_x(v); },     // Setter
                [this] () -> float {  return this->get_x(); },    // Getter
                [this] () -> float& {  return this->assign_x(); } // Assigner
        };

        property<float> y {
                [this] (float v) { this->set_y(v); },   // Setter
                [this] () -> float {  return this->get_y(); }, // Getter
                [this] () -> float& {  return this->assign_y(); } // Assigner
        };

        property<float> z {
                [this] (float v) { this->set_z(v); },   // Setter
                [this] () -> float {  return this->get_z(); }, // Getter
                [this] () -> float& {  return this->assign_z(); } // Assigner
        };

        property<float> w {
                [this] (float v) { this->set_w(v); },   // Setter
                [this] () -> float {  return this->get_w(); }, // Getter
                [this] () -> float& {  return this->assign_w(); } // Assigner
        };
    };


    inline static float2 make_float2(float x, float y) {
        return {x, y};
    }

    inline static float3 make_float3(float x, float y, float z) {
        return {x, y, z};
    }

    inline static float4 make_float4(float x, float y, float z, float w) {
        return {x, y, z, w};
    }

    /**
     * Kernel compatible function to convert single float to float2, float3, float4
     * @param C
     * @return
     */
    static inline float2 to_float2(float C) { return make_float2(C,C); }
    static inline float3 to_float3(float C) { return make_float3(C,C,C); }
    static inline float4 to_float4(float C) { return make_float4(C,C,C,C); }

    static inline float2 to_float2(int C) { return make_float2(C,C); }
    static inline float3 to_float3(int C) { return make_float3(C,C,C); }
    static inline float4 to_float4(int C) { return make_float4(C,C,C,C); }

    static inline float2 to_float2(uint C) { return make_float2(C,C); }
    static inline float3 to_float3(uint C) { return make_float3(C,C,C); }
    static inline float4 to_float4(uint C) { return make_float4(C,C,C,C); }

    static inline float4 to_float4(const float3& a, float w) {
        return make_float4(a.x, a.y, a.z, w);
    }

    static inline float3 to_float3(const float4& a) {
        return make_float3(a.x, a.y, a.z);
    }

    /**
     * Kernel compatible function of step
     * @param edge
     * @param x
     * @return
     */
    static inline float step(float edge, float x) {
        return x < edge ? 0.0f : 1.0f;
    }

    static inline float2 step(const float2& edge, const float2& x) {
        return make_float2(step(edge.x, x.x),step(edge.y, x.y));
    }

    static inline float3 step(const float3& edge, const float3& x) {
        return make_float3(step(edge.x, x.x),step(edge.y, x.y),step(edge.z, x.z));
    }

    static inline float4 step(const float4& edge, const float4&    x) {
        return make_float4(step(edge.x, x.x),step(edge.y, x.y),step(edge.z, x.z),step(edge.w, x.w));
    }

    static inline float2 step(float edge, const float2& x) {
        return make_float2(step(edge, x.x),step(edge, x.y));
    }

    static inline float3 step(float edge, const float3& x) {
        return make_float3(step(edge, x.x),step(edge, x.y),step(edge, x.z));
    }

    static inline float4 step(float edge, const float4& x) {
        return make_float4(step(edge, x.x),step(edge, x.y),step(edge, x.z),step(edge, x.w));
    }

    /***
     * Kernel compatible function of clamp
     * @param f
     * @param a
     * @param b
     * @return
     */
    static inline float clamp(float f, float a, float b) {
        return fmaxf(a, fminf(f, b));
    }

    static inline float2 clamp(const float2& v, float a, float b) {
        return make_float2(clamp(v.x, a, b), clamp(v.y, a, b));
    }

    static inline float2 clamp(const float2& v, const float2& a, const float2& b) {
        return make_float2(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y));
    }

    static inline float3 clamp(const float3& v, float a, float b) {
        return make_float3(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b));
    }

    static inline float3 clamp(const float3& v, const float3& a, const float3& b) {
        return make_float3(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z));
    }

    static inline float4 clamp(const float4& v, float a, float b) {
        return make_float4(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b), clamp(v.w, a, b));
    }

    static inline float4 clamp(const float4& v, const float4& a, const float4& b) {
        return make_float4(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z), clamp(v.w, a.w, b.w));
    }

    /**
     * Kernel compatible function of fabs
     * @return
     */

    static inline float2 fabs(const float2& v) {
        return make_float2(abs(v.x), abs(v.y));
    }

    static inline float3 fabs(const float3& v) {
        return make_float3(abs(v.x), abs(v.y), abs(v.z));
    }

    static inline float4 fabs(const float4& v) {
        return make_float4(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
    }

    /**
     * Kernel compatible function of fract
     * @param v
     * @return
     */
    static inline float fracf(float v) {
        return v - floorf(v);
    }

    static inline float2 fracf(const float2& v) {
        return make_float2(fracf(v.x), fracf(v.y));
    }

    static inline float3 fracf(const float3& v) {
        return make_float3(fracf(v.x), fracf(v.y), fracf(v.z));
    }

    static inline float4 fracf(const float4& v) {
        return make_float4(fracf(v.x), fracf(v.y), fracf(v.z), fracf(v.w));
    }


    static inline float mix(float x, float y, float a) {
        return x + (y - x) * a;
    }

    /**
     * Kernel compatible function of mix
     * @param x
     * @param y
     * @param a
     * @return
     */
    static inline float4 mix(const float4& x, const float4& y, float a) {
        return {
                mix(x.x, y.y, a),
                mix(x.y, y.y, a),
                mix(x.z, y.z, a),
                mix(x.w, y.w, a)
        };
    }

    static inline float4 mix(const float4& x, const float4& y, const float4& a) {
        return {
                mix(x.x, y.y, a.x),
                mix(x.y, y.y, a.y),
                mix(x.z, y.z, a.z),
                mix(x.w, y.w, a.w)
        };
    }

    static inline float3 mix(const float3& x, const float3& y, float a) {
        return{
                mix(x.x, y.y, a),
                mix(x.y, y.y, a),
                mix(x.z, y.z, a)
        };
    }

    static inline float3 mix(const float3& x, const float3& y, const float3& a) {
        return{
                mix(x.x, y.y, a.x),
                mix(x.y, y.y, a.y),
                mix(x.z, y.z, a.z)
        };
    }

    static inline float2 mix(const float2& x, const float2& y, float a) {
        return {
                mix(x.x, y.y, a),
                mix(x.y, y.y, a)
        };
    }

    static inline float2 mix(const float2& x, const float2& y, const float2& a) {
        return {
                mix(x.x, y.y, a.x),
                mix(x.y, y.y, a.y)
        };
    }

}