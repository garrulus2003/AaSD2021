#include <iostream>
#include <vector>

long long MOD = 1000000007;

long long power(long long a, long long deg) {
  if (deg == 1) {
    return a;
  }
  if (deg % 2 == 0) {
    long long temp = power(a, deg / 2);
    return (temp * temp) % MOD;
  } else {
    return (power(a, deg - 1) * a) % MOD;
  }
}

long long inverted(long long a) { return power(a, MOD - 2); }

long long combinatorics(long long n, long long k,
                        const std::vector<long long>& factorial) {
  if (k > n) return 0;
  long long ans = factorial[n] * inverted(factorial[k]);
  ans %= MOD;
  ans *= inverted(factorial[n - k]);
  ans %= MOD;
  return ans;
}

std::vector<long long> factorials(long long n) {
  std::vector<long long> factorial(n + 1);
  factorial[0] = 1;
  for (int i = 1; i < n + 1; ++i) {
    factorial[i] = factorial[i - 1] * (i);
    factorial[i] %= MOD;
  }
  return factorial;
}

long long stirling(long long n, long long k,
                   const std::vector<long long>& factorial) {
  long long number = 0;
  for (int i = 1; i <= n; ++i) {
    long long current = combinatorics(k, i, factorial);
    current *= power(i, n);
    current %= MOD;
    number += (((k - i) % 2 == 0) ? current : MOD - current);
    number %= MOD;
  }
  number *= inverted(factorial[k]);
  number %= MOD;
  return number;
}

long long summary_weight(long long weights_sum, long long n, long long k) {
  if (n == k) {
    return weights_sum;
  }
  std::vector<long long> factorial = factorials(n);

  long long stirling1 = stirling(n, k, factorial);
  long long stirling2 = stirling(n - 1, k, factorial);

  long long answer = stirling1 + (n - 1) * stirling2;
  answer %= MOD;
  answer *= weights_sum;
  answer %= MOD;
  return answer;
}

int main() {
  long long n, k;
  long long weights_sum = 0;
  long long current_weight = 0;
  std::cin >> n >> k;
  for (long long i = 0; i < n; ++i) {
    std::cin >> current_weight;
    weights_sum += current_weight;
    weights_sum %= MOD;
  }

  std::cout << summary_weight(weights_sum, n, k);

  return 0;
}
