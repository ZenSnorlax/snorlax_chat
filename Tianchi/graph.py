import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
#
#
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
#
#
# 构造Sex与Survived均值的条形图
sex_pivot = titanic.pivot_table(index="Sex", values="Survived")
sex_pivot.plot.bar(rot=360)
plt.show()
# 构造Class与Survived均值的条形图
class_pivot = titanic.pivot_table(index="Pclass", values="Survived")
class_pivot.plot.bar(rot=360)
plt.show()
# 构造SibSp与Survived均值的条形图
SibSp_pivot = titanic.pivot_table(index="SibSp", values="Survived")
SibSp_pivot.plot.bar(rot=360)
plt.show()
# 构造Parch与Survived均值的条形图
Parch_pivot = titanic.pivot_table(index="Parch", values="Survived")
Parch_pivot.plot.bar(rot=360)
plt.show()
#
#
# 探索多个变量与Survived的关系
g = sns.FacetGrid(titanic, col='Survived')
g.map(plt.hist, 'Age', bins=20)
# 探索年龄与获救人数的关系：
grid = sns.FacetGrid(titanic, col='Survived',
                     row='Pclass', height=2.2, aspect=1.6)
grid.map(plt.hist, 'Age', alpha=0.5, bins=20)
# 探索年龄、舱位与获救人数的关系：
grid = sns.FacetGrid(titanic, row='Embarked', height=2.2, aspect=1.6)
grid.map(sns.pointplot, 'Pclass', 'Survived', 'Sex', palette='deep',
         order=[1, 2, 3], hue_order=['male', 'female'])
grid.add_legend()
# 探索登船港口、舱位、性别与获救比例的关系：
grid = sns.FacetGrid(titanic, row='Embarked',
                     col='Survived', height=2.2, aspect=1.6)
grid.map(sns.barplot, 'Sex', 'Fare', alpha=0.5,
         errorbar=None, order=['female', 'male'])
grid.add_legend()
plt.show()
