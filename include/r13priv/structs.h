#pragma once
#ifndef R13_PRIVATE_ACCESS
#    error "This should NOT be included by files not part of R13"
#endif

#include "api.h"

/**
 * @class
 * @brief A 2-element vector of floats
 */
struct API Vec2 {
    float x; ///< A float containing either an x-axis position, or a width
    float y; ///< A float containing either a y-axis position, or a height
};

struct API Vec3 {
    float x;
    float y;
    float z;
};

struct API Vec4 {
    float x, y, z, w;
};

struct API IVec2 {
    int x, y;
};

/**
 * @class
 * @brief A struct holding information about a colour
 */
struct API Color {
    float r; ///< A float containing red value
    float g; ///< A float containing green value
    float b; ///< A float containing blue value
    float a; ///< A float containing alpha value
    operator Vec4() const {
        return Vec4{ r, g, b, a };
    }
};

struct API Rectangle {
    float x;      ///< The x position of the rectangle
    float y;      ///< The y position of the rectangle
    float height; ///< The height of the rectangle
    float width;  ///< The width of the rectangle
};