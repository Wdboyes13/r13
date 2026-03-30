#version 330 core
/* Copyright (c) 2025-2026 Wdboyes13
SPDX-License-Identifier: MIT */
layout(location = 0) in vec2 aPos;
uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(aPos, 0.0, 1.0);
}
