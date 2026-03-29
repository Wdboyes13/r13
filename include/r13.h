#pragma once

/* Copyright (c) 2025-2026 Wdboyes13
SPDX-License-Identifier: MIT */

typedef struct GLFWwindow GLFWwindow;
typedef struct ma_engine ma_engine;
typedef struct ma_sound ma_sound;

#include <r13priv/keys.h>
#include <r13priv/structs.h>

#include <filesystem>
#include <map>
#include <memory>
#include <string>

namespace fs = std::filesystem;

class AudioPlayer {
  public:
    bool load_file(const std::string& path);
    void play();
    void pause();
    void stop();

  private:
    std::unique_ptr<ma_sound> sound = NULL;
    std::unique_ptr<ma_engine> engine = NULL;
    uint64_t paused_frames = 0;
    bool paused = false;
};

class SquareRND;
class TextRND;
class CircleRND;

class R13 {
  public:
    R13(const std::string& _data_path, int width, int height);
    ~R13();

    Vec2 get_dimensions();

    static void fb_size_callback(GLFWwindow* window, int width, int height);

    void begin_draw(Color c);
    void end_draw();
    bool is_key_down(int k);
    bool should_close();

    std::unique_ptr<SquareRND> rect;
    std::unique_ptr<TextRND> text;
    std::unique_ptr<CircleRND> circle;

  private:
    void init();

    const fs::path data_path;
    const int width, height;

    GLFWwindow* window;
};

class Shader {
  private:
    unsigned int compile_shader(const char* source, unsigned int type);

    std::string data_to_string(unsigned char* data, unsigned int len);

  public:
    unsigned int id;
    Shader(unsigned char* vert_data, unsigned int vert_data_len, unsigned char* frag_data, unsigned int frag_data_len);

    ~Shader();

    void use();
    void set_vec2(const char* name, Vec2 v);
    void set_vec3(const char* name, Vec3 v);
    void set_vec4(const char* name, Vec4 v);
    void set_float(const char* name, float v);
};

class Renderer {
  public:
    virtual void init(R13* _prend) = 0;
    virtual ~Renderer() = default;

  protected:
    unsigned int vao, vbo;
    std::unique_ptr<Shader> shader;
    R13* prend;
};

class SquareRND : public Renderer {
  public:
    void init(R13* _prend) override;
    void render(Rectangle rect, Color color);
    ~SquareRND() override;
};

class TextRND : public Renderer {
  public:
    void init(R13* _prend) override;
    void render(std::string text, Vec2 pos, float scale, Color color);
    Vec2 measure(const std::string& text, float scale);
    ~TextRND() override;

  private:
    void init_font();

    struct Character {
        unsigned int texture_id; // id of the glyph texture
        IVec2 size;              // size of glyph
        IVec2 bearing;           // offset from baseline to left/top of glyph
        unsigned int advance;    // horiz offset to advance to next glyph
    };
    std::map<char, Character> characters;
};

class CircleRND : public Renderer {
  public:
    void init(R13* _prend) override;
    void render(Vec2 center, float radius, Color color);
    ~CircleRND() override;
};
