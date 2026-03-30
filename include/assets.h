#pragma once
#ifndef R13_PRIVATE_ACCESS
#    error "This should NOT be included by files not part of R13"
#endif

#include <stddef.h>
#include <stdint.h>

#define DECLARE_ASSET(BUILD_ID) \
    extern uint8_t BUILD_ID[];  \
    extern size_t BUILD_ID##_len;

DECLARE_ASSET(circle_frag)
DECLARE_ASSET(circle_vert)

DECLARE_ASSET(rect_frag)
DECLARE_ASSET(rect_vert)

DECLARE_ASSET(text_frag)
DECLARE_ASSET(text_vert)

DECLARE_ASSET(vt323_ttf)

#undef DECLARE_ASSET