#pragma once
#ifndef R13_PRIVATE_ACCESS
#    error "This should NOT be included by files not part of R13"
#endif

#include <stddef.h>
#include <stdint.h>

#define DECLARE_ASSET(BUILD_ID) \
    extern uint8_t BUILD_ID[];  \
    extern size_t BUILD_ID##_len;

#define DECLARE_SHADER(SHADER_ID) \
    DECLARE_ASSET(SHADER_ID##_frag) \
    DECLARE_ASSET(SHADER_ID##_vert)

DECLARE_SHADER(circle)
DECLARE_SHADER(default)
DECLARE_SHADER(sprite)
DECLARE_SHADER(text)

DECLARE_ASSET(vt323_ttf)

#undef DECLARE_ASSET