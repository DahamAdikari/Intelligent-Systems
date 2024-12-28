#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <chrono>

using namespace std;

// Minimax function
int minimax(int depth, int nodeIndex, bool isMaximizingPlayer, const vector<int>& scores, int height) {
    // Base case: leaf node
    if (depth == height) {
        return scores[nodeIndex];
    }

    if (isMaximizingPlayer) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 2; ++i) { // Two children
            int val = minimax(depth + 1, nodeIndex * 2 + i, false, scores, height);
            best = max(best, val);
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 2; ++i) { // Two children
            int val = minimax(depth + 1, nodeIndex * 2 + i, true, scores, height);
            best = min(best, val);
        }
        return best;
    }
}

int main() {
    // Example game tree with depth 3 (2^3 = 8 leaf nodes)
    vector<int> scores = {3, 5, 2, 9, 12, 5, 23, 23}; // Leaf node values
    int height = ceil(log2(scores.size())); // Calculate the height of the tree

    // Compute the optimal value once
    int optimal_value = minimax(0, 0, true, scores, height);
    cout << "The optimal value is: " << optimal_value << endl;

    // Measure execution time over multiple iterations
    int repeat_count = 100000; // Number of iterations
    auto start_time = chrono::high_resolution_clock::now();

    for (int i = 0; i < repeat_count; ++i) {
        minimax(0, 0, true, scores, height);
    }

    auto end_time = chrono::high_resolution_clock::now();

    // Calculate total duration
    auto total_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();

    // Average time per execution
    double average_time = static_cast<double>(total_time) / repeat_count;

    // Output execution times
    cout << "Execution time (total): " << total_time << " nanoseconds" << endl;
    cout << "Average execution time per iteration: " << average_time << " nanoseconds" << endl;

    return 0;
}