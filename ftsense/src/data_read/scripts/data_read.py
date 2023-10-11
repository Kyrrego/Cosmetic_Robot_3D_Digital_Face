import pickle
import matplotlib.pyplot as plt
import glob
import os

data_folder = "./data/"
result_folder = "./data/result/force_time_graph/"

# 创建结果文件夹（如果不存在）
os.makedirs(result_folder, exist_ok=True)

# 获取数据文件列表
data_files = glob.glob(os.path.join(data_folder, "*.p"))

for data_file in data_files:
    with open(data_file, "rb") as file:
        data = pickle.load(file)

    # 将数据分为x、y和z方向的列表
    x_data = [item[0] for item in data]
    y_data = [item[1] for item in data]
    z_data = [item[2] for item in data]

    # 创建时间序列（以秒为单位）
    time_series = list(range(len(data)))

    # 绘制x、y和z方向的力大小变化情况
    plt.figure(figsize=(10, 6))
    plt.plot(time_series, x_data, label="X Direction")
    plt.plot(time_series, y_data, label="Y Direction")
    plt.plot(time_series, z_data, label="Z Direction")

    # 设置图形标题和标签
    plt.title("Force Data Over Time")
    plt.xlabel("Time (s)")
    plt.ylabel("Force Magnitude")
    plt.legend()

    # 构建结果文件名，例如：result_1.png, result_2.png, ...
    result_filename = os.path.join(
        result_folder, f"result_{os.path.basename(data_file)}.png")

    # 保存图形为PNG文件
    plt.savefig(result_filename)

    # 关闭当前图形以准备下一个
    plt.close()

print("图像已保存在./result文件夹中。")
