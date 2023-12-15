import pandas as pd
import matplotlib.pyplot as plt
df1= pd.read_excel('./data/广告费.xlsx')
df2= pd.read_excel('./data/销售表.xlsx')
df1['投放日期'] = pd.to_datetime(df1['投放日期'])
df1= df1.set_index('投放日期',drop=True)
df2=df2[['日期','销售码洋']]
df2['日期'] = pd.to_datetime(df2['日期'])
df2= df2.set_index('日期',drop=True)
# 按月统计金额
df_x=df1.resample('M').sum().to_period('M')
df_y=df2.resample('M').sum().to_period('M')
#x为广告费，y为销售收入
x=pd.DataFrame(df_x['支出'])
y=pd.DataFrame(df_y['销售码洋'])
# 图表字体为黑体，字号为11
plt.rc('font', family='SimHei',size=11)
plt.figure("京东电商销售收入与广告费分析散点图")
plt.scatter(x, y,color='r')     #真实值散点图
plt.xlabel(u'广告费（元）')
plt.ylabel(u'销售收入（元）')
plt.subplots_adjust(left=0.15)  #图表距画布右侧之间的空白
plt.show()
