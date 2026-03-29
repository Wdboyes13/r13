#pragma once
#ifndef R13_PRIVATE_ACCESS
#    error "This should NOT be included by files not part of R13"
#endif

#include <string>
#include "structs.h"

class R13;
class Font;

typedef struct ma_engine ma_engine;
typedef struct ma_sound ma_sound;

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

class RectRND : public Renderer {
  public:
    void init(R13* _prend) override;
    void render(Rectangle rect, Color color);
    ~RectRND() override;
};

class TextRND : public Renderer {
  public:
    TextRND(int font_sz);
    void init(R13* _prend) override;
    void render(std::string text, Vec2 pos, Color color, float scale = 1);

    Vec2 measure(const std::string& text, float scale = 1);
    void set_font(const Font& f);

    ~TextRND() override;

  private:
    std::unique_ptr<Font> font;
    int font_sz;
};

class CircleRND : public Renderer {
  public:
    void init(R13* _prend) override;
    void render(Vec2 center, float radius, Color color);
    ~CircleRND() override;
};

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