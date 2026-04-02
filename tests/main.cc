#include <r13.h>

int main() {
    auto rnd = new R13(1280, 720);
    auto dms = rnd->get_dimensions();

    Rectangle sqr = { (float)(dms.x / 2), (float)(dms.y / 2), 25, 25 };
    Sprite sprite("sprite.jpg");

    auto text_size = rnd->measure_text("test", 1);

    while (!rnd->should_close()) {
        if (rnd->is_key_down(KEY_W)) {
            sqr.y--;
        }

        if (rnd->is_key_down(KEY_S)) {
            sqr.y++;
        }

        if (rnd->is_key_down(KEY_A)) {
            sqr.x--;
        }

        if (rnd->is_key_down(KEY_D)) {
            sqr.x++;
        }

        rnd->begin_draw({ 0, 0, 0, 1 });
        rnd->render_sprite(sprite, { 1, 1 }, { 0.125 / 2, 0.125 / 2 });
        rnd->render_rectangle(sqr, Color{ 1, 1, 1, 1 });
        rnd->render_text("test", { sqr.x, sqr.y }, { 1, 1, 1, 1 });
        rnd->end_draw();
    }
}