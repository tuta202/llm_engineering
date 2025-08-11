
#include <iostream>
#include <vector>
#include <cstdint>     // For uint32_t
#include <algorithm>   // For std::max
#include <chrono>      // For timing

// Linear Congruential Generator (LCG) function
class LCG {
public:
    LCG(uint32_t seed, uint32_t a = 1664525, uint32_t c = 1013904223, uint32_t m = 4294967296) 
        : value(seed), A(a), C(c), M(m) {}

    uint32_t next() {
        value = (A * value + C) % M;
        return value;
    }

private:
    uint32_t value;
    const uint32_t A, C, M;
};

// Function to calculate maximum subarray sum
int64_t max_subarray_sum(int n, uint32_t seed, int min_val, int max_val) {
    LCG lcg(seed);
    std::vector<int> random_numbers(n);

    // Generate random numbers
    for (int i = 0; i < n; ++i) {
        random_numbers[i] = lcg.next() % (max_val - min_val + 1) + min_val;
    }

    // Kadane's algorithm to calculate maximum subarray sum
    int64_t max_sum = INT64_MIN, current_sum = 0;
    for (int i = 0; i < n; ++i) {
        current_sum = std::max<int64_t>(random_numbers[i], current_sum + random_numbers[i]);
        max_sum = std::max(max_sum, current_sum);
    }
    return max_sum;
}

// Function to calculate total maximum subarray sum over 20 runs
int64_t total_max_subarray_sum(int n, uint32_t initial_seed, int min_val, int max_val) {
    int64_t total_sum = 0;
    LCG lcg(initial_seed);

    for (int i = 0; i < 20; ++i) {
        uint32_t seed = lcg.next();
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }

    return total_sum;
}

int main() {
    // Parameters
    int n = 10000;              // Number of random numbers
    uint32_t initial_seed = 42; // Initial seed for the LCG
    int min_val = -10;          // Minimum value of random numbers
    int max_val = 10;           // Maximum value of random numbers

    // Timing the function
    auto start_time = std::chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();

    // Output result and timing
    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << "\n";
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Execution Time: " << elapsed.count() << " seconds\n";

    return 0;
}
