import pandas as pd
import matplotlib.pyplot as plt
titanic = pd.read_csv("./titanic.csv")
plt.rc('font', family='DejaVu Sans', size=10)
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
