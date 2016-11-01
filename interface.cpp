#include <iostream>
#include <string>
#include <vector>
#include "interface.h"
#include "logic.h"
#include "SDL.h"
#include "SDL_ttf.h"

using namespace std;

void Interface::_draw_canvas() {
    cout << "Drawing the canvas" << endl;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set the color to black
    SDL_RenderClear(renderer); // Clear the whole screen, i.e turn it to black

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White

    Canvas& canvas = logic.get_canvas();

    SDL_Rect rect;
    rect.w = pixel_size_x;
    rect.h = pixel_size_y;
    int x_pos = 0;
    int y_pos = 0;
    for (int row = 0; row < canvas.row_count(); ++row) {
        y_pos = 0;
        for (int col = 0; col < canvas.col_count(); ++col) {
            if (canvas.get_pixel(row, col)) {
                rect.x = x_pos;
                rect.y = y_pos;

                SDL_RenderFillRect(renderer, &rect);
            }
            y_pos += pixel_size_y;
        }
        x_pos += pixel_size_x;
    }
}

void Interface::_draw_separator_line() {
    /* Draws the white line between the canvas and the texts. */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    SDL_Rect line;
    line.x = canvas_size_x;
    line.y = 0;
    line.w = SEPARATOR_LINE_WIDTH;
    line.h = canvas_size_y;
    SDL_RenderFillRect(renderer, &line);
}

void Interface::draw_screen() {
    /* Use this function to update the screen after modifying the canvas. */
    _draw_canvas();
    _draw_separator_line();
    // _draw_texts();
    SDL_RenderPresent(renderer); // Update the screen
}

void Interface::_draw_texts() {
    // To be implemented
}

void Interface::_handle_mouse_click(SDL_Event& event) {
    Canvas& canvas = logic.get_canvas();

    // Left button sets pixels on, right button off
    bool pixel_state = (event.button.button == SDL_BUTTON_LEFT);
    Pixel clicked_pixel(event.button.x/pixel_size_x, event.button.y/pixel_size_y);
    cout << "Clicked " << clicked_pixel.as_string() << endl;

    if (draw_mode == pencil) {
        canvas.set_pixel(clicked_pixel, pixel_state);
    } else if (draw_mode == line) {
        if (selected_pixel.null()) {
            selected_pixel = clicked_pixel;
           // cout << selected_pixel.row << ", " << selected_pixel.col << endl;
        } else {
            canvas.draw_line(selected_pixel, clicked_pixel, pixel_state);
            selected_pixel.set_null();
        }
    }
}

void Interface::_handle_key_press(SDL_Event& event) {
    if (draw_mode == pencil) {
        draw_mode = line;
    } else {
        draw_mode = pencil;
    }
    cout << "Draw mode is now " << draw_mode << endl;
}

void Interface::mainloop() {
    SDL_Event event;

    while (SDL_WaitEvent(&event)) {
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            cout << "Mouse button pressed" << endl;
            _handle_mouse_click(event);
            draw_screen();
            break;
        case SDL_KEYDOWN:
            cout << "Key pressed" << endl;
            _handle_key_press(event);
            break;
        case SDL_QUIT:
            return;
        }
    }
}

void Interface::start() {
    /* Use this to start the program. */

    cout << "Starting the interface" << endl;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Drawing program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_size_x, window_size_y, 0);
    if (window == NULL) {
        cout << "Error in initializing the program window." << endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        cout << "Error in initializing the renderer." << endl;
        return;
    }

    logic.create_new_canvas();

    // Update the variables
    pixel_size_x = canvas_size_x/logic.get_canvas().row_count();
    pixel_size_y = canvas_size_y/logic.get_canvas().col_count();

    draw_screen();

    mainloop();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

