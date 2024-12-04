#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void    handle_file(ifstream &file) {
    string      line;
    size_t      pos;
    vector<int> list_one, list_two;
    int         result = 0;

    while (getline(file, line)) {
        pos = line.find("   ");
        list_one.push_back(stoi(line.substr(0, pos)));
        list_two.push_back(stoi(line.substr(pos + 3)));
    }
    sort(list_one.begin(), list_one.end());
    sort(list_two.begin(), list_two.end());

    if (list_one.size() != list_two.size()) {
        cerr << "Error: lists are not the same size" << endl;
        exit(1);
    }

    for (size_t i = 0; i < list_one.size(); i++) {
        result += abs(list_one[i] - list_two[i]);
    }
    cout << "Result: " << result << endl;
}

int     main(int argc, char **argv) {
    ifstream    file;

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
    return 0;
}
