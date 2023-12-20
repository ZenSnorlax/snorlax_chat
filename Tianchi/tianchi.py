import re
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import warnings
plt.rc('font', family = "DejaVu Sans", size = 10 )
warnings.filterwarnings("ignore")
train_data = pd.read_csv("./date/titanic_train.csv")
test_data = pd.read_csv("./date/titanic_test.csv")
from sklearn.ensemble import RandomForestRegressor

#choose training data to predict age
age_df = train_data[['Age','Survived','Fare', 'Parch', 'SibSp', 'Pclass']]
age_df_notnull = age_df.loc[(train_data['Age'].notnull())]
age_df_isnull = age_df.loc[(train_data['Age'].isnull())]
X = age_df_notnull.values[:,1:]
Y = age_df_notnull.values[:,0]

# use RandomForestRegression to train data
RFR = RandomForestRegressor(n_estimators=1000, n_jobs=-1)
RFR.fit(X,Y)
predictAges = RFR.predict(age_df_isnull.values[:,1:])
train_data.loc[train_data['Age'].isnull(), ['Age']]= predictAges
print(train_data.groupby(['Sex','Survived'])['Survived'].count())
train_data[['Sex','Survived']].groupby(['Sex']).mean()
plt.show()
