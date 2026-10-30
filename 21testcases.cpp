// Tao 21 file testcase chua mang so nguyen ngau nhien
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
using namespace std;

void TestCase(const string& folder, int id, int n, mt19937& rng) {
    string fileName = folder + "/TC";

    if (id < 10) fileName += "0";
    fileName += to_string(id) + ".txt";

    ofstream fout(fileName);

    if (!fout) {
        cerr << "Khong tao duoc file: " << fileName << '\n';
        return;
    }

    uniform_int_distribution<int> dist(-1000000, 1000000);

    fout << n << '\n';

    for (int i = 0; i < n; i++) {
        fout << dist(rng) << ' ';
    }

    fout << '\n';
    cout << "Da tao " << fileName << '\n';
}

int main() {
    const string folder = "testcases";
    random_device rd;
    mt19937 rng(rd());

    vector<int> sizes = {
        100, 1000, 10000, 20000, 30000,
        40000, 50000, 60000, 70000, 80000,
        100000, 150000, 200000, 250000, 300000,
        500000, 600000, 700000, 800000, 900000,
        1000000
    };

    for (int i = 0; i < (int)sizes.size(); i++) {
        TestCase(folder, i + 1, sizes[i], rng);
    }

    cout << "Da tao xong " << sizes.size() << " testcase.\n";

    return 0;
}
