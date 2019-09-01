//
// Created by denn nevera on 2019-09-01.
//

#pragma once


#define PROPERTY(T,_ARG_) __declspec(property(put = property__set_ ##_ARG_, get = property__get_ ##_ARG_)) T _ARG_; typedef T property__tmp_type_ ##_ARG_;

#define GET(n) property__tmp_type_##n property__get_##n()
#define SET(n) void property__set_##n(const property__tmp_type_##n& value)

