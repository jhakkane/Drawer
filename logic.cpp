#include <vector>
#include <algorithm>
#include <exception>
#include <cmath>
#include "logic.h"
using namespace std;

// ----- Useful functions ----

int sign(int x) {
    return (x >= 0 ? 1 : -1);
}

bool is_space(char x) {
    return (x == ' ');
}
bool not_space(char x) {
    return !is_space(x);
}

vector<string> split(const string& str) {
    /* A function that splits the given string into a vector of strings using whitespace as delimiter. */
    typedef string::const_iterator iter;
    vector<string> ret;

    iter i = str.begin();
    while (i != str.end()) {
        i = find_if(i, str.end(), not_space);
        iter j = find_if(i, str.end(), is_space);

        if (i != str.end())
            ret.push_back(string(i, j));
        i = j;
    }
    return ret;
}

vector<Pixel> get_line(Pixel first, Pixel last) {
    /* Calculates the Pixels that form a line between the given ending and starting points.
    The line is returned as a vector of Pixels. */
    vector<Pixel> point_vec;

    int abs_change[2] = {abs(first.row-last.row), abs(first.col-last.col)};
    int length = max(abs_change[0], abs_change[1]);

    int signs[2] = {sign(last.row-first.row), sign(last.col-first.col)};
    int cum[2] = {0, 0};

    Pixel point = {first.row, first.col};
    for (int i=0; i<length; ++i) {
        point_vec.push_back(point);

        for (int o=0; o < 2; ++o) {
            cum[o] += 2*abs_change[o];
            if (cum[o] >= length) {
                cum[o] -= 2*length;
                point[o] += signs[o];
            }
        }
    }
    point_vec.push_back({last.row, last.col}); // add the last point, too
    return point_vec;
}

// --------- CANVAS ---------

bool Canvas::get_pixel(int row, int col) {
    return arr[row*cols + col];
}

void Canvas::set_pixel(int row, int col, bool pixel_state) {
    if (row >= 0 && row < rows && col >= 0 && col < cols)
        arr[row*cols + col] = pixel_state;
}

void Canvas::set_pixel(Pixel pixel, bool pixel_state) {
    if (pixel.row >= 0 && pixel.row < rows && pixel.col >= 0 && pixel.col < cols)
        arr[pixel.row*cols + pixel.col] = pixel_state;
}

void Canvas::draw_line(int first_row, int first_col, int last_row, int last_col, bool pixel_state) {
    Pixel first(first_row, first_col);
    Pixel last(last_row, last_col);
    draw_line(first, last, pixel_state);
}
void Canvas::draw_line(Pixel first, Pixel last, bool pixel_state) {
    vector<Pixel> line = get_line(first, last);
    for (auto it = line.begin(); it != line.end(); ++it) {
        set_pixel(*it, pixel_state);
    }
}


void Canvas::create(int row_num, int col_num) {
    /* Initializes the canvas so that it can be used for drawing. */
    cout << "Creating a canvas" << endl;
    rows = row_num;
    cols = col_num;
    arr = new bool[rows*cols];
    for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
        arr[row*cols + col] = 0;
    }}
}

void Logic::create_new_canvas() {
    canvas.create();
}

