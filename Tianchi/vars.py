import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd 
plt.rc('font', family='DejaVu Sans', size=10)
titanic = pd.read_csv("./titanic.csv")
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
