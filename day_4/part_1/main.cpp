#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class   Direction {
    public:
        int x;
        int y;

        Direction(int x, int y) : x(x), y(y) {}

        bool    is_move_valid(int row, int col, const vector<vector<char>> &grid) const {
            return (
                row >= 0 && row < grid.size() &&
                col >= 0 && col < grid[row].size()
            );
        }
};

const vector<Direction> directions = {
    Direction(-1, 0),   // Up
    Direction(-1, 1),   // Up right
    Direction(0, 1),    // Right
    Direction(1, 1),    // Down right
    Direction(1, 0),    // Down
    Direction(1, -1),   // Down left
    Direction(0, -1),   // Left
    Direction(-1, -1)   // Up left
};

int     get_xmas_occurences_from_pos(int row, int col, const vector<vector<char>> &grid) {
    string  xmas_word = "XMAS";
    int     xmas_occurences = 0;

    for (Direction dir : directions) {
        bool    can_explore = true;

        for (int i = 0; i < xmas_word.size(); i++) {
            int new_row = row + dir.x * i;
            int new_col = col + dir.y * i;

            if (!dir.is_move_valid(new_row, new_col, grid)) {
                can_explore = false;
                break;
            }

            if (grid[new_row][new_col] != xmas_word[i]) {
                can_explore = false;
                break;
            }
        }

        if (can_explore) {
            xmas_occurences++;
        }
    }
    return xmas_occurences;
} 

void    count_xmas_occurences(vector<vector<char>> &grid) {
    int xmas_occurences = 0;

    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] == 'X') {
                xmas_occurences += get_xmas_occurences_from_pos(row, col, grid);
            }
        }
    }
    cout << "Xmas occurences: " << xmas_occurences << endl;
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
