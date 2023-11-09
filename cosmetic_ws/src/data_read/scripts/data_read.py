import pickle
import matplotlib.pyplot as plt
import glob
import numpy as np
import os
from scipy.signal import butter, filtfilt

exp_date = "1028"
sub_idx = 12

# Low Pass Filter
order = 3
Wn = 1  # cutoff frequency
fs = 100  # sample rate


# Read data from pickle file, plot raw data with opacity and corresponding filtered data
def plot_data(result_folder, data_file):
    with open(data_file, "rb") as file:
        data = pickle.load(file)

    data_np = np.array(data)

    # zeroing the data using the first 100 samples
    data_np -= np.mean(data_np[:100], axis=0)
    # revert the data of z axis
    data_np[:, 2] *= -1

    # Low Pass Filter
    b, a = butter(order, Wn, "lowpass", fs=fs)
    data_filt = filtfilt(b, a, data_np, axis=0)

    # 创建时间序列（以秒为单位）
    time_series = np.arange(0, len(data_np)) / fs

    # Plot
    plt.figure(figsize=(10, 6))
    raw_lines = plt.plot(time_series, data_np, alpha=0.2, label=["X", "Y", "Z"], linewidth=1)
    raw_colors = [line.get_color() for line in raw_lines]
    for i in range(data_filt.shape[1]):
        plt.plot(time_series, data_filt[:, i], label=f"{i}_filt", color=raw_colors[i])

    # Assuming the Z axis data is the third column in data_filt
    z_force = data_filt[:, 2]

    # Identify the start and end of each injection
    above_threshold = z_force > 1
    starts = np.where(np.diff(above_threshold.astype(int)) > 0)[0]
    ends = np.where(np.diff(above_threshold.astype(int)) < 0)[0]

    # Combine starts and ends into a list of tuples
    injections = list(zip(starts, ends))
    print("Injections:", injections)

    for start, end in injections:
        plt.axvspan(time_series[start], time_series[end], facecolor="gray", alpha=0.1)

    # 设置图形标题和标签
    tag = os.path.basename(data_file).replace(".p", "")
    plt.title(f"Force Data Over Time, Exp_ID: {tag}")
    plt.xlabel("Time (s)")
    plt.ylabel("Force Magnitude (N)")
    plt.legend()

    # show the plot
    # plt.show()

    # 构建结果文件名
    result_filename = os.path.join(result_folder, f"result_{os.path.basename(data_file)}.pdf")

    # 保存图形为PNG文件
    plt.savefig(result_filename)

    # 关闭当前图形以准备下一个
    plt.close()


for sub_idx in range(1, 13):
    data_folder = f"./data/{exp_date}/force_data/subject_{sub_idx}/"
    result_folder = f"./data/{exp_date}/result/force_time_graph/subject_{sub_idx}/"

    # 创建结果文件夹（如果不存在）
    os.makedirs(result_folder, exist_ok=True)

    # 获取数据文件列表
    data_files = glob.glob(os.path.join(data_folder, "*.p"))

    for data_file in data_files:
        plot_data(result_folder, data_file)

    print(f"图像已保存在{result_folder}文件夹中。")
