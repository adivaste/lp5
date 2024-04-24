//min _max_ assign.3

#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int n = 10; // Number of elements in the array
    int arr[n] = {10, 5, 8, 3, 9, 2, 7, 4, 6, 1}; // Sample array

    // Initialize variables for min, max, sum, and average
    int min_val = arr[0];
    int max_val = arr[0];
    int sum_val = 0;
    double avg_val = 0.0;

    // Parallel reduction for finding min, max, and sum
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum_val)
    for (int i = 0; i < n; ++i) {
        min_val = min(min_val, arr[i]);
        max_val = max(max_val, arr[i]);
        sum_val += arr[i];
    }

    // Calculate average
    avg_val = static_cast<double>(sum_val) / n;

    // Output results
    cout << "Minimum: " << min_val << endl;
    cout << "Maximum: " << max_val << endl;
    cout << "Sum: " << sum_val << endl;
    cout << "Average: " << avg_val << endl;

    return 0;
}
