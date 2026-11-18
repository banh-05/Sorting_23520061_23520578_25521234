# Sorting_23520061_23520578_25521234

Bài tập chương Tìm kiếm và Sắp xếp — Môn **Cấu trúc dữ liệu và Giải thuật** (GVHD: ThS. Nguyễn Thị Ngọc Diễm).

## 1. Giới thiệu dự án
Dự án thực hiện cài đặt, kiểm thử và thống kê thời gian chạy thực tế của 5 thuật toán sắp xếp phổ biến trên mảng một chiều gồm các số nguyên sinh ngẫu nhiên:
- **Selection Sort** (Sắp xếp chọn)
- **Insertion Sort** (Sắp xếp chèn)
- **Heap Sort** (Sắp xếp vun đống)
- **Quick Sort** (Sắp xếp nhanh)
- **Merge Sort** (Sắp xếp trộn)

Mỗi thuật toán được kiểm thử trên **21 bộ dữ liệu** có kích thước tăng dần từ `100` đến `1,000,000` phần tử. Tại mỗi testcase, chương trình chạy độc lập **3 lần**, tự động kiểm tra tính đúng đắn của mảng sau khi sắp xếp và tính thời gian trung bình (giới hạn thời gian chờ tối đa 5 phút cho mỗi lượt chạy).

## 2. Cấu trúc thư mục
```text
Sorting_23520061_23520578_25521234/
├── main.cpp
├── Selection Sort.cpp
├── Insertion Sort.cpp
├── Heap Sort.cpp
├── Quick Sort.cpp
├── Merge Sort.cpp
├── 21testcases.cpp
├── ve_chart.py
├── testcases/
│   ├── TC01.txt
│   ├── TC02.txt
│   ├── ...
│   └── TC21.txt
├── results/
│   ├── SelectionSort_Result.csv
│   ├── InsertionSort_Result.csv
│   ├── HeapSort_Result.csv
│   ├── QuickSort_Result.csv
│   ├── MergeSort_Result.csv
│   ├── Bang_Tong_Hop.csv
│   ├── chart_1_tong_quan_5_thuat_toan.png
│   ├── chart_2_nhom_On2.png
│   └── chart_3_nhom_Onlogn.png
└── README.md
```

## 3. Chức năng các thành phần

| Tệp / Thư mục | Mô tả |
| :--- | :--- |
| `main.cpp` | Chương trình chính: hiển thị menu chọn thuật toán, đọc testcase, đo thời gian chạy 3 lần bằng `<chrono>`, kiểm tra kết quả và xuất file CSV |
| `Selection Sort.cpp` | Cài đặt thuật toán Selection Sort |
| `Insertion Sort.cpp` | Cài đặt thuật toán Insertion Sort |
| `Heap Sort.cpp` | Cài đặt thuật toán Heap Sort |
| `Quick Sort.cpp` | Cài đặt thuật toán Quick Sort (khử đệ quy nhánh dài để tránh tràn stack khi `n = 1,000,000`) |
| `Merge Sort.cpp` | Cài đặt thuật toán Merge Sort |
| `21testcases.cpp` | Chương trình sinh tự động 21 bộ dữ liệu kiểm thử ngẫu nhiên |
| `ve_chart.py` | Script Python tổng hợp số liệu từ 5 file CSV và vẽ biểu đồ so sánh trực quan |
| `testcases/` | Chứa 21 file dữ liệu đầu vào (`TC01.txt` đến `TC21.txt`) |
| `results/` | Lưu trữ các file CSV kết quả đo thời gian, bảng tổng hợp và biểu đồ PNG |
| `README.md` | Tài liệu giới thiệu cấu trúc và hướng dẫn chạy dự án |

## 4. Hướng dẫn biên dịch và chạy chương trình

### Chạy chương trình đo thời gian (C++)
Mở Terminal tại thư mục gốc của dự án, biên dịch toàn bộ các file `.cpp` với cờ tối ưu `-O2` và chạy:

```bash
g++ -O2 main.cpp "Selection Sort.cpp" "Insertion Sort.cpp" "Heap Sort.cpp" "Quick Sort.cpp" "Merge Sort.cpp" -o main.exe
./main.exe
```

Sau khi chạy, nhập số từ `1` đến `6` theo menu để đo riêng từng thuật toán hoặc chạy toàn bộ 5 thuật toán. Kết quả sẽ tự động lưu vào thư mục `results/`.

### Xuất bảng tổng hợp và biểu đồ (Python)
Yêu cầu cài đặt thư viện `matplotlib`:

```bash
pip install matplotlib
python ve_chart.py
```
