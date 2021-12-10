#include <iostream>
#include <vector>
#include <complex>

using complex = std::complex<double>;
double PI = 3.14159265358979;

class Polynom : std::vector<complex> {
    int max_size = 1 << 17;
    void fft(bool invert);

public:
    Polynom operator*(const Polynom& other);
    void read(long long deg);
    void print(long long deg) const;
};

//
Polynom Polynom::operator*(const Polynom& other) {
    Polynom first, second;
    first.resize(max_size, 0);
    second.resize(max_size, 0);
    for (int i = 0; i < max_size; ++i) {
        first[i] = at(i);
        second[i] = other[i];
    }
    first.fft(false);
    second.fft(false);
    for (int i = 0; i < max_size; ++i) {
        first[i] *= second[i];
    }
    first.fft(true);
    std::vector<int> ans;
    ans.resize(max_size);
    return first;
}

void Polynom::fft(bool invert) {
    if (size() == 1) return;

    Polynom first, second;
    first.resize(size() / 2);
    second.resize(size() / 2);

    for (int i = 0; i < size() / 2; ++i) {
        first[i] = at(2 * i);
        second[i] = at(2 * i + 1);
    }

    first.fft(invert);
    second.fft(invert);

    complex current = 1;
    double angle = invert ? -2 * PI / size() : 2 * PI / size();
    complex turn(cos(angle), sin(angle));

    for (int i = 0; i < size() / 2; ++i) {
        at(i) = first[i] + current * second[i];
        at(i + size() / 2) = first[i] - current * second[i];
        current *= turn;

        if (invert) {
            at(i) /= complex(2);
            at(i + size() / 2) /= complex(2);
        }
    }
}

void Polynom::read(long long n) {
    resize(max_size, 0);
    for (long long i = 0; i < n + 1; ++i) {
        std::cin >> at(n - i);
    }
}

void Polynom::print(long long deg) const {
    for (int i = 0; i < deg + 1; ++i) {
        std::cout << int(llround(at(deg - i).real())) << " ";
    }
}

int main() {
    Polynom v, u;

    long long n, m;
    std::cin >> n;
    v.read(n);
    std::cin >> m;
    u.read(m);

    Polynom ans = v * u;
    std::cout << n + m << " ";
    ans.print(n + m);
    return 0;
}
