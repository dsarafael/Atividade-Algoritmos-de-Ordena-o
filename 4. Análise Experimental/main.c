#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ----------------------------------------------
   Função auxiliar: troca dois elementos
------------------------------------------------*/
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/* ============================================================
                    BUBBLE SORT
============================================================ */
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/* ============================================================
                    INSERTION SORT
============================================================ */
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

/* ============================================================
                    SELECTION SORT
============================================================ */
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min])
                min = j;
        }

        swap(&arr[i], &arr[min]);
    }
}

/* ============================================================
                    MERGE SORT
============================================================ */
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = malloc(sizeof(int) * n1);
    int *R = malloc(sizeof(int) * n2);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_rec(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort_rec(arr, l, m);
        merge_sort_rec(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge_sort(int arr[], int n) {
    merge_sort_rec(arr, 0, n - 1);
}

/* ============================================================
                    QUICK SORT
============================================================ */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort_rec(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quick_sort_rec(arr, low, p - 1);
        quick_sort_rec(arr, p + 1, high);
    }
}

void quick_sort(int arr[], int n) {
    quick_sort_rec(arr, 0, n - 1);
}

/* ============================================================
                    SHELL SORT
============================================================ */
void shell_sort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}

/* ============================================================
                GERADORES DE VETORES
============================================================ */
void fill_random(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = rand();
}

void fill_sorted(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

void fill_reverse(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

/* ============================================================
                FUNÇÃO DE MEDIÇÃO DE TEMPO
============================================================ */
double measure(void (*sort)(int*, int), void (*fill)(int*, int), int n)
{
    int *arr = malloc(n * sizeof(int));
    fill(arr, n);

    clock_t start = clock();
    sort(arr, n);
    clock_t end = clock();

    free(arr);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

/* ============================================================
                PROGRAMA PRINCIPAL
============================================================ */
int main() {
    srand(time(NULL));

    int sizes[] = {10, 100, 1000, 10000};
    void (*fills[])(int*, int) = {fill_sorted, fill_random, fill_reverse};
    char *fill_names[] = {"Ordenado", "Aleatório", "Invertido"};

    void (*sorts[])(int*, int) =
    { bubble_sort, insertion_sort, selection_sort,
      merge_sort, quick_sort, shell_sort };

    char *sort_names[] = {"Bubble", "Insertion", "Selection",
                          "Merge", "Quick", "Shell"};

    for (int s = 0; s < 4; s++) {
        int n = sizes[s];
        printf("\n======= N = %d =======\n", n);

        for (int f = 0; f < 3; f++) {
            printf("\nCaso: %s\n", fill_names[f]);

            for (int so = 0; so < 6; so++) {
                double t = measure(sorts[so], fills[f], n);
                printf("  %-10s : %f s\n", sort_names[so], t);
            }
        }
    }

    return 0;
}
