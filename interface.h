#ifndef GUARD_interface_h
#define GUARD_interface_h

#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "logic.h"

using namespace std;

class Logic;

// Constants
const int DEFAULT_WINDOW_SIZE_X = 640;
const int DEFAULT_WINDOW_SIZE_Y = 480;
const int DEFAULT_CANVAS_SIZE_X = 480;
const int DEFAULT_CANVAS_SIZE_Y = 480;
const int SEPARATOR_LINE_WIDTH = 5;

class Interface {
    /* A class that handles output and input. */

    enum draw_mode_t {pencil, line};

    public:
        Interface(Logic& l): logic(l), window_size_x(DEFAULT_WINDOW_SIZE_X), window_size_y(DEFAULT_WINDOW_SIZE_Y),
        canvas_size_x(DEFAULT_CANVAS_SIZE_X), canvas_size_y(DEFAULT_CANVAS_SIZE_Y), pixel_size_x(0), pixel_size_y(0),
        draw_mode(pencil) {cout << "Interface created" << endl;};

        void start();
        void mainloop();
        void draw_screen();
    private:
        Logic& logic;

        int window_size_x;
        int window_size_y;
        int canvas_size_x;
        int canvas_size_y;
        double pixel_size_x;
        double pixel_size_y;

        SDL_Window* window;
        SDL_Renderer* renderer;

        draw_mode_t draw_mode;
        Pixel selected_pixel;

        void _draw_canvas();
        void _draw_separator_line();
        void _draw_texts();
        void _handle_mouse_click(SDL_Event&);
        void _handle_key_press(SDL_Event&);
};

#endif // GUARD_interface_h

