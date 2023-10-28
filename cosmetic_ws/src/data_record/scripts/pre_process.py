import pickle
import matplotlib.pyplot as plt
import glob
import os

data_folder = "./data/"
result_folder = "./data/result/pre_process"

# data_name = [robo_1695891344.5341144.p, robo_1695891660.6068246.p, robo_1695891747.7542102
#               robo_1695891848.8325953.p, robo_1695891924.3209918.p]

# scale = [[1000, 2000], [1500, 2700], [3000, 4200], [1200,2200], [800,1700]]

# 创建结果文件夹（如果不存在）
os.makedirs(result_folder, exist_ok=True)

# 获取数据文件列表
data_files = glob.glob(os.path.join(data_folder, "robo_1695891924.3209918.p"))

# 指定要保留的数据范围
start_index = 800
end_index = 1700

for data_file in data_files:
    with open(data_file, "rb") as file:
        data = pickle.load(file)

    # 截取感兴趣的数据范围
    data_subset = data[start_index:end_index]

    # 构建新pickle文件名
    new_pickle_filename = os.path.basename(data_file).replace(".p", "_new.p")
    new_pickle_filepath = os.path.join(result_folder, new_pickle_filename)

    # 将data_subset保存到新pickle文件中
    with open(new_pickle_filepath, "wb") as new_pickle_file:
        pickle.dump(data_subset, new_pickle_file)

    # 将数据分为x、y和z方向的列表
    x_data = [item[0] for item in data_subset]
    y_data = [item[1] for item in data_subset]
    z_data = [item[2] for item in data_subset]

    # 创建时间序列（以秒为单位）
    time_series = list(range(len(data_subset)))

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

    # 显示图片
    plt.show()

    '''# 构建结果文件名，例如：result_1.png, result_2.png, ...
    result_filename = os.path.join(
        result_folder, f"result_{os.path.basename(data_file)}.png")

    # 保存图形为PNG文件
    plt.savefig(result_filename)'''

    # 关闭当前图形以准备下一个
    plt.close()

print("图像已保存在./result文件夹中。")
