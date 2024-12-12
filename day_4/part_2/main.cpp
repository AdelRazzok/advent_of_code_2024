#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool    is_half_cross_valid(char up, char down) {
    return (up == 'M' && down == 'S') || (up == 'S' && down == 'M');
}

bool    is_in_bounds(int row, int col, int row_size, int col_size) {
    return row >= 0 && col >= 0 && row < row_size && col < col_size;
}

bool    is_xmas_cross_at(vector<vector<char>> &grid, int row, int col, int row_size, int col_size) {
    bool    is_first_half_valid;
    bool    is_second_half_valid;

    if (!is_in_bounds(row + 1, col + 1, row_size, col_size) ||
        !is_in_bounds(row + 1, col -1, row_size, col_size) ||
        !is_in_bounds(row - 1, col + 1, row_size, col_size) ||
        !is_in_bounds(row - 1, col - 1, row_size, col_size)
    ) {
        return false;
    }

    is_first_half_valid = is_half_cross_valid(grid[row - 1][col - 1], grid[row + 1][col + 1]);
    is_second_half_valid = is_half_cross_valid(grid[row - 1][col + 1], grid[row + 1][col - 1]);

    return is_first_half_valid && is_second_half_valid;
}

void    count_xmas_occurences(vector<vector<char>> &grid) {
    int row_size = grid.size();
    int col_size = grid[0].size();
    int count = 0;

    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            if (grid[i][j] == 'A' && is_xmas_cross_at(grid, i, j, row_size, col_size)) {
                count++;
            }
        }
    }
    cout << "Number of MAS crosses: " << count << endl;
}

void    handle_file(ifstream &file) {
    string                  line;
    vector<vector<char>>    grid;

    while (getline(file, line)) {
        vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }
    count_xmas_occurences(grid);
}

int     main(int argc, char **argv) {
    ifstream    file;
    string      line;

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    file.open(argv[1], ifstream::in);

    if (!file.is_open()) {
        cerr << "Error: cannot open file " << argv[1] << endl;
        return 1;
    }

    handle_file(file);
    file.close();

    return 0;
}
