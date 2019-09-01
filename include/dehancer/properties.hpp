//
// Created by denn nevera on 2019-09-01.
//

#pragma once


#define PROPERTY(T,_ARG_) __declspec(property(put = property__set_ ##_ARG_, get = property__get_ ##_ARG_)) T _ARG_; typedef T property__tmp_type_ ##_ARG_;
#define READONLY_PROPERTY(T,_ARG_) __declspec(property(get = property__get_ ##_ARG_)) T _ARG_; typedef T property__tmp_type_ ##_ARG_;

#define GET(_ARG_) property__tmp_type_##_ARG_ property__get_##_ARG_()
#define SET(_ARG_) void property__set_##_ARG_(const property__tmp_type_##_ARG_& value)
#define TYPE(_ARG_) property__tmp_type_ ##_ARG_

