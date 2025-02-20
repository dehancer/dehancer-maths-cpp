//
// Created by denn nevera on 2019-09-01.
//

#pragma once

#include <functional>

template<typename Outer, typename T, T& (Outer::*getter)(), void (Outer::*setter)(const T&)>
struct Property
{
    Outer *instance;

    Property(Outer *instance): instance(instance){}
    Property(): instance(nullptr){}

    operator T () const { return (instance->*getter)(); }
    operator T& ()      { return (instance->*getter)(); }

    Property& operator = (const Property& other) { *this = (other.instance->*getter)(); return *this; }

    Property& operator = (const T& value) { (instance->*setter)(value); return *this; }

    Property& operator = (Outer *value) { instance = value; return *this; }

    template<typename OuterIn, typename TIn, TIn (OuterIn::*getter2)(), void (OuterIn::*setter2)(const TIn&)>
    Property& operator = (const Property<OuterIn, TIn, getter2, setter2>& other)
    {
        *this = (other.instance->*getter2)(); return *this ;
    }

};

#define PROPERTY(__PROPS__, __PROPS_TYPE__, __OUTER_CLASS__, __GETTER__, __SETTER__ ) \
  void set_ ##__PROPS__(const __PROPS_TYPE__& value) {__PROPS__.instance = this; __SETTER__; };\
  __PROPS_TYPE__&  get_ ##__PROPS__() __GETTER__;\
  Property<__OUTER_CLASS__, __PROPS_TYPE__,\
  &__OUTER_CLASS__::get_ ##__PROPS__, &__OUTER_CLASS__::set_ ##__PROPS__> __PROPS__ = this


template<typename Outer, typename T, T (Outer::*getter)() const>
struct ReadOnlyProperty
{
    Outer *instance;

    ReadOnlyProperty(Outer *instance)
            : instance(instance)
    {
    }

    operator T () const{
        return (instance->*getter)();
    }

    template<typename OuterIn, typename TIn, TIn (OuterIn::*getter2)()>
    ReadOnlyProperty& operator=(const ReadOnlyProperty<OuterIn, TIn, getter2>& other)
    {
        *this = (other.instance->*getter2)(); return *this;
    }

    ReadOnlyProperty& operator=(const ReadOnlyProperty& other)
    {
        *this = (other.instance->*getter)(); return *this;
    }
};

#define READONLY_PROPERTY(__PROPS__, __PROPS_TYPE__, __OUTER_CLASS__, __GETTER__) \
__PROPS_TYPE__ get_ ##__PROPS__() const __GETTER__;\
ReadOnlyProperty<__OUTER_CLASS__, __PROPS_TYPE__, &__OUTER_CLASS__::get_ ##__PROPS__> __PROPS__ = this

namespace dehancer::math {

    template<typename T>
    class value_property {
    public:

        [[maybe_unused]] value_property()= default;

        explicit value_property(const T& value) { value_=value; };

        operator T() const {return (T)(value_);}

        const T& operator()() const { return value_(); }

        value_property<T> &operator=(const T &value) {
            value_ = value;
            return *this;
        }

    private:
        T value_{};
    };

    template<typename T>
    class property {
    public:

        [[maybe_unused]] property(
                std::function<void   (const T&)> setter,
                std::function<const T&()> getter
        ) :
                setter_(setter),
                getter_(getter)
        {};

        explicit property(const T& value) { setter_(value); };

        operator T() const {return getter_();}

        const T& operator()() const { return getter_(); }

        property<T> &operator=(const T &value) {
            setter_(value);
            return *this;
        }

    private:
        std::function<void   (const T&)> setter_;
        std::function<const T&()> getter_;
    };

    template<typename T>
    class copied_property {
    public:

        [[maybe_unused]] copied_property(
                std::function<void(T)> setter,
                std::function<T()> getter
        ) :
                setter_(setter),
                getter_(getter)
        {};

        explicit copied_property(const T& value) { setter_(value); };

        explicit operator const T&() const {return getter_();}

        const T operator()() const { return getter_(); }

        copied_property<T> &operator=(const T &value) {
            setter_(value);
            return *this;
        }

    private:
        std::function<void(T)> setter_;
        std::function<T()> getter_;
    };

    template<typename T>
    class assigned_property {
    public:

        [[maybe_unused]] assigned_property(
                std::function<void(const T&)> setter,
                std::function<T()> getter,
                std::function<T&()> assigner
                ) :
                setter_(setter),
                getter_(getter),
                assigner_(assigner)
                {};

        explicit assigned_property(const T& value) { setter_(value); };

        operator T() const {return getter_();}

        const T& operator()() const { return assigner_(); }

        T& operator()() { return assigner_(); }

        assigned_property<T> &operator=(const T &value) {
            setter_(value);
            return *this;
        }

    private:
        std::function<void(T)> setter_;
        std::function<T()> getter_;
        std::function<T&()> assigner_;
    };

}