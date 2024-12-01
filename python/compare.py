import pandas as pd
from collections import defaultdict

# 读取 CSV 文件
df = pd.read_csv('C:\\Users\\admin\\Desktop\\rdpm1hund.csv')

# 统计每个数值与其他数值的大小关系
greater_than_count = defaultdict(int)
less_than_count = defaultdict(int)

# 遍历所有行
for index, row in df.iterrows():
    # 获取每行的所有变量
    m = row['m']
    c = row['c']
    e = row['e']
    p = row['p']
    q = row['q']
    d = row['d']
    
    # 将每个数值存入字典
    values = {'m': m, 'c': c, 'e': e, 'p': p, 'q': q, 'd': d}
    
    # 比较每个数值与其他数值的大小
    for var1 in values:
        for var2 in values:
            if var1 != var2:
                if values[var1] < values[var2]:
                    less_than_count[var1] += 1
                    greater_than_count[var2] += 1
                else:
                    less_than_count[var2] += 1
                    greater_than_count[var1] += 1

# 根据统计结果得到一个明确的排序
sorted_variables = sorted(less_than_count.items(), key=lambda x: x[1], reverse=True)

# 输出最终排序
sorted_order = [var for var, count in sorted_variables]
print("全局大小排序：")
print(" < ".join(sorted_order))
