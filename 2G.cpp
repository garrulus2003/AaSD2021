#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

const int MUCH = 10000000;

class Tree {
    struct Node {
        int l;
        int len;
        int link = 0;
        explicit Node(int l = -1, int len = MUCH) : l(l), len(len){};
        std::map<char, int> go;
    };

    std::string s;
    std::vector<Node> nodes;

    int remainder = 0;
    int current_vertex = 0;

    void add(int i);

    int depth_in_edge(int vertex) const;
    void next_case();

    bool can_go(char c);
    bool short_path(char c);
    bool ended_path(char c, int i);

    void no_path(char c, int i, int& prev);

public:
    bool find(const std::string& command);
    void enlarge(char c);

    Tree(const std::string& s) : s(s) {
        nodes.push_back(Node());
        for (int i = 0; i < s.size(); ++i) {
            add(i);
        }
    }
};

void Tree::next_case() {
    if (current_vertex == 0) {
        remainder -= 1;
    } else {
        current_vertex = nodes[current_vertex].link;
    }
}

bool Tree::can_go(char c) {
    return nodes[current_vertex].go.find(c) != nodes[current_vertex].go.end();
};

bool Tree::short_path(char c) {
    return nodes[nodes[current_vertex].go[c]].len < remainder;
}

bool Tree::ended_path(char c, int i) {
    return s[nodes[nodes[current_vertex].go[c]].l + remainder - 1] == s[i];
}

void Tree::no_path(char c, int i, int& prev) {
    nodes.emplace_back(i);
    nodes[current_vertex].go[c] = nodes.size() - 1;

    if (prev != -1) {
        nodes[prev].link = current_vertex;
    }

    prev = -1;
}

void Tree::add(int i) {
    remainder += 1;
    int prev = -1;

    while (remainder > 0) {
        char beginning = s[i - remainder + 1];

        while (can_go(beginning) && short_path(beginning)) {
            int next = nodes[current_vertex].go[beginning];
            remainder -= nodes[next].len;
            current_vertex = next;
            beginning = s[i - remainder + 1];
        }

        if (!can_go(beginning)) {
            no_path(beginning, i, prev);
        } else if (ended_path(beginning, i)) {
            if (prev != -1) {
                nodes[prev].link = current_vertex;
            }
            return;
        } else {
            int next = nodes[current_vertex].go[beginning];
            nodes.push_back(Node(nodes[next].l, remainder - 1));
            if (nodes[next].len < MUCH) {
                nodes[next].len -= (remainder - 1);
            }
            nodes[next].l += (remainder - 1);
            nodes.back().go[s[nodes[next].l]] = next;
            nodes[current_vertex].go[beginning] = nodes.size() - 1;
            nodes.push_back(Node(i));
            nodes[nodes.size() - 2].go[s[i]] = nodes.size() - 1;
            if (prev != -1) {
                nodes[prev].link = nodes.size() - 2;
            }
            prev = nodes.size() - 2;
        }
        next_case();
    }
}

int Tree::depth_in_edge(int vertex) const {
    return (nodes[vertex].len == MUCH) ? (s.size() - nodes[vertex].l)
                                       : nodes[vertex].len;
}

bool Tree::find(const std::string& pattern) {
    int vertex = 0;
    int up = 0;

    for (int i = 0; i < pattern.size(); ++i) {
        if (up == 0) {
            if (nodes[vertex].go.find(pattern[i]) == nodes[vertex].go.end())
                return false;
            vertex = nodes[vertex].go[pattern[i]];
            up = depth_in_edge(vertex) - 1;
        } else {
            int len = depth_in_edge(vertex);
            if (s[nodes[vertex].l + len - up] != pattern[i]) return false;
            --up;
        }
    }
    return true;
}

void Tree::enlarge(char c) {
    s += c;
    add(s.size() - 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Tree t("");
    char symbol;
    std::string text;
    while (std::cin >> symbol >> text) {
        std::transform(text.begin(), text.end(), text.begin(), tolower);
        if (symbol == '?') {
            std::cout << (t.find(text) ? "YES" : "NO") << '\n';
            continue;
        }
        for (int i = 0; i < text.size(); ++i) {
            t.enlarge(text[i]);
        }
    }

    return 0;
}
