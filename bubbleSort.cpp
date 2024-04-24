//bubble_sort

#include <iostream>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        #pragma omp parallel for shared(swapped)
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

       
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;

    

    double start_time = omp_get_wtime(); // Start measuring time
    cout<<"start time: "<<start_time<<endl;

    bubbleSort(arr, n);
    double end_time = omp_get_wtime(); // End measuring time
    cout<<"end time: "<<end_time<<endl;

    cout << "Sorted array: ";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;

    cout << "Execution time: " << end_time - start_time << " seconds" << endl;

    return 0;
}
