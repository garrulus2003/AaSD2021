#include <iostream>
#include <vector>

std::vector<int> min_divisor(long long n) {
  std::vector<int> min_div(n + 1, 0);
  for (long long i = 2; i <= n; ++i) {
    if (min_div[i] == 0) {
      if (i * i <= n) {
        for (long long j = i * i; j <= n; j += i) {
          if (min_div[j] == 0) {
            min_div[j] = i;
          }
        }
      }
    }
  }
  return min_div;
}
int main() {
  long long n;
  std::cin >> n;

  std::vector<int> min_div = min_divisor(n);

  long long ans = 0;
  for (int i = 2; i <= n; ++i) {
    ans += min_div[i];
  }

  std::cout << ans;
  return 0;
}