#version 330 core
/* Copyright (c) 2025 Wdboyes13
SPDX-License-Identifier: MIT */
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = textColor * sampled;
}
