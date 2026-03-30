#pragma once
#ifndef R13_PRIVATE_ACCESS
#    error "This should NOT be included by files not part of R13"
#endif

#include <miniaudio.h>
#include <memory>
#include <string>
#include "structs.h"

class R13;
struct Font;

class Shader {
  private:
    unsigned int compile_shader(const char* source, unsigned int type);

    std::string data_to_string(unsigned char* data, size_t len);

  public:
    unsigned int id;
    Shader(unsigned char* vert_data, size_t vert_data_len, unsigned char* frag_data, size_t frag_data_len);

    ~Shader();

    void use();
    void set_vec2(const char* name, Vec2<float> v);
    void set_vec3(const char* name, Vec3<float> v);
    void set_vec4(const char* name, Vec4<float> v);
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
    void render(std::string text, Vec2<float> pos, Color color, float scale = 1);

    Vec2<float> measure(const std::string& text, float scale = 1);
    void set_font(const Font& f);

    ~TextRND() override;

  private:
    std::unique_ptr<Font> font;
    int font_sz;
};

class CircleRND : public Renderer {
  public:
    void init(R13* _prend) override;
    void render(Vec2<float> center, float radius, Color color);
    ~CircleRND() override;
};

class LineRND : public Renderer {
  public:
    void init(R13* _prend) override;
    void render(Line line, Color color);
    ~LineRND() override;
};

class AudioPlayer {
  public:
    bool load_file(const std::string& path);
    void play();
    void pause();
    void stop();
    void loop();
    void unloop();
    void set_volume(float volume);

  private:
    std::unique_ptr<ma_sound> sound = NULL;
    std::unique_ptr<ma_engine> engine = NULL;
    uint64_t paused_frames = 0;
    bool paused = false;
};