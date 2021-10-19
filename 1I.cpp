//Z-function
//Input: a string is given
//Output: an array of values that z-function has on this string



#include <iostream>
#include <string>
#include <vector>

std::vector<int> zet(std::string s){
    std::vector<int> z(s.size());
    z[0] = 0;
    int l = 0;
    int r = 0;

    for (int i = 1; i < s.size(); ++i){
        z[i] = std::max(0, std::min(r - i, z[i - l]));
        while(i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r){
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
int main(){
    std::string s;
    std::cin >> s;
    std::vector<int> ans = zet(s);
    for (int i = -0; i < s.size(); ++i) {
        std::cout << ans[i] << " ";
    }

    return 0;
}