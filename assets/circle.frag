#version 330 core
/* Copyright (c) 2025 Wdboyes13
SPDX-License-Identifier: MIT */
in vec2 TexCoord;
out vec4 FragColor;

uniform vec4 color;

void main() {
    float dist = length(TexCoord);
    if (dist > 1.0) {
        discard; // Outside circle
    }
    FragColor = color;
}
