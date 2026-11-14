// e-Olymp 1964 "What is left?"
// In-place array filtering. The cycle is: drop even positions,
// drop odd positions, drop positions divisible by 3, then repeat.
// Positions are renumbered from 1 after every pass.

#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }

    int len = n;
    int phase = 0;
    while (len > 1) {
        int w = 0;
        for (int i = 0; i < len; ++i) {
            int pos = i + 1;
            bool keep = phase == 0 ? (pos % 2 == 1)
                      : phase == 1 ? (pos % 2 == 0)
                                   : (pos % 3 != 0);
            if (keep) {
                a[w++] = a[i];
            }
        }
        len = w;
        phase = (phase + 1) % 3;
    }

    std::cout << a[0] << '\n';
    return 0;
}
