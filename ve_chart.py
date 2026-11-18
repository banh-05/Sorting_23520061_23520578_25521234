import csv
import matplotlib.pyplot as plt

files = {
    "Selection Sort": "results/SelectionSort_Result.csv",
    "Insertion Sort": "results/InsertionSort_Result.csv",
    "Heap Sort": "results/HeapSort_Result.csv",
    "Quick Sort": "results/QuickSort_Result.csv",
    "Merge Sort": "results/MergeSort_Result.csv",
}

markers = {
    "Selection Sort": "o",
    "Insertion Sort": "s",
    "Heap Sort": "^",
    "Quick Sort": "D",
    "Merge Sort": "v",
}

data = {}
all_n = []

for name, path in files.items():
    ns, times = [], []
    with open(path, "r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            n = int(row["So phan tu"])
            if n not in all_n:
                all_n.append(n)
            val = row["Trung binh (giay)"]
            if val != "N/A" and row["Ket qua"] == "OK":
                ns.append(n)
                times.append(float(val))
    data[name] = dict(zip(ns, times))

def format_n(n):
    if n >= 1_000_000:
        return f"{n // 1_000_000}M"
    if n >= 1_000:
        return f"{n // 1_000}K"
    return str(n)

labels = [format_n(n) for n in all_n]
x_idx = list(range(len(all_n)))

# 1. Bieu do tong quan 5 thuat toan (thang Log-Log de tach ro ca 5 duong)
plt.figure(figsize=(11, 6))
for name in files.keys():
    ns = [n for n in all_n if n in data[name]]
    ts = [data[name][n] for n in ns]
    plt.plot(ns, ts, marker=markers[name], markersize=5, linewidth=2, label=name)

plt.xscale("log")
plt.yscale("log")
plt.title("So sánh thời gian chạy 5 thuật toán sắp xếp (Thang đo Log-Log)", fontsize=12, fontweight="bold")
plt.xlabel("Số phần tử (n)")
plt.ylabel("Thời gian trung bình (giây - thang Log)")
plt.grid(True, which="both", linestyle="--", alpha=0.5)
plt.legend()
plt.tight_layout()
plt.savefig("results/chart_1_tong_quan_5_thuat_toan.png", dpi=300)
plt.close()

# 2. Bieu do nhom O(n^2) gian deu truc ngang
plt.figure(figsize=(12, 6))
for name in ["Selection Sort", "Insertion Sort"]:
    xs = [i for i, n in enumerate(all_n) if n in data[name]]
    ts = [data[name][all_n[i]] for i in xs]
    plt.plot(xs, ts, marker=markers[name], markersize=5, linewidth=2, label=name)
    plt.annotate(f"{ts[-1]:.2f}s", (xs[-1], ts[-1]), textcoords="offset points", xytext=(-10, 8), fontsize=9, fontweight="bold")

plt.xticks(x_idx, labels, rotation=45)
plt.title("So sánh nhóm O(n²): Selection Sort vs Insertion Sort", fontsize=12, fontweight="bold")
plt.xlabel("Kích thước mảng (n)")
plt.ylabel("Thời gian trung bình (giây)")
plt.grid(True, linestyle="--", alpha=0.6)
plt.legend()
plt.tight_layout()
plt.savefig("results/chart_2_nhom_On2.png", dpi=300)
plt.close()

# 3. Bieu do nhom O(n log n) gian deu truc ngang
plt.figure(figsize=(12, 6))
for name in ["Heap Sort", "Quick Sort", "Merge Sort"]:
    xs = [i for i, n in enumerate(all_n) if n in data[name]]
    ts = [data[name][all_n[i]] for i in xs]
    plt.plot(xs, ts, marker=markers[name], markersize=5, linewidth=2, label=name)
    plt.annotate(f"{ts[-1]:.3f}s", (xs[-1], ts[-1]), textcoords="offset points", xytext=(-12, 7), fontsize=9, fontweight="bold")

plt.xticks(x_idx, labels, rotation=45)
plt.title("So sánh chi tiết nhóm O(n log n): Heap, Quick, Merge Sort", fontsize=12, fontweight="bold")
plt.xlabel("Kích thước mảng (n)")
plt.ylabel("Thời gian trung bình (giây)")
plt.grid(True, linestyle="--", alpha=0.6)
plt.legend()
plt.tight_layout()
plt.savefig("results/chart_3_nhom_Onlogn.png", dpi=300)
plt.close()

print("Da xuat 3 bieu do moi ro net trong thu muc results/!")
