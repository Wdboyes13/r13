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
     * @brief Gets the dimensions of the current window
     * @returns a Vec2 containing the current window size
     */
    Vec2 get_dimensions();

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
    void render_text(std::string text, Vec2 pos, Color color, float scale = 1);

    /**
     * @see Font::measure
     */
    Vec2 measure_text(const std::string& text, float scale = 1);

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
    void render_circle(Vec2 center, float radius, Color color);

    /**
     * @brief Loads an audio file
     * @param path The path to the audio file to load
     * @return A bool indicating whether the loading failed, or succeeded
     */
    bool load_file_audio(const std::string& path);

    /**
     * @brief Starts playing or unpauses the current audio file
     */
    void play_audio();
    /**
     * @brief Pauses the current audio file
     */
    void pause_audio();
    /**
     * @brief Stops the current audio file
     */
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