#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

// A simple binary-tree node holding a string value
struct Node {
    string val;
    Node*   left  = nullptr;
    Node*   right = nullptr;
    Node(const string& v) : val(v) {}
};

// Print exactly 'count' spaces
void printSpaces(int count) {
    while (count-- > 0) cout << ' ';
}

// Given a full-array representation and its height, draw the tree
void printTree(const vector<string>& arr, int levels) {
    for (int lvl = 0; lvl < levels; ++lvl) {
        int nodes   = 1 << lvl;
        int offset  = (1 << (levels - lvl - 1)) - 1;
        int between = offset * 2 + 1;
        int baseIdx = nodes - 1;

        // 1) Print node labels
        for (int i = 0; i < nodes; ++i) {
            if (i == 0)          printSpaces(offset);
            else                 printSpaces(between);
            const string& v = arr[baseIdx + i];
            cout << (v.empty() ? " " : v);
        }
        cout << "\n";

        // 2) Print one line of branches under this level
        if (lvl < levels - 1) {
            for (int i = 0; i < nodes; ++i) {
                if (i == 0)          printSpaces(offset - 1);
                else                 printSpaces(between - 2);

                int idx     = baseIdx + i;
                int leftIdx = 2*idx + 1;
                int rightIdx= 2*idx + 2;

                // left branch
                cout << (leftIdx < (int)arr.size() && !arr[leftIdx].empty() ? "/" : " ");
                printSpaces(1);
                // right branch
                cout << (rightIdx< (int)arr.size() && !arr[rightIdx].empty() ? "\\" : " ");
            }
            cout << "\n";
        }
    }
}

// Smallest height H so that (2^H - 1) >= count
int computeHeight(int count) {
    int h = 0;
    while ((1 << h) - 1 < count) ++h;
    return h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string,Node*> nodes;
    string line, parent, arrow, children;
    bool   rootSet = false;
    Node*  root    = nullptr;

    // 1) Read lines "P -> L,R" until "end"
    while (getline(cin, line)) {
        if (line == "end")   break;
        if (line.empty())    continue;

        stringstream ss(line);
        if (!(ss >> parent >> arrow >> children) || arrow != "->")
            continue;  // skip malformed lines

        // first valid line defines the root
        if (!rootSet) {
            if (parent == "0") continue;
            rootSet = true;
            nodes[parent] = new Node(parent);
            root = nodes[parent];
        }
        if (!nodes.count(parent)) continue;

        // split "L,R"
        auto pos = children.find(',');
        string L = children.substr(0, pos);
        string R = (pos == string::npos ? "" : children.substr(pos + 1));

        if (L != "0" && !L.empty()) {
            if (!nodes.count(L)) nodes[L] = new Node(L);
            nodes[parent]->left  = nodes[L];
        }
        if (R != "0" && !R.empty()) {
            if (!nodes.count(R)) nodes[R] = new Node(R);
            nodes[parent]->right = nodes[R];
        }
    }

    if (!root) return 0;  // no valid tree built

    // 2) Flatten into a full-array of size (2^H - 1)
    int total  = nodes.size();
    int height = computeHeight(total);
    int size   = (1 << height) - 1;
    vector<string> arr(size, "");

    // BFS-style fill: index(root)=0, left=2*i+1, right=2*i+2
    vector<pair<Node*,int>> queue;
    queue.emplace_back(root, 0);
    for (size_t i = 0; i < queue.size(); ++i) {
        Node* nd  = queue[i].first;
        int   idx = queue[i].second;
        if (idx >= size) continue;
        arr[idx] = nd->val;
        if (nd->left)  queue.emplace_back(nd->left,  2*idx + 1);
        if (nd->right) queue.emplace_back(nd->right, 2*idx + 2);
    }

    // 3) Print the tree—no extra text
    printTree(arr, height);
    return 0;
}