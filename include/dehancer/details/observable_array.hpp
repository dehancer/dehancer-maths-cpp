//
// Created by denn nevera on 2019-09-04.
//

#pragma once

#include <vector>
#include "dehancer/properties.hpp"

namespace dehancer {
    namespace observable {

        struct auto_lf {
            std::function< void() > _lambda;
            template< typename RET, typename ... ARGS >
            inline auto_lf( RET F( ARGS... ),  ARGS... args ) : _lambda{ [ F, args... ] { F( args... ); } } {}
            inline auto_lf( std::function< void() >&& func ) : _lambda{ std::move( func ) } {}
            inline ~auto_lf() { _lambda(); }
        };

        template <typename V>
        using Handler  = std::function<void(const V&)>;

        template <typename T>
        struct Aproxy {

            Aproxy(T& v,
                   std::vector<T>& a,
                   const Handler<std::vector<T>>& on_update = nullptr):
                    data_(&v),
                    root_(&a),
                    on_update_(on_update)
            {}

            Aproxy& operator = (const T& data) {
                *data_ = data;
                if (on_update_) {
                    on_update_(*root_);
                }
                return *this;
            }

            Aproxy& operator = (const Aproxy& a) {
                *data_ = *a.data_;
                root_ = a.root_;
                if (on_update_) {
                    on_update_(*root_);
                }
                return *this;
            }

            PROPERTY(point,
                     T,
                     Aproxy,
                     { return get_data();         }, // getter
                     {        get_data() = value; }  // setter
            );

            T& get_data() { return *data_;};
            const T& get_data() const { return *data_;};

        private:
            T* data_;
            std::vector<T>* root_;
            Handler<std::vector<T>> on_update_;
        };

        template <typename T>
        struct Array {

            Array() = default;

            explicit Array(const std::vector<T>& value){
                //std::copy(value.begin(), value.end(), std::back_inserter(value_));
                for (auto v: value) value_.push_back(v);
            }

            Array(const Array<T>& value){
                for (auto v: value.value_) value_.push_back(v);
                //std::copy(value.value_.begin(), value.value_.end(), std::back_inserter(value_));
            }

            Handler<std::vector<T>> on_update = nullptr;

            size_t  size() const { return value_.size(); }

            std::vector<T>& operator= (const std::vector<T>& value) {
                value_ = value;
                if (on_update) {
                    on_update(value_);
                }
                return value_;
            }

            Array<T>& operator= (const Array<T>& value) {
                value_ = value.value_;
                if (on_update) {
                    on_update(value_);
                }
                return *this;
            }

            operator std::vector<T>() const {
                return value_;
            }

            const T  operator[] (int index) const {
                if (value_.empty()) return {0,0};
                if (index<0) return value_[0];
                if (index>=value_.size()) return value_[value_.size()-1];
                return value_[index];
            }

            Aproxy<T> operator[](int i) {

                if (i>=value_.size()) {
                    value_.resize(i+1);
                }

                return Aproxy<T>(
                        value_[i],
                        value_,
                        [this](const std::vector<T>& vector){
                            if (on_update)
                                on_update(vector);
                        });
            }

            friend std::ostream& operator<<(std::ostream& os, const Array& array){
                for (auto &v: array.value_) {
                    os << v.t();
                }
                return os;
            }

        private:
            std::vector<T> value_;
        };
    }
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector){
    for (auto &v: vector) {
        os << v.t();
    }
    return os;
}
