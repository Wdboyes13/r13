#include <r13.h>

int main() {
    auto rnd = new R13Renderer("../assets", 1280, 720);
    auto dms = rnd->get_dimensions();

    Rectangle sqr = { dms.x / 2, dms.y / 2, 25, 25 };

    auto text_size = rnd->text->measure("test", 1);

    while (!rnd->should_close()) {
        if (rnd->is_key_down(GLFW_KEY_W)) {
            sqr.y++;
        }

        if (rnd->is_key_down(GLFW_KEY_S)) {
            sqr.y--;
        }

        if (rnd->is_key_down(GLFW_KEY_A)) {
            sqr.x--;
        }

        if (rnd->is_key_down(GLFW_KEY_D)) {
            sqr.x++;
        }

        rnd->begin_draw({ 0, 0, 0, 1 });
        rnd->rect->render(sqr, Color{ 1, 1, 1, 1 });
        rnd->text->render(
            "test",
            { (dms.x / 2) - (text_size.x / 2), 14 },
            1,
            { 1, 1, 1, 1 });
        rnd->end_draw();
    }
}