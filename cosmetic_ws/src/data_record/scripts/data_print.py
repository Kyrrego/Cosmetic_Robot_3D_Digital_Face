import pickle
import glob
import os

data_folder = "./data/"

# 获取数据文件列表
data_files = glob.glob(os.path.join(data_folder, "*.p"))

if data_files:
    # 打开第一个pickle文件
    first_data_file = './data/robo_1695891848.8325953.p'  # 打开第一个文件
    # 输出文件名
    print(f"Opening {first_data_file}...")

    with open(first_data_file, "rb") as file:
        data = pickle.load(file)

        # 提取第三列数据并获取其对应的行号
        third_column = [(i, row[2]) for i, row in enumerate(data)]

        # 按第三列数据降序排序
        third_column.sort(key=lambda x: x[1], reverse=False)

        # 打印前十个最大值及其行号
        for i, (row_num, value) in enumerate(third_column[:10]):
            print(f"Row {row_num + 1}: Value = {value:.2f}")

else:
    print("No data files found in the specified folder.")
