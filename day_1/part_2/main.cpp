#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void    handle_file(ifstream &file) {
    string      line;
    size_t      pos;
    vector<int> list_one, list_two;
    int         nb_occurences;
    int         result = 0;

    while (getline(file, line)) {
        pos = line.find("   ");
        list_one.push_back(stoi(line.substr(0, pos)));
        list_two.push_back(stoi(line.substr(pos + 3)));
    }

    for (size_t i = 0; i < list_one.size(); i++) {
        nb_occurences = 0;

        for (size_t j = 0; j < list_two.size(); j++) {
            if (list_one[i] == list_two[j]) {
                nb_occurences++;
            }
        }
        result += list_one[i] * nb_occurences;
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
    file.close();

    return 0;
}
