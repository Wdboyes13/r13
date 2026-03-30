#pragma once
#ifndef R13_PRIVATE_ACCESS
#    error "This should NOT be included by files not part of R13"
#endif

#include "api.h"

/**
 * @class
 * @brief A 2-element vector of floats
 */
template<typename T>
struct API Vec2 {
    T x; ///< A float containing either an x-axis position, or a width
    T y; ///< A float containing either a y-axis position, or a height
};

template<typename T>
struct API Vec3 {
    T x;
    T y;
    T z;
};

template<typename T>
struct API Vec4 {
    T x, y, z, w;
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
    operator Vec4<float>() const {
        return Vec4<float>{ r, g, b, a };
    }
};

struct API Rectangle {
    float x;      ///< The x position of the rectangle
    float y;      ///< The y position of the rectangle
    float height; ///< The height of the rectangle
    float width;  ///< The width of the rectangle
};

struct API Line {
    float x1; ///< The x position of the start of the line
    float y1; ///< The y position of the start of the line
    float x2; ///< The x position of the end of the line
    float y2; ///< The y position of the end of the line
};