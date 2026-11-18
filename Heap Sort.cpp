#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static void heapify(vector<int>& a, int n, int i) {
    while (true) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && a[l] > a[largest]) largest = l;
        if (r < n && a[r] > a[largest]) largest = r;

        if (largest == i) break;

        swap(a[i], a[largest]);
        i = largest;
    }
}

void HeapSort(vector<int>& a) {
    int n = (int)a.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}