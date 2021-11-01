#include <iostream>
#include <vector>
#include <deque>

template <int alphabet_size>
class AC {
private:
    struct Node {
        std::vector<int> to;
        int link;
        bool terminal;
        Node()
        {
            to.resize(alphabet_size, -1);
            link = -1;
            terminal = false;
        }
    };

    std::vector<Node> trie;
    void add(const std::string& s)
    {
        int index = 0;
        int current = 0;
        while (index < s.size() && trie[current].to[s[index] - '0'] != -1) {
            current = trie[current].to[s[index] - '0'];
            ++index;
        }
        while (index < s.size()) {
            trie.push_back(Node());
            trie[current].to[s[index] - '0'] = trie.size() - 1;
            current = trie.size() - 1;
            ++index;
        }
        trie[current].terminal = true;
    }

    void add_element(int parent, int letter_number)
    {
        int son = trie[parent].to[letter_number];
        if (parent == 0) {
            trie[son].link = 0;
        }
        else {
            int extended_father = trie[trie[parent].link].to[letter_number];
            trie[son].link = extended_father;
            trie[son].terminal = trie[son].terminal || trie[extended_father].terminal;
        }
        for (int j = 0; j < alphabet_size; ++j) {
            if (trie[son].to[j] != -1)
                continue;
            trie[son].to[j] = trie[trie[son].link].to[j];
        }
    }

public:
    explicit AC(std::vector<std::string>& v)
    {
        trie.resize(1);
        trie[0].link = 0;
        for (auto& i : v) {
            add(i);
        }
        std::deque<int> adding_queue;
        for (int i = 0; i < alphabet_size; ++i) {
            if (trie[0].to[i] != -1)
                continue;
            trie[0].to[i] = 0;
        }
        adding_queue.push_back(0);
        while (!adding_queue.empty()) {
            int vertex = adding_queue[0];
            adding_queue.pop_front();
            for (int i = 0; i < alphabet_size; ++i) {
                if (trie[trie[vertex].to[i]].link != -1)
                    continue;
                add_element(vertex, i);
                adding_queue.push_back(trie[vertex].to[i]);
            }
        }
    }

    bool is_cyclic()
    {
        std::vector<int> marked(trie.size());
        return is_cyclic(0, marked);
    }

private:
    bool is_cyclic(int vertex, std::vector<int>& marked)
    {
        marked[vertex] = 1;

        for (auto vertex_to: trie[vertex].to) {
            if (marked[vertex_to] == 1)
                return true;
            if (marked[vertex_to] == 0 && !trie[vertex_to].terminal) {
                if (is_cyclic(vertex_to, marked))
                    return true;
            }
        }
        marked[vertex] = 2;
        return false;
    }
};

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::string> v(n);
    for (int i = 0; i < n; ++i)
        std::cin >> v[i];
    AC<2> ac(v);
    std::cout << (ac.is_cyclic() ? "TAK" : "NIE");
    return 0;
}
