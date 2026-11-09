#include <stdio.h>
#include <stdlib.h>

static void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int read_int(const char *prompt, int min_value)
{
    int value;
    int ok;

    while (1) {
        printf("%s", prompt);
        ok = scanf("%d", &value);
        if (ok == 1 && value >= min_value) {
            clear_input();
            return value;
        }
        if (ok == EOF) {
            fprintf(stderr, "Ввод прерван.\n");
            exit(EXIT_FAILURE);
        }
        printf("Ошибка: введите целое число не меньше %d.\n", min_value);
        clear_input();
    }
}

static double read_double(const char *prompt)
{
    double value;
    int ok;

    while (1) {
        printf("%s", prompt);
        ok = scanf("%lf", &value);
        if (ok == 1) {
            clear_input();
            return value;
        }
        if (ok == EOF) {
            fprintf(stderr, "Ввод прерван.\n");
            exit(EXIT_FAILURE);
        }
        printf("Ошибка: введите число.\n");
        clear_input();
    }
}

static double **create_matrix(int n, int m)
{
    int i;
    double **a = (double **)malloc((size_t)n * sizeof(double *));

    if (a == NULL) {
        return NULL;
    }
    for (i = 0; i < n; i++) {
        a[i] = (double *)malloc((size_t)m * sizeof(double));
        if (a[i] == NULL) {
            while (--i >= 0) {
                free(a[i]);
            }
            free(a);
            return NULL;
        }
    }
    return a;
}

static void free_matrix(double **a, int n)
{
    int i;

    if (a == NULL) {
        return;
    }
    for (i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
}

static void print_matrix(double **a, int n, int m)
{
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%10.3f ", a[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int n, m, i, j;
    double **a;
    double A, product, col_min;
    int diag_len;
    char prompt[64];

    printf("Вариант 25\n");

    n = read_int("Введите количество строк N: ", 1);
    m = read_int("Введите количество столбцов M: ", 1);

    a = create_matrix(n, m);
    if (a == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            snprintf(prompt, sizeof(prompt), "a[%d][%d] = ", i + 1, j + 1);
            a[i][j] = read_double(prompt);
        }
    }

    printf("\nИсходная матрица:\n");
    print_matrix(a, n, m);

    diag_len = (n < m) ? n : m;
    A = a[0][0];
    for (i = 1; i < diag_len; i++) {
        if (a[i][i] < A) {
            A = a[i][i];
        }
    }
    printf("\n1) Минимальный элемент главной диагонали A = %.3f\n", A);

    product = A;
    for (j = 0; j < m; j++) {
        col_min = a[0][j];
        for (i = 1; i < n; i++) {
            if (a[i][j] < col_min) {
                col_min = a[i][j];
            }
        }
        printf("   Минимум столбца %d: %.3f\n", j + 1, col_min);
        product *= col_min;
    }
    printf("2) Произведение A и минимумов столбцов P = %.3f\n", product);

    if (n >= 2 && m >= 4) {
        a[1][3] = product;
        printf("3) Элемент a24 заменён на %.3f\n", product);
        printf("\nМатрица после замены:\n");
        print_matrix(a, n, m);
    } else {
        printf("3) Замена невозможна: в матрице нет элемента a24 "
               "(нужно минимум 2 строки и 4 столбца).\n");
    }

    free_matrix(a, n);
    return EXIT_SUCCESS;
}
