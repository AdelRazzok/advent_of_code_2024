#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

auto loadData(ifstream &file) {
    vector<pair<int, int>>  rules;
    vector<vector<int>>     updates;
    string                  line;
    bool                    readingRules = true;

    while (getline(file, line)) {
        if (line.empty()) {
            readingRules = false;
            continue;
        }

        if (readingRules) {
            size_t delimiter = line.find('|');
            int x = stoi(line.substr(0, delimiter));
            int y = stoi(line.substr(delimiter + 1));
            rules.emplace_back(x, y);
        } else {
            vector<int> update;
            istringstream lineStream(line);
            string number;
            while (getline(lineStream, number, ',')) {
                update.push_back(stoi(number));
            }
            updates.push_back(update);
        }
    }
    return make_tuple(rules, updates);
}

unordered_map<int, vector<int>> buildGraph(const vector<pair<int, int>> &rules) {
    unordered_map<int, vector<int>> graph;
    for (const pair<int, int> &rule : rules) {
        graph[rule.first].push_back(rule.second);
    }
    return graph;
}

bool isValidUpdate(const unordered_map<int, vector<int>> &graph, const vector<int> &update) {
    unordered_map<int, int> indexMap;

    for (size_t i = 0; i < update.size(); ++i) {
        indexMap[update[i]] = i;
    }
    for (const pair<int, vector<int>> &entry : graph) {
        int x = entry.first;
        const vector<int> &dependencies = entry.second;

        if (indexMap.find(x) != indexMap.end()) {
            for (int dependency : dependencies) {
                if (indexMap.find(dependency) != indexMap.end() && indexMap[x] > indexMap[dependency]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int getMiddlePage(const vector<int> &update) {
    return update[update.size() / 2];
}

auto calculateResult(const vector<pair<int, int>> &rules, const vector<vector<int>> &updates) {
    unordered_map<int, vector<int>> graph = buildGraph(rules);
    vector<vector<int>>             validUpdates;
    int                             sumMiddlePages = 0;

    for (const vector<int> &update : updates) {
        if (isValidUpdate(graph, update)) {
            validUpdates.push_back(update);
            sumMiddlePages += getMiddlePage(update);
        }
    }
    return make_tuple(sumMiddlePages, validUpdates);
}

void handleFile(ifstream &file) {
    auto [rules, updates] = loadData(file);
    auto [result, validUpdates] = calculateResult(rules, updates);

    cout << "Sum of middle pages: " << result << endl;
    cout << "Valid updates: " << endl;
    for (const vector<int> &update : validUpdates) {
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

    handleFile(file);
    file.close();

    return 0;
}
