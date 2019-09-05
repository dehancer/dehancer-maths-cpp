//
// Created by denn nevera on 2019-09-01.
//

#pragma once

/**
 * only clang and mvc support this syntax
 *
#define PROPERTY(T,_ARG_) __declspec(property(put = property__set_ ##_ARG_, get = property__get_ ##_ARG_)) T _ARG_; typedef T property__tmp_type_ ##_ARG_;
#define READONLY_PROPERTY(T,_ARG_) __declspec(property(get = property__get_ ##_ARG_)) T _ARG_; typedef T property__tmp_type_ ##_ARG_;

#define GET(_ARG_) property__tmp_type_##_ARG_ property__get_##_ARG_()
#define SET(_ARG_) void property__set_##_ARG_(const property__tmp_type_##_ARG_& value)
 */

/*
#define DEFINE_PROPERTY(__PROPS__, __PROPS_TYPE__, __OUTER_CLASS__, __SETTER__, __GETTER__ ) \
struct __property__ ##__PROPS__\
{ \
__OUTER_CLASS__* self; \
__property__ ##__PROPS__() = default;\
__PROPS_TYPE__& operator= (const __PROPS_TYPE__& value) __SETTER__; \
operator const __PROPS_TYPE__() const __GETTER__; \
} __PROPS__ = { .self = this }
*/

/*
#define DEFINE_READONLY_PROPERTY(__PROPS__, __PROPS_TYPE__, __OUTER_CLASS__, __GETTER__ ) \
struct \
{ \
__OUTER_CLASS__* self; \
operator const __PROPS_TYPE__() const __GETTER__; \
} __PROPS__ = { .self = this }
*/

template<typename C, typename T, T (C::*getter)() const, void (C::*setter)(const T&)>
struct Property
{
    C *instance;

    Property(C *instance)
            : instance(instance)
    {
    }

    operator T () const
    {
        return (instance->*getter)();
    }

    Property& operator=(const T& value)
    {
        (instance->*setter)(value);
        return *this;
    }

    template<typename C2, typename T2,
            T2 (C2::*getter2)(), void (C2::*setter2)(const T2&)>
    Property& operator=(const Property<C2, T2, getter2, setter2>& other)
    {
        return *this = (other.instance->*getter2)();
    }

    Property& operator=(const Property& other)
    {
        return *this = (other.instance->*getter)();
    }
};


#define PROPERTY(__PROPS__, __PROPS_TYPE__, __OUTER_CLASS__, __GETTER__, __SETTER__ ) \
void  set_ ##__PROPS__(const __PROPS_TYPE__& value) __SETTER__;\
__PROPS_TYPE__ get_ ##__PROPS__() const __GETTER__;\
Property<__OUTER_CLASS__, __PROPS_TYPE__, &__OUTER_CLASS__::get_ ##__PROPS__, &__OUTER_CLASS__::set_ ##__PROPS__> __PROPS__ = this

template<typename C, typename T, T (C::*getter)() const>
struct ReadOnlyProperty
{
    C *instance;

    ReadOnlyProperty(C *instance)
            : instance(instance)
    {
    }

    operator T () const{
        return (instance->*getter)();
    }

    template<typename C2, typename T2, T2 (C2::*getter2)()>
    ReadOnlyProperty& operator=(const ReadOnlyProperty<C2, T2, getter2>& other)
    {
        return *this = (other.instance->*getter2)();
    }

    ReadOnlyProperty& operator=(const ReadOnlyProperty& other)
    {
        return *this = (other.instance->*getter)();
    }
};

#define READONLY_PROPERTY(__PROPS__, __PROPS_TYPE__, __OUTER_CLASS__, __GETTER__) \
__PROPS_TYPE__ get_ ##__PROPS__() const __GETTER__;\
ReadOnlyProperty<__OUTER_CLASS__, __PROPS_TYPE__, &__OUTER_CLASS__::get_ ##__PROPS__> __PROPS__ = this
