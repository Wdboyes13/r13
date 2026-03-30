#pragma once

/* Copyright (c) 2025-2026 Wdboyes13
SPDX-License-Identifier: MIT */

#ifndef R13_PRIVATE_ACCESS
#    define R13_PRIVATE_ACCESS
#    define R13_MAIN_HEADER_PRV
#endif
#include <r13priv/api.h>
#include <r13priv/keys.h>
#include <r13priv/structs.h>
#ifdef R13_MAIN_HEADER_PRV
#    undef R13_PRIVATE_ACCESS
#endif

#include <map>
#include <memory>
#include <string>

extern "C" typedef struct GLFWwindow GLFWwindow;

class RectRND;
class TextRND;
class CircleRND;
class AudioPlayer;

#ifdef _MSC_VER
#    pragma warning(push)
#    pragma warning(disable : 4251)
#endif
struct API Font {
    Font(const std::string& path = "__DEFAULT__", int size = 48);
    ~Font();
    Vec2 measure(const std::string& text, float scale = 1);

  private:
    friend TextRND;
    struct Character {
        unsigned int texture_id; // id of the glyph texture
        IVec2 size;              // size of glyph
        IVec2 bearing;           // offset from baseline to left/top of glyph
        unsigned int advance;    // horiz offset to advance to next glyph
    };
    std::map<char, Character> characters;
};

class API R13 {
  public:
    R13(int width, int height, int font_size = 48);
    ~R13();

    Vec2 get_dimensions();

    static void fb_size_callback(GLFWwindow* window, int width, int height);

    void begin_draw(Color c);
    void end_draw();
    bool is_key_down(int k);
    bool should_close();

    // "re-exported" functions from renderers
    void render_rectangle(Rectangle rect, Color color);

    void render_text(std::string text, Vec2 pos, Color color, float scale = 1);
    Vec2 measure_text(const std::string& text, float scale = 1);
    void set_font_text(const Font& f);

    void render_circle(Vec2 center, float radius, Color color);

    bool load_file_audio(const std::string& path);
    void play_audio();
    void pause_audio();
    void stop_audio();

  private:
    void init();

    const int font_sz;
    const int width, height;

    std::unique_ptr<RectRND> rect;
    std::unique_ptr<TextRND> text;
    std::unique_ptr<CircleRND> circle;
    std::unique_ptr<AudioPlayer> audio;

    GLFWwindow* window;
};
#ifdef _MSC_VER
#    pragma warning(pop)
#endif