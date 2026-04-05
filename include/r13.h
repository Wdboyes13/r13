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
#include <random>
#include <string>
#include <vector>

extern "C" typedef struct GLFWwindow GLFWwindow;

class RectRND;
class TextRND;
class CircleRND;
class LineRND;
class SpriteRND;
class PolyRND;
class AudioPlayer;

#ifdef _MSC_VER
#    pragma warning(push)
#    pragma warning(disable : 4251)
#endif
/**
 * @class Font
 * @brief A struct containing data for a font
 * This font struct is to use and load fonts
 * the default font is the VT323 font and is usually loaded automatically
 * when you instantiate the R13 class
 * the default font is selected when the "path" argument of the constructor is "__DEFAULT__"
 *
 * Example usage:
 * @code
 * Font my_font("path/to/my_font.ttf")
 * r13->set_font(my_font)
 * @endcode
 */
struct API Font {
    /**
     * @brief Loads in a Font, constructing an instance of the Font class
     * @param path The path to the font to load, by default "__DEFAULT__" which loads the builtin VT323 font
     * @param size The size to load the font as, by default it is 48
     * @throws std::runtime_error if the file can't be opened
     * @throws std::runtime_error if the font can't be used/initialized
     */
    Font(const std::string& path = "__DEFAULT__", int size = 48);
    ~Font();

    /**
     * @brief Returns the size of "text" when using this Font at "scale"
     * @param text The text to get the size of
     * @param scale The scale it will be rendered at
     * @return The size of "text" when rendered at "scale" as a Vec2
     */
    Vec2<float> measure(const std::string& text, float scale = 1);

  private:
    friend TextRND;
    struct Character {
        unsigned int texture_id; // id of the glyph texture
        Vec2<int> size;          // size of glyph
        Vec2<int> bearing;       // offset from baseline to left/top of glyph
        unsigned int advance;    // horiz offset to advance to next glyph
    };
    std::map<char, Character> characters;
};

struct API Sprite {
    Sprite(const std::string& path);
    ~Sprite();

  private:
    friend SpriteRND;
    unsigned char* data;
    unsigned int texture_id;
    int w, h, c;
};

/**
 * @class R13
 * @brief An instance of the R13 engine
 * This class holds and exports functions/instances of fonts, renderers, and audio objects
 * it also manages the OpenGL, GLFW, and GLAD contexts, offering various mechanisms to control them
 *
 * Example usage:
 * @code
 * auto rnd = new R13(1280, 720);
 * auto dms = rnd->get_dimensions();
 *
 * Rectangle sqr = { dms.x / 2, dms.y / 2, 25, 25 };
 *
 * auto text_size = rnd->measure_text("test", 1);
 *
 * while (!rnd->should_close()) {
 *     if (rnd->is_key_down(KEY_W)) {
 *         sqr.y++;
 *     }
 *
 *     if (rnd->is_key_down(KEY_S)) {
 *         sqr.y--;
 *     }
 *
 *     if (rnd->is_key_down(KEY_A)) {
 *        sqr.x--;
 *     }
 *
 *     if (rnd->is_key_down(KEY_D)) {
 *        sqr.x++;
 *     }
 *
 *     rnd->begin_draw({ 0, 0, 0, 1 });
 *     rnd->render_rectangle(sqr, Color{ 1, 1, 1, 1 });
 *     rnd->render_text(
 *         "test",
 *         { (dms.x / 2) - (text_size.x / 2), 14 },
 *        { 1, 1, 1, 1 }
 *     );
 *     rnd->end_draw();
 * }
 * @endcode
 */
class API R13 {
  public:
    /**
     * @brief Constructs and initializes an instance of the R13 engine
     * @param width The width of the window to create
     * @param height The height of the window to create
     * @param font_size The size to load the default VT323 font at, by default 48
     * @throws std::runtime_error if window creation failed
     * @throws std::runtime_error if loading OpenGL failed
     */
    R13(int width, int height, int font_size = 48);
    ~R13();

    /**
     * @brief Set the window icon object
     *
     * @param path path to the file
     * @param height height of the image
     * @param width width of the image
     * @throws std::runtime_error if the file can't be opened
     */
    void set_window_icon(const std::string& path, int height, int width);
    /**
     * @brief Set the window title object
     *
     * @param title title to set to
     */
    void set_window_title(const std::string& title);
    /**
     * @brief Set the window pos object
     *
     * @param size position to move the window to
     */
    void set_window_pos(Vec2<int> size);
    /**
     * @brief Set the window opacity object
     *
     * @param opacity opacity to set the window to, from 0 to 1
     */
    void set_window_opacity(float opacity);
    /**
     * @brief Set the window size object
     *
     * @param size size to set the window to
     */
    void set_window_size(Vec2<int> size);
    /**
     * @brief Set the window to fullscreen
     */
    void set_window_fullscreen();

