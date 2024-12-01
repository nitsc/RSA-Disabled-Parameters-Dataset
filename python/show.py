# 导入必要的库
import pandas as pd
import numpy as np
from mayavi import mlab
from matplotlib import colors

# 读取数据
file_path = 'C:\\Users\\admin\\Desktop\\rdpm1hund.csv'
data = pd.read_csv(file_path)

# 获取前5000个数据
x = data['e'].values[:2500]
y = data['q'].values[:2500]
z = data['p'].values[:2500]
lightness = (data['m'].values[:2500]) / 300
size = data['d'].values[:2500] / 30

# 生成颜色（HSL -> RGB）
hue = 0
saturation = 1.0
colors_rgb = [colors.hsv_to_rgb([hue, saturation, b]) for b in lightness]
colors_rgb = np.array(colors_rgb)

# 创建图形窗口
fig = mlab.figure(size=(1920, 1200), bgcolor=(1, 1, 1))

# 逐个点绘制
for i in range(len(x)):
    # 设置每个点的位置、颜色和大小
    mlab.points3d(x[i], y[i], z[i], color=tuple(colors_rgb[i].tolist()), scale_factor=size[i])

# 坐标轴
mlab.axes(xlabel='X', ylabel='Y', zlabel='Z', color=(0, 0, 0), extent=[min(x), max(x), min(y), max(y), min(z), max(z)])

# 在2D窗口下方中央添加文本
mlab.text(0.5, 0.05, 'x轴=e, y轴=q, z轴=p, 颜色亮度=m/500, 大小=d/30, 5000个五维点', width=0.2, color=(0, 0, 0))

print('x轴=e, y轴=q, z轴=p, 颜色亮度=m/300, 大小=d/30, 2500个五维点')

# 显示图形
mlab.show()
