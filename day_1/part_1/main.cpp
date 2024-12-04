#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
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

    while (getline(file, line)) {
        cout << line << endl;
    }

    return 0;
}
