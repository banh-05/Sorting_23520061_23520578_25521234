#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <thread>
#include <future>
using namespace std;

void SelectionSort(vector<int>& a);
void InsertionSort(vector<int>& a);
void HeapSort(vector<int>& a);
void QuickSort(vector<int>& a);
void MergeSort(vector<int>& a);

void chayThongKe(string tenThuatToan, void (*hamSort)(vector<int>&)) {
    string fileKQ = "results/" + tenThuatToan + "_Result.csv";
    ofstream fout(fileKQ);
    if (!fout) {
        cout << "Khong tao duoc file ket qua\n";
        return;
    }

    fout << "Testcase,So phan tu,Thoi gian lan 1 (giay),"
         << "Thoi gian lan 2 (giay),Thoi gian lan 3 (giay),"
         << "Trung binh (giay),Ket qua\n";

    cout << "\n--- " << tenThuatToan << " ---\n";
    bool quaGio = false;

    for (int t = 1; t <= 21; t++) {
        string tenFile = "testcases/TC";
        if (t < 10) tenFile += "0";
        tenFile += to_string(t) + ".txt";

        ifstream fin(tenFile);
        if (!fin) {
            cout << "Khong mo duoc file " << tenFile << '\n';
            continue;
        }

        int n;
        if (!(fin >> n) || n < 0) {
            cout << "File khong hop le: " << tenFile << '\n';
            continue;
        }

        if (quaGio) {
            cout << tenFile << " | n = " << n << " | Qua 5 phut\n";
            fout << tenFile << "," << n << ",N/A,N/A,N/A,N/A,Qua 5 phut\n";
            continue;
        }

        vector<int> a(n);
        bool docDu = true;
        for (int i = 0; i < n; i++) {
            if (!(fin >> a[i])) {
                docDu = false;
                break;
            }
        }
        fin.close();

        if (!docDu) {
            cout << "Du lieu trong file bi thieu: " << tenFile << '\n';
            continue;
        }

        double thoiGian[3] = {0, 0, 0};
        bool dung = true;

        for (int lan = 0; lan < 3; lan++) {
            promise<pair<double, bool>> p;
            auto f = p.get_future();

            thread([b = a, hamSort, p = move(p)]() mutable {
                auto batDau = chrono::steady_clock::now();
                hamSort(b);
                auto ketThuc = chrono::steady_clock::now();

                double tg = chrono::duration<double>(ketThuc - batDau).count();
                bool ok = true;
                for (size_t i = 1; i < b.size(); i++) {
                    if (b[i] < b[i - 1]) {
                        ok = false;
                        break;
                    }
                }
                p.set_value({tg, ok});
            }).detach();

            if (f.wait_for(chrono::seconds(300)) == future_status::timeout) {
                quaGio = true;
                break;
            }

            auto kq = f.get();
            thoiGian[lan] = kq.first;
            dung = kq.second;
            if (!dung) break;
        }

        if (quaGio) {
            cout << tenFile << " | n = " << n << " | Qua 5 phut\n";
            fout << tenFile << "," << n << ",N/A,N/A,N/A,N/A,Qua 5 phut\n";
            continue;
        }

        double trungBinh = dung ? (thoiGian[0] + thoiGian[1] + thoiGian[2]) / 3.0 : 0;

        cout << fixed << setprecision(6);
        cout << tenFile << " | n = " << n
             << " | Lan 1: " << thoiGian[0]
             << " | Lan 2: " << thoiGian[1]
             << " | Lan 3: " << thoiGian[2]
             << " | Trung binh: " << trungBinh
             << " giay | " << (dung ? "OK" : "SAI") << '\n';

        fout << tenFile << "," << n << ","
             << thoiGian[0] << "," << thoiGian[1] << "," << thoiGian[2] << ","
             << trungBinh << "," << (dung ? "OK" : "SAI") << '\n';
    }

    fout.close();
    cout << "Da luu ket qua vao " << fileKQ << '\n';
}

int main() {
    int chon;
    cout << "Chon thuat toan muon do thoi gian:\n";
    cout << "1. Selection Sort\n";
    cout << "2. Insertion Sort\n";
    cout << "3. Heap Sort\n";
    cout << "4. Quick Sort\n";
    cout << "5. Merge Sort\n";
    cout << "6. Chay tat ca 5 thuat toan\n";
    cout << "Nhap lua chon (1-6): ";
    cin >> chon;

    switch (chon) {
        case 1: chayThongKe("SelectionSort", SelectionSort); break;
        case 2: chayThongKe("InsertionSort", InsertionSort); break;
        case 3: chayThongKe("HeapSort", HeapSort); break;
        case 4: chayThongKe("QuickSort", QuickSort); break;
        case 5: chayThongKe("MergeSort", MergeSort); break;
        case 6:
            chayThongKe("SelectionSort", SelectionSort);
            chayThongKe("InsertionSort", InsertionSort);
            chayThongKe("HeapSort", HeapSort);
            chayThongKe("QuickSort", QuickSort);
            chayThongKe("MergeSort", MergeSort);
            break;
        default:
            cout << "Lua chon khong hop le!\n";
    }

    return 0;
}