    /**
     * @brief Gets the dimensions of the current window
     * @returns a Vec2 containing the current window size
     */
    Vec2<int> get_dimensions();

    /**
     * @brief Starts drawing to the window
     * @param c The color to clear the window with
     */
    void begin_draw(Color c);

    /**
     * @brief Ends drawing to the window, showing the frame to the user
     */
    void end_draw();

    /**
     * @brief Reports if a key is down
     * @param k The key to check
     * @return a bool reporting if the key "k" is currently down
     */
    bool is_key_down(int k);

    /**
     * @brief Reports if a mouse button is down
     * @param b The mouse button to check
     * @return a bool reporting if the mouse button "b" is currently down
     */
    bool is_mouse_button_down(int b);

    Vec2<double> get_mouse_pos(); ///< Gets the current position of the mouse cursor

    using KeyCallback = void (*)(GLFWwindow* window, int key, int scancode, int action, int mods);
    void set_key_callback(KeyCallback callback); ///< Sets the key callback for the window, see GLFW documentation for more details on how key callbacks work

    /**
     * @brief Tells if we should close the window and cleanup the game
     * Example usage:
     * @code
     * while (!r13->window_should_close()) {
     *     // do game stuff...
     * }
     * @endcode
     * @return A bool reporting if the window should be closed
     */
    bool should_close();

    uint64_t get_delta_time();                            ///< Gets the time in milliseconds since the last frame, useful for framerate independent movement
    int get_fps();                                        ///< Gets the current framerate, useful for debugging and performance monitoring
    int64_t get_random(int64_t min = 0, int64_t max = 0); ///< Gets a random number between min and max, if max is 0, it will be set to the maximum value of int64_t, and if min is 0, it will be set to the minimum value of int64_t

    /**
     * @brief Renders a rectangle to the current frame
     * @param rect The Rectangle to render
     * @param color The colour of the rectangle to render
     */
    void render_rectangle(Rectangle rect, Color color);

    /**
     * @brief Renders text using the current Font to the current frame
     * @param text The text to render
     * @param pos The position to render the text at
     * @param color The colour the text should be
     * @param scale The scale to render the text at, by default 1
     */
    void render_text(std::string text, Vec2<float> pos, Color color, float scale = 1);

    /**
     * @see Font::measure
     */
    Vec2<float> measure_text(const std::string& text, float scale = 1);

    /**
     * @brief Sets the font to use
     * @param f The instance of the Font struct to use
     * @note This function copies the entire font data to a separate instance
     */
    void set_font_text(const Font& f);

    /**
     * @brief Renders a circle to the current frame
     * @param center The position of the centre of the circle
     * @param radius The radius of the circle to render
     * @param color The colour to render the circle as
     */
    void render_circle(Vec2<float> center, float radius, Color color);

    /**
     * @brief Renders a line to the current frame
     * @param line The line to render
     * @param color The colour to render the line as
     */
    void render_line(Line line, Color color);

    /**
     * @brief Renders a sprite to the current frame
     *
     * @param pos position of the sprite
     * @param scale scale of the sprite
     * @param path path to the sprite image file
     */
    void render_sprite(Sprite& sprite, Vec2<float> pos, Vec2<float> scale);

    /**
     * @breif Renders a polygon to the current from
     * @param n_vertices number of vertices for the polygon
     * @param radius radius of the polygon
     * @param pos position of the polygon
     * @param color colour of the polygon
     */
    void render_polygon(int n_vertices, float radius, Vec2<float> pos, Color color);

    /**
     * @brief Loads an audio file
     * @param path The path to the audio file to load
     * @return A bool indicating whether the loading failed, or succeeded
     */
    bool load_file_audio(const std::string& path);

    void play_audio();   ///< Starts playing or unpauses the current audio file
    void pause_audio();  ///< Pauses the current audio file
    void stop_audio();   ///< Stops the current audio file
    void loop_audio();   ///< Sets the current audio file to loop
    void unloop_audio(); ///< Sets the current audio file to not loop
    void set_volume_audio(float volume); ///< Sets the volume of the current audio file, from 0 to 1

  private:
    void init();

    const int font_sz;
    const int width, height;
    std::vector<uint64_t> frame_times;

    std::unique_ptr<RectRND> rect;
    std::unique_ptr<TextRND> text;
    std::unique_ptr<CircleRND> circle;
    std::unique_ptr<LineRND> line;
    std::unique_ptr<SpriteRND> sprite;
    std::unique_ptr<AudioPlayer> audio;
    std::unique_ptr<PolyRND> polygon;

    std::mt19937_64 rng;

    GLFWwindow* window;
};
#ifdef _MSC_VER
#    pragma warning(pop)
#endif