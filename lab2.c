#include <stdio.h>

long long count_paths(int i, int j, int n, int m) {
    if (i == n && j == m) return 1;
    if (i > n || j > m)   return 0;

    long long down  = count_paths(i + 1, j, n, m);
    long long right = count_paths(i, j + 1, n, m);
    return down + right;
}

int read_natural(const char *prompt, int *out) {
    printf("%s", prompt);
    if (scanf("%d", out) != 1) {
        printf("Ошибка: введено не число.\n");
        return 0;
    }
    if (*out < 1) {
        printf("Ошибка: число должно быть натуральным (>= 1).\n");
        return 0;
    }
    return 1;
}

int main(void) {
    int n, m;

    if (!read_natural("Введите n: ", &n)) return 1;
    if (!read_natural("Введите m: ", &m)) return 1;

    long long total = count_paths(0, 0, n, m);
    printf("Количество путей: %lld\n", total);

    return 0;
}
