
#include <iostream>
#include <iomanip>
#include <chrono>

// High-performance implementation of the given code
double calculate(int iterations, int param1, int param2) {
    double result = 1.0;  // Use double for floating-point precision
    for (int i = 1; i <= iterations; ++i) {
        int j = i * param1 - param2;
        result -= (1.0 / j);
        j = i * param1 + param2;
        result += (1.0 / j);
    }
    return result;
}

int main() {
    constexpr int iterations = 100000000;  // 100 million iterations
    constexpr int param1 = 4;
    constexpr int param2 = 1;

    auto start_time = std::chrono::high_resolution_clock::now();
    double result = calculate(iterations, param1, param2) * 4;
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << std::fixed << std::setprecision(12);
    std::cout << "Result: " << result << "\n";
    std::cout << "Execution Time: " << elapsed.count() << " seconds\n";

    return 0;
}
