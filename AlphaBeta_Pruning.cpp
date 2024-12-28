#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <chrono>

using namespace std;

// Minimax function with Alpha-Beta Pruning
int minimax(int depth, int nodeIndex, bool isMax, vector<int>& scores, int alpha, int beta, int height) {
    // Base case: leaf node
    if (depth == height) {
        return scores[nodeIndex];
    }

    if (isMax) {
        int best = numeric_limits<int>::min();

        // Traverse all children
        for (int i = 0; i < 2; i++) {
            int val = minimax(depth + 1, nodeIndex * 2 + i, false, scores, alpha, beta, height);
            best = max(best, val);
            alpha = max(alpha, best);

            // Alpha-Beta Pruning
            if (beta <= alpha) {
                break;
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();

        // Traverse all children
        for (int i = 0; i < 2; i++) {
            int val = minimax(depth + 1, nodeIndex * 2 + i, true, scores, alpha, beta, height);
            best = min(best, val);
            beta = min(beta, best);

            // Alpha-Beta Pruning
            if (beta <= alpha) {
                break;
            }
        }
        return best;
    }
}

int main() {
    // Example leaf nodes (scores)
    vector<int> scores = {3, 5, 2, 9, 12, 5, 23, 23, 2,4, 12, 32, 124, 23, 42, 22, 4, 4, 12, 12, 33, 221, 21, 22,3, 5, 2, 9, 12, 5, 23, 23, 2,4, 12, 32, 124, 23,42,22,4,4,12,12,33,221,21,22};

    // Calculate the height of the tree
    int height = ceil(log2(scores.size()));

    // Run the algorithm 100,000 times and measure execution time
    auto start = chrono::high_resolution_clock::now();

    int alpha = numeric_limits<int>::min();
    int beta = numeric_limits<int>::max();
    int optimum = 0;

    // Run 100,000 iterations
    for (int i = 0; i < 100000; i++) {
        optimum = minimax(0, 0, true, scores, alpha, beta, height);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    // Calculate the average execution time per iteration
    double avg_time_per_iteration = duration.count() / 100000.0;

    // Output results
    cout << "The optimal value is: " << optimum << endl;
    cout << "Execution time (total): " << duration.count() << " nanoseconds" << endl;
    cout << "Average execution time per iteration: " << avg_time_per_iteration << " nanoseconds" << endl;

    return 0;
}
