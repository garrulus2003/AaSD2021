//Words sorting realization via Trie structure



#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>

struct trie{
    struct Node{
        int terminal;
        std::map<char, int> to;
        Node() = default;
    };
    std::vector<Node> t;
    void add(std::string s);
    std::vector<std::string> answer();
    void dfs(int i, std::vector<std::string>& ans, std::string& s);
    trie() {
        t.resize(1);
    }
};

void trie::add(std::string s) {
    int current = 0;
    int index = 0;
    while (index < s.size() && t[current].to[s[index]]){
        current = t[current].to[s[index]];
        ++index;
    }
    while (index < s.size()){
        t.push_back(Node());
        t[current].to[s[index]] = t.size() - 1;
        current = t.size() - 1;
        ++index;
    }
    t[current].terminal += 1;
}

void trie::dfs(int i,std::vector<std::string>& ans, std::string& s){
    for (int j = 0; j < t[i].terminal; ++j){
        ans.push_back(s);
    }
    for (auto item : t[i].to){
        dfs(item.second, ans, s += item.first);
    }
    s.pop_back();
}


std::vector<std::string> trie::answer(){
    std::vector<std::string> ans;
    std::string s = "";
    dfs(0, ans, s);
    return ans;
}

int main(){
    trie t;
    std::string s;
    std::cin >> s;
    std::vector<std::string> ss;
    std::vector<int> skips;
    for (int i = 0; i < s.size(); ++i){
        if (s[i] == '.'){
            if (i == 0 || s[i - 1] != '.') skips.push_back(0);
            ++skips[skips.size() - 1];
            continue;
        }
        if (i == 0 || s[i - 1] == '.') ss.push_back("");
        ss[ss.size() - 1] += s[i];
    }
    for (int i = 0; i < ss.size(); ++i) t.add(ss[i]);
    std::vector<std::string> ans = t.answer();
    if (s[0] == '.') {
        for (int i = 0; i < ans.size(); ++i){
            for (int j = 0; j < skips[i]; ++j){
                std::cout << ".";
            }
            std::cout << ans[i];
        }
        if (ans.size() < skips.size()) {
            for (int j = 0; j < skips[skips.size() - 1]; ++j){
                std::cout << ".";
            }
        }
        return 0;
    }
    for (int i = 0; i < skips.size(); ++i){
        std::cout << ans[i];
        for (int j = 0; j < skips[i]; ++j){
            std::cout << ".";
        }
    }
    if (ans.size() > skips.size()) std::cout << ans[ans.size() - 1];
    return 0;
}