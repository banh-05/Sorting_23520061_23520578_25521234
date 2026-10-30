
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;

void MergeSort(vector<int>& a);

int main() {
    ofstream fout("results/MergeSort_Result.csv");

    if (!fout) {
        cout << "Khong tao duoc file ket qua\n";
        return 1;
    }

    fout << "Testcase,So phan tu,Thoi gian lan 1 (giay),"
         << "Thoi gian lan 2 (giay),Thoi gian lan 3 (giay),"
         << "Trung binh (giay),Ket qua\n";

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
            cout << "Du lieu trong file bi thieu: "
                 << tenFile << '\n';
            continue;
        }

        vector<int> original = a;
        double thoiGian[3];
        bool dung = true;

        for (int lan = 0; lan < 3; lan++) {
            vector<int> b = original;

            auto batDau = chrono::steady_clock::now();
            MergeSort(b);
            auto ketThuc = chrono::steady_clock::now();

            thoiGian[lan] =
                chrono::duration<double>(ketThuc - batDau).count();

            for (int i = 1; i < n; i++) {
                if (b[i] < b[i - 1]) {
                    dung = false;
                    break;
                }
            }

            if (!dung) break;
        }

        double trungBinh = 0;

        if (dung) {
            trungBinh =
                (thoiGian[0] + thoiGian[1] + thoiGian[2]) / 3.0;
        }

        cout << fixed << setprecision(6);
        cout << tenFile << " | n = " << n
             << " | Lan 1: " << thoiGian[0]
             << " | Lan 2: " << thoiGian[1]
             << " | Lan 3: " << thoiGian[2]
             << " | Trung binh: " << trungBinh
             << " giay | " << (dung ? "OK" : "SAI")
             << '\n';

        fout << tenFile << "," << n << ","
             << thoiGian[0] << ","
             << thoiGian[1] << ","
             << thoiGian[2] << ","
             << trungBinh << ","
             << (dung ? "OK" : "SAI") << '\n';
    }

    fout.close();

    cout << "\nDa luu ket qua vao results/MergeSort_Result.csv\n";

    return 0;
}
