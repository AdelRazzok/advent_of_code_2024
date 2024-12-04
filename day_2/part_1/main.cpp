#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> convert_line_to_vector(const string &line) {
    vector<int>     numbers;
    int             number;
    istringstream   iss(line);

    while (iss >> number) {
        numbers.push_back(number);
    }
    return numbers;
}

bool        is_line_safe(const string &line) {
    vector<int> numbers;
    int         diff;
    bool        is_increasing = false;
    bool        is_decreasing = false;

    numbers = convert_line_to_vector(line);

    for (size_t i = 1; i < numbers.size(); i++) {
        diff = abs(numbers[i] - numbers[i - 1]);
        if (diff < 1 || diff > 3) {
            return false;
        }

        if (numbers[i] > numbers[i - 1]) {
            is_increasing = true;
        }
        if (numbers[i] < numbers[i - 1]) {
            is_decreasing = true;
        }

        if (is_increasing && is_decreasing) {
            return false;
        }
    }
    return true;
}

void        handle_file(ifstream &file) {
    string  line;
    int     nb_safe_lines = 0;

    while (getline(file, line)) {
        if (is_line_safe(line)) {
            nb_safe_lines++;
        }
    }
    cout << "Number of safe lines: " << nb_safe_lines << endl;
}

int         main(int argc, char **argv) {
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
