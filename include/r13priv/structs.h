#pragma once
#ifndef R13_PRIVATE_ACCESS
#    error "This should NOT be included by files not part of R13"
#endif

struct Vec2 {
    float x, y;
};

struct Vec3 {
    float x, y, z;
};

struct Vec4 {
    float x, y, z, w;
};

struct IVec2 {
    int x, y;
};

struct Color {
    float r, g, b, a;
    operator Vec4() const {
        return Vec4{ r, g, b, a };
    }
};

struct Rectangle {
    float x, y, height, width;
};