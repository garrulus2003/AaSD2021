//Words sorting realization via Trie structure

#include <iostream>
#include <string>
#include <vector>
#include <map>

class trie {
private:
    struct Node {
        int terminal;
        std::map<char, int> to;
        Node() = default;
    };

    std::vector<Node> nodes;
    void add(const std::string& s);
    void all_words(int i, std::vector<std::string>& ans, std::string& s);

public:
    std::vector<std::string> all_words();
    trie() { nodes.resize(1); }
    trie(const std::vector<std::string>& v)
    {
        nodes.resize(1);
        for (const auto& str : v)
            add(str);
    }
};

void trie::add(const std::string& s)
{
    int current = 0;
    int index = 0;
    while (index < s.size() && nodes[current].to[s[index]]) {
        current = nodes[current].to[s[index]];
        ++index;
    }
    while (index < s.size()) {
        nodes.push_back(Node());
        nodes[current].to[s[index]] = nodes.size() - 1;
        current = nodes.size() - 1;
        ++index;
    }
    nodes[current].terminal += 1;
}

void trie::all_words(int i, std::vector<std::string>& ans, std::string& s)
{
    for (int j = 0; j < nodes[i].terminal; ++j) {
        ans.push_back(s);
    }
    for (auto item : nodes[i].to) {
        all_words(item.second, ans, s += item.first);
    }
    s.pop_back();
}

std::vector<std::string> trie::all_words()
{
    std::vector<std::string> ans;
    std::string s = "";
    all_words(0, ans, s);
    return ans;
}

std::vector<int> count_skips(const std::string& s)
{
    std::vector<int> skips;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '.') {
            if (i == 0 || s[i - 1] != '.')
                skips.push_back(0);
            ++skips[skips.size() - 1];
            continue;
        }
    }
    return skips;
}

std::vector<std::string> find_all_words(const std::string& s)
{
    std::vector<std::string> wordlist;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '.')
            continue;
        if (i == 0 || s[i - 1] == '.')
            wordlist.push_back("");
        wordlist[wordlist.size() - 1] += s[i];
    }
    return wordlist;
}

template <typename T, typename U>
void print_merged(const std::vector<T>& first, const std::vector<U>& second)
{
    for (size_t i = 0; i < second.size(); ++i) {
        std::cout << first[i] << second[i];
    }
    if (second.size() < first.size())
        std::cout << first.back();
}

std::vector<std::string> skips_to_points(std::vector<int>& skips)
{
    std::vector<std::string> points;
    for (auto skip : skips) {
        points.push_back("");
        for (int i = 0; i < skip; ++i)
            points.back() += ".";
    }
    return points;
}
int main()
{
    std::string s;
    std::cin >> s;

    std::vector<std::string> wordlist = find_all_words(s);
    trie t(wordlist);
    std::vector<std::string> sorted_wordlist = t.all_words();

    std::vector<int> skips = count_skips(s);
    std::vector<std::string> points = skips_to_points(skips);

    if (s[0] == '.')
        print_merged<std::string, std::string>(points, sorted_wordlist);
    else
        print_merged<std::string, std::string>(sorted_wordlist, points);
    return 0;
}
