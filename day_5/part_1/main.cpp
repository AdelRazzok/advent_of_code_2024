#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

auto load_data(ifstream &file) {
    vector<pair<int, int>>  rules;
    vector<vector<int>>     updates;
    string                  line;
    bool                    reading_rules = true;

    while (getline(file, line)) {
        if (line.empty()) {
            reading_rules = false;
            continue;
        }

        if (reading_rules) {
            size_t delimiter = line.find('|');
            int x = stoi(line.substr(0, delimiter));
            int y = stoi(line.substr(delimiter + 1));
            rules.emplace_back(x, y);
        } else {
            vector<int> update;
            istringstream line_stream(line);
            string number;
            while (getline(line_stream, number, ',')) {
                update.push_back(stoi(number));
            }
            updates.push_back(update);
        }
    }
    return make_tuple(rules, updates);
}

unordered_map<int, vector<int>> build_graph(const vector<pair<int, int>> &rules) {
    unordered_map<int, vector<int>> graph;

    for (const pair<int, int> &rule : rules) {
        graph[rule.first].push_back(rule.second);
    }
    return graph;
}

bool is_valid_update(const unordered_map<int, vector<int>> &graph, const vector<int> &update) {
    unordered_map<int, int> index_map;

    for (size_t i = 0; i < update.size(); ++i) {
        index_map[update[i]] = i;
    }
    for (const pair<int, vector<int>> &entry : graph) {
        int x = entry.first;
        const vector<int> &dependencies = entry.second;

        if (index_map.find(x) != index_map.end()) {
            for (int dependency : dependencies) {
                if (index_map.find(dependency) != index_map.end() && index_map[x] > index_map[dependency]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int get_middle_page(const vector<int> &update) {
    return update[update.size() / 2];
}

auto calculate_result(const vector<pair<int, int>> &rules, const vector<vector<int>> &updates) {
    unordered_map<int, vector<int>> graph = build_graph(rules);
    vector<vector<int>>             valid_updates;
    int                             sum_middle_pages = 0;

    for (const vector<int> &update : updates) {
        if (is_valid_update(graph, update)) {
            valid_updates.push_back(update);
            sum_middle_pages += get_middle_page(update);
        }
    }
    return make_tuple(sum_middle_pages, valid_updates);
}

void handle_file(ifstream &file) {
    auto [rules, updates] = load_data(file);
    auto [result, valid_updates] = calculate_result(rules, updates);

    cout << "Sum of middle pages: " << result << endl;
    cout << "Valid updates: " << endl;
    for (const vector<int> &update : valid_updates) {
        for (size_t i = 0; i < update.size(); ++i) {
            cout << update[i];
            if (i < update.size() - 1) cout << ",";
        }
        cout << endl;
    }
}

int main(int argc, char **argv) {
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
