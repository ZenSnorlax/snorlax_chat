import pandas as pd
import matplotlib.pyplot as plt
plt.rc('font', family='DejaVu Sans', size=10)
titanic = pd.read_csv("./titanic.csv")
# 1.获救情况分布，共891位乘客，仅有300多位乘客幸免于难,占比38%
titanic['Survived'].value_counts().plot(kind='bar', color='yellow',
                                        title='Rescue situation', rot=360)
plt.show()
# 2.性别分布，共891位乘客，男性乘客就有577位,占比达64.76%
titanic['Sex'].value_counts().plot(kind='bar', color='pink',
                                   title='Gender distribution', rot=360)
plt.show()
# 3.船舱分布，其中三等舱人数最多，一等舱人口次之。一等舱约占1/4，三等舱约占1/2
titanic['Pclass'].value_counts().plot(kind='bar', color='green',
                                      title='Pclass distribution', rot=360)
plt.show()
# 4.年龄分布，乘客的年龄都集中在20-40岁之间
titanic['Age'].plot(kind='hist', color='red', title='Age distribution')
plt.show()
