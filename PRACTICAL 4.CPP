#include <iostream>
#include <chrono>
#include <limits>

using namespace std;

// Iterative Factorial
unsigned long long factorialIterative(int n) {
    unsigned long long result = 1;

    for (int i = 2; i <= n; i++) {
        if (result > numeric_limits<unsigned long long>::max() / i) {
            throw overflow_error("Factorial is too large for unsigned long long.");
        }
        result *= i;
    }

    return result;
}

// Recursive Factorial
unsigned long long factorialRecursive(int n) {
    if (n == 0 || n == 1)
        return 1;

    unsigned long long prev = factorialRecursive(n - 1);

    if (prev > numeric_limits<unsigned long long>::max() / n) {
        throw overflow_error("Factorial is too large for unsigned long long.");
    }

    return n * prev;
}

int main() {
    int n;

    cout << "Enter a non-negative integer (0-20): ";
    cin >> n;

    if (cin.fail() || n < 0) {
        cout << "Invalid input!\n";
        return 1;
    }

    if (n > 20) {
        cout << "Warning: 21! and above exceed the range of unsigned long long.\n";
        return 1;
    }

    try {
        // Iterative timing
        auto startIter = chrono::high_resolution_clock::now();
        unsigned long long iterResult = factorialIterative(n);
        auto endIter = chrono::high_resolution_clock::now();

        // Recursive timing
        auto startRec = chrono::high_resolution_clock::now();
        unsigned long long recResult = factorialRecursive(n);
        auto endRec = chrono::high_resolution_clock::now();

        auto iterTime =
            chrono::duration_cast<chrono::nanoseconds>(endIter - startIter);

        auto recTime =
            chrono::duration_cast<chrono::nanoseconds>(endRec - startRec);

        cout << "\n========== Factorial Comparison ==========\n";
        cout << "Number               : " << n << endl;
        cout << "Factorial            : " << iterResult << endl;
        cout << "------------------------------------------\n";
        cout << "Iterative Time       : " << iterTime.count() << " ns\n";
        cout << "Recursive Time       : " << recTime.count() << " ns\n";

        if (iterResult == recResult)
            cout << "Results Match        : Yes\n";
        else
            cout << "Results Match        : No\n";

    }
    catch (const overflow_error &e) {
        cout << e.what() << endl;
    }

    return 0;
}