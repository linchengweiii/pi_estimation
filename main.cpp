#include <iostream>
#include <iomanip>

#include <vector>
#include <queue>

#include <thread>
#include <mutex>
#include <functional>

#include <chrono>

#include "ArgumentParser.h"
#include "PIDigitEstimator.h"

using namespace std;
using namespace std::chrono;

inline bool is_correct(vector<int>& digits, int index) {
    return digits[index] / 10 == digits[index-1] % (int)(1e8);
}

inline int max_precision(vector<int>& digits) {
    for (int i = 1; i < digits.size(); i++)
        if (!is_correct(digits, i)) return i-1;
    return digits.size() - 1;
}

void print_pi(vector<int>& digits) {
    for (int i = 0; i < digits.size(); i++) {
        if (i == 1) cout << '.';
        cout << (digits[i] / (int)(1e8));
    }
    cout << endl;
}

// using thread pooling
void estimate_pi(int n_precision, vector<int>& digits) {
    queue<function<void()>> tasks;
    mutex queue_mutex;
    
    for (int i = 1; i <= n_precision; i++) {
        tasks.emplace([&, i] { PIDigitEstimator::get_nth_digit_of_pi(i, digits[i]); });
    }

    vector<thread> workers(thread::hardware_concurrency());
    for (int i = 0; i < workers.size(); i++) {
        auto get_task = [&] (function<void()>& task) {
            unique_lock<mutex> lock(queue_mutex);
            if (tasks.empty()) return false;
            task = move(tasks.front());
            tasks.pop();
            return true;
        };
        auto worker = [&] {
            while (true) {
                function<void()> task;
                if (!get_task(task)) break;
                task();
            }
        };
        workers[i] = thread(worker);
    }

    for (thread& worker: workers)
        worker.join();
}

int main(int argc, char* argv[]) {
    ArgumentParser args;
    args.add_argument("p", "100000");
    args.parse_args(argc, argv);

    auto start = high_resolution_clock::now();

    int n_precision = stoi(args["p"]);
    vector<int> digits(n_precision+1, 314159265);
    estimate_pi(n_precision, digits);

    int maxp = max_precision(digits);
    if (maxp < n_precision) {
        cout << "This program can only handle " << maxp << " precision." << endl;
    } else {
        print_pi(digits);
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken: " << duration.count() / 1000.0 << " seconds" << endl;
}
