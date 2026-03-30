#define R13_PRIVATE_ACCESS

#include <r13.h>
#include <r13priv/classes.h>

void R13::render_rectangle(Rectangle rect, Color color) {
    return this->rect->render(rect, color);
}

void R13::render_text(std::string text, Vec2 pos, Color color, float scale) {
    return this->text->render(text, pos, color, scale);
}

Vec2 R13::measure_text(const std::string& text, float scale) {
    return this->text->measure(text, scale);
}

void R13::set_font_text(const Font& f) {
    return text->set_font(f);
}

void R13::render_circle(Vec2 center, float radius, Color color) {
    return circle->render(center, radius, color);
}

bool R13::load_file_audio(const std::string& path) {
    return audio->load_file(path);
}

void R13::play_audio() {
    return audio->play();
}

void R13::pause_audio() {
    return audio->pause();
}

void R13::stop_audio() {
    return audio->stop();
}

void R13::loop_audio() {
    return audio->loop();
}

void R13::unloop_audio() {
    return audio->unloop();
}