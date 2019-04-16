#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <climits>

/*
 * Used for
 * https://stackoverflow.com/questions/55714369/are-there-performance-concerns-when-constructing-lambdas-inside-other-functions
 *
 *
 * Conclusion:
 * I've noticed a significant difference on several runs of this benchmark;
 * however, none of the runs have a consistently signficant difference.
 * f2 generally wins, but there have been a few times when f1 has one
 */

using namespace std;
using namespace std::chrono;

int f1(vector<int>& v) {
    for_each(v.begin(), v.end(), [](int i) { i * i; });
}

auto mult_int = [](int i) { i * i; };
int f2(vector<int>& v) {
    for_each(v.begin(), v.end(), mult_int);
}

int main() {
    // INT_MAX == 2147483647
    const int len = 1000000000;
    vector<int> v(len);
    for (int i = 0; i < len; i++) {
        v[i] = i;
    }

    cout << "Measruing f1" << endl;
    auto start = high_resolution_clock::now();
    f1(v);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;

    cout << endl;

    cout << "Measruing f2" << endl;
    start = high_resolution_clock::now();
    f2(v);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;
}

