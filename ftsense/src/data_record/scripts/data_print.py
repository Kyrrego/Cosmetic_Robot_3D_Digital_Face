import pickle
import glob
import os

data_folder = "./data/"

# 获取数据文件列表
data_files = glob.glob(os.path.join(data_folder, "*.p"))

if data_files:
    # 打开第一个pickle文件
    first_data_file = data_files[0]

    with open(first_data_file, "rb") as file:
        data = pickle.load(file)

        # 打印前十行数据
        for i, row in enumerate(data[:10]):
            print(f"Row {i + 1}: {row}")
else:
    print("No data files found in the specified folder.")
