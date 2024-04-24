//mergesort
#include<iostream>
#include<omp.h>

using namespace std;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int temp[n1 + n2], i = l, j = m + 1, k = 0;
    
    while (i <= m && j <= r)
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];

    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    
    for (int p = 0; p < k; p++) arr[l + p] = temp[p];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, l, m);
            #pragma omp section
            mergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    const int n = 100; // Define the size of the array
    int arr[n]; // Declare an array of size n

    // Generate 100 random numbers and fill the array
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 1000; // Generates random numbers between 0 and 999
    }

    cout << "ORIGINAL ARRAY" << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << endl;

    mergeSort(arr, 0, n - 1);

    cout << "SORTED ARRAY" << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << endl;

    return 0;
}
