import pickle
import matplotlib.pyplot as plt
import glob
import os

data_folder = "./data/"

# 获取数据文件列表
data_files = glob.glob(os.path.join(data_folder, "*.p"))

# 创建存储所有数据的列表
all_data = []

# # 逐个读取数据文件并合并数据
# for data_file in data_files:
#     with open(data_file, "rb") as file:
#         data = pickle.load(file)
#         all_data.extend(data)

with open(data_files[0], "rb") as file:
    all_data = pickle.load(file)

# 将数据分为x、y和z方向的列表
x_data = [item[0] for item in all_data]
y_data = [item[1] for item in all_data]
z_data = [item[2] for item in all_data]

# 创建时间序列（以秒为单位）
time_series = list(range(len(all_data)))

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

# 显示图形
plt.show()
