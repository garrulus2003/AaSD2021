// Problem G(viruses) solution via Aho-Corasick structure


#include <iostream>
#include <vector>
#include <deque>

struct AC{
    struct Node{
        std::vector<int> to;
        int link;
        bool terminal;
        Node(){
            to.resize(2, -1);
            link = -1;
            terminal = false;
        }
    };
    std::vector<Node> t;
    void add(std::string s){
        int index = 0;
        int current = 0;
        while (index < s.size() && t[current].to[s[index] - '0'] != -1){
            current = t[current].to[s[index] - '0'];
            ++index;
        }
        while (index < s.size()){
            t.push_back(Node());
            t[current].to[s[index] - '0'] = t.size() - 1;
            current = t.size() - 1;
            ++index;
        }
        t[current].terminal = true;
    }

    AC(std::vector<std::string>& v){
        t.resize(1);
        t[0].link = 0;
        for (int i = 0; i < v.size(); ++i) {
            add(v[i]);
        }
        std::deque<int> q;
        for (int i = 0; i < 2; ++i){
            if (t[0].to[i] != -1) continue;
            t[0].to[i] = 0;
        }
        q.push_back(0);
        while (!q.empty()){
            int v = q[0];
            q.pop_front();
            for (int i = 0; i < 2; ++i){
                int u = t[v].to[i];
                if (t[u].link != -1) continue;
                if (v == 0) {
                    t[u].link = 0;
                }
                else{
                    t[u].link = t[t[v].link].to[i];
                    t[u].terminal = t[u].terminal || t[t[t[v].link].to[i]].terminal;
                }
                for (int j = 0; j < 2; ++j){
                    if (t[u].to[j] != -1) continue;
                    t[u].to[j] = t[t[u].link].to[j];
                }
                q.push_back(u);
            }
        }
    }
};

bool dfs(AC& ac, int v, std::vector<int>& marked){
    marked[v] = 1;
    int u = ac.t[v].to[0];
    int w = ac.t[v].to[1];
    if (marked[u] == 1 or marked[w] == 1) {
        return true;
    }
    if (marked[u] == 0 && !ac.t[u].terminal) {
        if (dfs(ac, u, marked)) return true;
    }
    if (marked[w] == 0 && !ac.t[w].terminal) {
        if (dfs(ac, w, marked)) return true;
    }
    marked[v] = 2;
    return false;
}

int main(){
    int n;
    std::cin >> n;
    std::vector<std::string> v(n);
    for (int i = 0; i < n; ++i) std::cin >> v[i];
    AC ac(v);
    int sz = ac.t.size();
    std::vector<int> marked(sz);
    dfs(ac, 0, marked);
    if (dfs(ac, 0, marked)) std::cout << "TAK";
    else std::cout << "NIE";
    return 0;
}