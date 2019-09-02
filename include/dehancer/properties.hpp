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

#define DEFINE_PROPERTY(__PROPS__, __PROPS_TYPE__, __OUTER_CLASS__, __SETTER__, __GETTER__ ) \
struct \
{ \
__OUTER_CLASS__ *self; \
__PROPS_TYPE__& operator= (const __PROPS_TYPE__& value) __SETTER__; \
operator __PROPS_TYPE__&() const __GETTER__; \
} __PROPS__ = { .self = this }

#define DEFINE_READONLY_PROPERTY(__PROPS__, __PROPS_TYPE__, __OUTER_CLASS__, __GETTER__ ) \
struct \
{ \
__OUTER_CLASS__ *self; \
operator const __PROPS_TYPE__() const __GETTER__; \
} __PROPS__ = { .self = this }

