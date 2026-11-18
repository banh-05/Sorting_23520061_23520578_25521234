#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static void quickSortHelper(vector<int>& a, int left, int right) {
    while (left < right) {
        int i = left;
        int j = right;
        int pivot = a[left + (right - left) / 2];

        while (i <= j) {
            while (a[i] < pivot) i++;
            while (a[j] > pivot) j--;
            if (i <= j) {
                swap(a[i], a[j]);
                i++;
                j--;
            }
        }

        if (j - left < right - i) {
            if (left < j) quickSortHelper(a, left, j);
            left = i;
        } else {
            if (i < right) quickSortHelper(a, i, right);
            right = j;
        }
    }
}

void QuickSort(vector<int>& a) {
    if (a.size() <= 1) return;
    quickSortHelper(a, 0, (int)a.size() - 1);
}