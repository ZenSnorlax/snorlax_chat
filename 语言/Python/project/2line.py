import pandas as pd
import matplotlib.pyplot as plt
df1 = pd.read_excel('./data/广告费.xlsx')
df2 = pd.read_excel('./data/销售表.xlsx')
print(df1.head())
print(df2.head())
df1['投放日期'] = pd.to_datetime(df1['投放日期'])
df1 = df1.set_index('投放日期', drop=True)
df2 = df2[['日期', '销售码洋']]
df2['日期'] = pd.to_datetime(df2['日期'])
df2 = df2.set_index('日期', drop=True)
# 按月统计金额
df_x = df1.resample('M').sum().to_period('M')
df_y = df2.resample('M').sum().to_period('M')
# x为广告费，y为销售收入
y1 = pd.DataFrame(df_x['支出'])
y2 = pd.DataFrame(df_y['销售码洋'])
fig = plt.figure()
# 图表字体为黑体，字号为11
plt.rc('font', family='SimHei', size=11)
ax1 = fig.add_subplot(111)  # 添加子图
plt.title('京东电商销售收入与广告费分析折线图')  # 图表标题
# 图表x轴标题
x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
plt.xticks(x, ['1月', '2月', '3月', '4月', '5月', '6月',
           '7月', '8月', '9月', '10月', '11月', '12月'])
ax1.plot(x, y1, color='orangered', linewidth=2,
         linestyle='-', marker='o', mfc='w', label='广告费')
plt.legend(loc='upper left')
ax2 = ax1.twinx()  # 添加一条y轴坐标轴
ax2.plot(x, y2, color='b', linewidth=2, linestyle='-',
         marker='o', mfc='w', label='销售收入')
plt.subplots_adjust(right=0.85)
plt.legend(loc='upper center')
plt.show()
