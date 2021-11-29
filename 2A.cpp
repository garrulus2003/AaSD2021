#include <iostream>
#include <string>
#include <vector>

char minimal_symbol = '@';
int letters_number = 257;
std::vector<int> suffix_mass(const std::string& str) {
    std::string s = str + minimal_symbol;
    size_t len = s.size();

    std::vector<int> permutation, classes(len);
    std::vector<std::vector<int>> letters_pos(letters_number);
    for (int i = 0; i < len; ++i) {
        letters_pos[s[i] - minimal_symbol].push_back(i);
    }

    int class_num = 0;
    for (int i = 0; i < letters_number; ++i) {
        if (letters_pos[i].empty()) continue;
        for (int& j : letters_pos[i]) {
            permutation.push_back(j);
            classes[j] = class_num;
        }
        ++class_num;
    }

    int deg = 1;
    while (class_num < len) {
        std::vector<std::vector<int>> new_perm(class_num);

        for (int i = 0; i < len; ++i) {
            size_t current_position = (permutation[i] - deg + 2 * len) % len;
            new_perm[classes[current_position]].push_back(current_position);
        }

        std::vector<int> new_classes(len);
        permutation.resize(0);
        class_num = -1;

        for (int i = 0; i < new_perm.size(); ++i) {
            for (int j = 0; j < new_perm[i].size(); ++j) {
                bool same_class = classes[(new_perm[i][j] + deg) % len] !=
                                  classes[(new_perm[i][j - 1] + deg) % len];
                if (j == 0 || same_class) {
                    ++class_num;
                }
                permutation.push_back(new_perm[i][j]);
                new_classes[new_perm[i][j]] = class_num;
            }
        }

        ++class_num;
        classes = new_classes;
        deg <<= 1;
    }
    return permutation;
}

int main() {
    std::string s;
    std::cin >> s;
    std::vector<int> ans = suffix_mass(s);
    for (int i = 1; i < ans.size(); ++i) {
        std::cout << ans[i] + 1 << " ";
    }
}
