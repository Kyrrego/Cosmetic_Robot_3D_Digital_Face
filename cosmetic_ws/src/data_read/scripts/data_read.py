from __future__ import annotations

import pickle
import matplotlib.pyplot as plt
import glob
import numpy as np
import os
from scipy.signal import butter, filtfilt
from itertools import chain

exp_date = "1028"
sub_idx = 12

# Low Pass Filter
order = 3
Wn = 1  # cutoff frequency
fs = 100  # sample rate

avg_forces: dict[str, list] = {}


def process_data(data_file, result_folder):
    with open(data_file, "rb") as file:
        data = pickle.load(file)

    data_np = np.array(data)
    doctor = os.path.basename(data_file).split("_")[0]
    subject = os.path.basename(data_file).split("_")[1]

    # zeroing the data using the first 100 samples
    data_np -= np.mean(data_np[:100], axis=0)
    # revert the data of z axis
    data_np[:, 2] *= -1

    # Low Pass Filter
    b, a = butter(order, Wn, "lowpass", fs=fs)
    data_filt = filtfilt(b, a, data_np, axis=0)

    # Identify the start and end of each injection
    above_threshold = data_filt[:, 2] > 1  # if z force greater than 1N
    starts = np.where(np.diff(above_threshold.astype(int)) > 0)[0]
    ends = np.where(np.diff(above_threshold.astype(int)) < 0)[0]
    injections = list(zip(starts, ends))

    global avg_forces
    if doctor not in avg_forces:
        avg_forces[doctor] = []
    avg_forces[doctor].append([np.mean(data_filt[start:end, 2]) for start, end in injections])

    # plot_data(data_np, data_filt, injections, doctor, subject, result_folder)


def plot_data(data_np, data_filt, injections, doctor, subject, result_folder):
    # 创建时间序列（以秒为单位）
    time_series = np.arange(0, len(data_np)) / fs

    # Plot
    plt.figure(figsize=(10, 6))
    raw_lines = plt.plot(time_series, data_np, alpha=0.2, label=["X", "Y", "Z"], linewidth=1)
    raw_colors = [line.get_color() for line in raw_lines]
    for i in range(data_filt.shape[1]):
        plt.plot(time_series, data_filt[:, i], label=f"{i}_filt", color=raw_colors[i])

    # mark injections
    for start, end in injections:
        plt.axvspan(time_series[start], time_series[end], facecolor="gray", alpha=0.1)

    # 设置图形标题和标签
    tag = os.path.basename(data_file).replace(".p", "")
    plt.title(f"Force Data Over Time, Exp_ID: {tag}")
    plt.xlabel("Time (s)")
    plt.ylabel("Force Magnitude (N)")
    plt.legend()

    # 保存图形为PDF文件
    result_filename = os.path.join(result_folder, f"{doctor}_{subject}.pdf")
    plt.savefig(result_filename)

    # 关闭当前图形以准备下一个
    plt.close()


for sub_idx in range(1, 13):
    data_folder = f"./data/{exp_date}/force_data/subject_{sub_idx}/"
    result_folder = f"./data/{exp_date}/result/force_time_graph/"

    # 创建结果文件夹（如果不存在）
    os.makedirs(result_folder, exist_ok=True)

    # 获取数据文件列表
    data_files = glob.glob(os.path.join(data_folder, "*.p"))

    for data_file in data_files:
        process_data(data_file, result_folder)

    print(f"图像已保存在{result_folder}文件夹中。")

print(avg_forces)

stat = {
    doctor: [
        np.mean(np.array(list(chain.from_iterable(avg_forces[doctor]))), axis=0),
        np.std(np.array(list(chain.from_iterable(avg_forces[doctor]))), axis=0),
    ]
    for doctor in avg_forces
}

print(stat)

plt.figure(figsize=(10, 6))
# plot the average force of each doctor as bar graph with error bar
for doctor in stat:
    plt.bar(
        doctor,
        stat[doctor][0],
        yerr=stat[doctor][1],
        capsize=5,
        label=doctor,
    )

plt.title("Average Injection Force")
plt.xlabel("Doctor")
plt.ylabel("Force (N)")
plt.legend()
plt.savefig(f"./data/{exp_date}/result/force_avg.pdf")
