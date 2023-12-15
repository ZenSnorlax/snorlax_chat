import pandas as pd
from sklearn import linear_model
import matplotlib.pyplot as plt
import numpy as np
df1= pd.read_excel('./data/广告费.xlsx')
df2= pd.read_excel('./data/销售表.xlsx')
#数据处理
df1['投放日期'] = pd.to_datetime(df1['投放日期'])
df1= df1.set_index('投放日期',drop=True)
df2=df2[['日期','销售码洋']]
df2['日期'] = pd.to_datetime(df2['日期'])
df2= df2.set_index('日期',drop=True)
#按月统计金额
df_x=df1.resample('M').sum().to_period('M')
df_y=df2.resample('M').sum().to_period('M')
clf=linear_model.LinearRegression()   #创建线性模型
#x为广告费，y为销售收入
x=pd.DataFrame(df_x['支出'])
y=pd.DataFrame(df_y['销售码洋'])
clf.fit(x,y) #拟合线性模型
k=clf.coef_  #获取回归系数
b=clf.intercept_ #获取截距
#未来6个月计划投入的广告费
x0=np.array([120000,130000,150000,180000,200000,250000])
x0=x0.reshape(6,1)    #数组重塑
#预测未来6个月的销售收入（y0）
y0=clf.predict(x0)
print('预测销售收入：')
print(y0)
#使用线性模型预测y值
y_pred =clf.predict(x)
# 图表字体为华文细黑，字号为10
plt.rc('font', family='SimHei',size=11)
plt.figure("京东电商销售数据分析与预测")
plt.scatter(x, y,color='r')                     #真实值散点图
plt.plot(x,y_pred, color='blue', linewidth=1.5) #预测回归线
plt.ylabel(u'销售收入（元）')
plt.xlabel(u'广告费（元）')
plt.subplots_adjust(left=0.2)                   #设置图表距画布左边的空白
plt.show()
#预测评分
from sklearn.metrics import r2_score
y_true = [360000,450000,600000,800000,920000,1300000]# 真实值
score=r2_score(y_true,y0)  # 预测评分
print(score)
