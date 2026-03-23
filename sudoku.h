#pragma once
#include <iostream>
#include <cstring>
#include <random>
#include <chrono>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 engine(seed);

std::uniform_int_distribution<int> dist(1, 9);
std::uniform_int_distribution<int> fifty_fifty(0, 1);

class Sudoku {
    public:
        Sudoku(int (*sudoku_grid)[9]);
        bool solve(int c = 0, int r = 0, bool copy = 1);
        void generate();
        void render_grid();

    private:
        bool isValid(int x, int y, int cell); 
        bool generate_grid(int c = 0, int r = 0);
        int (*grid)[9];
        int original_grid[9][9] {}; // test grid
        int buffer[9][9]; // another buffer
};

Sudoku::Sudoku(int (*sudoku_grid)[9]) : grid {sudoku_grid} {
    std::memcpy(original_grid, grid, sizeof(original_grid));
}

void Sudoku::generate() {
    this->generate_grid(); // generate random grid

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                bool dug_or_not = fifty_fifty(engine);

                if (dug_or_not) { // dug
                    int dugged_cell = original_grid[i][j];
                    bool unique_solution = 1;
                    for (int num = 1; num < 10; ++num) {
                        if (num == dugged_cell) continue;
                        else {
                            original_grid[i][j] = num;

                            if (isValid(i, j, num)) {
                                original_grid[i][j] = num;
                            } else continue;

                            if (solve(0, 0, false)) {
                                unique_solution = 0;
                                break;
                            } 
                        }
                    }

                    if (unique_solution) {
                        original_grid[i][j] = 0;
                        grid[i][j] = 0;
                    } else {
                        original_grid[i][j] = dugged_cell;
                        grid[i][j] = dugged_cell;
                    }

                }

            }
        }
    }


bool Sudoku::generate_grid(int c, int r) {  
    if (c == 9) return solve(0, r + 1);
    if (r == 9) {
        std::memcpy(grid, original_grid, sizeof(original_grid));
        return true;
    }

    if (original_grid[r][c] != 0) return solve(c + 1, r);
    else {
        int tries = 0;
        tryagain:
        int random_num = dist(engine);
        if (isValid(c, r, random_num)) {
            original_grid[r][c] = random_num;
            if (generate_grid(c + 1, r)) {
                return true;
            }
            original_grid[r][c] = 0;
        } else {
            tries++;
            if (tries < 100) {
                goto tryagain;
            } else return false;
        }

        return false;
    }
}


bool Sudoku::solve(int c, int r, bool copy) {
    if (c == 9) return solve(0, r + 1, copy);
    if (r == 9) {
        if (copy)
            std::memcpy(grid, original_grid, sizeof(original_grid)); // solve and save
        else {
            //std::memcpy(original_grid, grid, sizeof(original_grid)); // solve and set it back
        }
        return true;
    }

    if (original_grid[r][c] != 0) return solve(c + 1, r, copy);
    else {
        for (int i = 1; i < 10; ++i) {
            if (isValid(c, r, i)) {
                original_grid[r][c] = i;
                if (solve(c + 1, r, copy)) {
                    return true;
                } 
                original_grid[r][c] = 0;
            }
        }

        return false;
    }
}

bool Sudoku::isValid(int c, int r, int cell) {
    for (int i = 0; i < 9; ++i) {
        if (i != c && original_grid[r][i] == cell) return false; // row
    }


    for (int j = 0; j < 9; ++j) {
        if (j != r && original_grid[j][c] == cell) return false; // coloumn
    }

 
    for (int i = (r / 3) * 3; i < (r / 3) * 3 + 3; ++i) { // block
        for (int j = (c / 3) * 3; j < (c / 3) * 3 + 3; ++j) {
            if (i != r && j != c && original_grid[i][j] == cell) return false;
        }
    }

    return true;

} 

void Sudoku::render_grid() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << grid[i][j] << ' ';
            if ((j + 1) % 3 == 0) std::cout << ' ';
        }

        std::cout << '\n';
        if ((i + 1) % 3 == 0) std::cout << '\n';
    }
}