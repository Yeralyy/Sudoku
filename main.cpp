#include <iostream>
#include "sudoku.h"


constexpr bool input_grid = 0;

/*
int my_sudoku[9][9] = {
    {0, 3, 0,  0, 0, 0,  0, 4, 0},
    {5, 4, 0,  0, 7, 1,  0, 2, 0},
    {0, 0, 0,  3, 0, 0,  0, 0, 6},

    {0, 0, 8,  0, 0, 9,  0, 0, 0},
    {3, 0, 2,  0, 0, 0,  0, 0, 0},
    {0, 1, 0,  0, 0, 7,  0, 0, 3},

    {0, 0, 0,  0, 0, 0,  0, 8, 9},
    {7, 8, 5,  9, 0, 0,  0, 0, 0},
    {0, 0, 0,  5, 0, 0,  0, 6, 2},
};
*/

int my_sudoku[9][9] = {
    {0, 0, 0,  0, 0, 0,  0, 0, 0},
    {0, 0, 0,  0, 0, 0,  0, 0, 0},
    {0, 0, 0,  0, 0, 0,  0, 0, 0},

    {0, 0, 0,  0, 0, 0,  0, 0, 0},
    {0, 0, 0,  0, 0, 0,  0, 0, 0},
    {0, 0, 0,  0, 0, 0,  0, 0, 0},

    {0, 0, 0,  0, 0, 0,  0, 0, 0},
    {0, 0, 0,  0, 0, 0,  0, 0, 0},
    {0, 0, 0,  0, 0, 0,  0, 0, 0},
};

Sudoku sudoku(my_sudoku);

int main() {

    if constexpr (input_grid) {
        for (int c = 0; c < 9; ++c) {
            for (int r = 0; r < 9; ++r) {
                std::cin >> my_sudoku[c][r];
            }
        }

        std::cout << '\n';
    } 

    sudoku.generate();

    sudoku.render_grid();

    std::cout << '\n';
    sudoku.solve(); 

    sudoku.render_grid();



    return 0;
}