#ifndef GUARD_logic_h
#define GUARD_logic_h

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <stdexcept>
using namespace std;

struct Pixel {
    /* A structure representing a pixel on the canvas. */

    // Default constructor creates a pixel that is not actually anywhere on the canvas, a null pixel
    Pixel(): row(-1), col(-1) {};
    Pixel(int x, int y): row(x), col(y) {};

    void set_null() {row = -1; col = -1;};
    bool null() {return (row == -1 || col == -1);};

    int& operator[](size_t i) {
        switch(i) {
        case 0:
            return row;
            break;
        case 1:
            return col;
            break;
        }
        throw out_of_range("Index out of range!");
    }

    string as_string() {return to_string(row)+" "+to_string(col);};

    int row;
    int col;
};

// Constants
const int DEFAULT_ROW_NUM = 30;
const int DEFAULT_COL_NUM = 30;

// Function declarations
int sign(int);
vector<string> split(const string& str);
vector<Pixel> get_line(int, int, int, int);

class Canvas {
    /* This class describes the image the user is drawing. */

    friend class Logic;
    public:
        Canvas(): rows(0), cols(0) {};
        ~Canvas() {delete[] arr;};

        int row_count() {return rows;};
        int col_count() {return cols;};
        bool get_pixel(int row, int col);
        void set_pixel(int row, int col, bool pixel_state=true);
        void set_pixel(Pixel, bool);
        void draw_line(int, int, int, int, bool=true);
        void draw_line(Pixel, Pixel, bool=true);

        void create(int row_num = DEFAULT_ROW_NUM, int col_num = DEFAULT_COL_NUM);

    private:
        int rows;
        int cols;
        bool* arr;

};

class Logic {
    /* A general class used to manage the internal state of the program. */
    public:
        Canvas& get_canvas() {return canvas;};

        void create_new_canvas();

    private:
        Canvas canvas;
};

#endif // GUARD_logic_h
