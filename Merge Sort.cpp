#include <iostream>
#include <vector>
using namespace std;

void Merge(vector<int>& a, int left, int mid, int right) {
    vector<int> temp;
    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp.push_back(a[i]);
            i++;
        } else {
            temp.push_back(a[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(a[i]);
        i++;
    }

    while (j <= right) {
        temp.push_back(a[j]);
        j++;
    }

    for (int k = 0; k < (int)temp.size(); k++) {
        a[left + k] = temp[k];
    }
}

void MergeSort(vector<int>& a, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    MergeSort(a, left, mid);
    MergeSort(a, mid + 1, right);
    Merge(a, left, mid, right);
}

void MergeSort(vector<int>& a) {
    if (a.empty()) return;
    MergeSort(a, 0, (int)a.size() - 1);
}
