import pandas as pd
import matplotlib.pyplot as plt
df= pd.read_excel('./data/销售表.xlsx')
df=df[['日期','销售码洋']]
df['日期'] = pd.to_datetime(df['日期'])    #将日期转换为日期格式
df1= df.set_index('日期',drop=True)        #设置日期为索引
#按天统计销售数据
df_d=df1.resample('D').sum().to_period('D')
print(df_d)
#按月统计销售数据
df_m=df1.resample('M').sum().to_period('M')
print(df_m)
df_d.to_excel('result1.xlsx') #导出结果
df_m.to_excel('result2.xlsx') #导出结果
#图表字体为黑体，字号为10
plt.rc('font', family='SimHei',size=10)
#绘制子图
fig = plt.figure(figsize=(9,5))
ax=fig.subplots(1,2)   #创建Axes对象
#分别设置图表标题
ax[0].set_title('按天分析销售收入')
ax[1].set_title('按月分析销售收入')
df_d.plot(ax=ax[0],color='r')             #第一个图折线图
df_m.plot(kind='bar',ax=ax[1],color='g')  #第二个图柱形图
#调整图表距上部和底部的空白
plt.subplots_adjust(top=0.95,bottom=0.15)
plt.show()
