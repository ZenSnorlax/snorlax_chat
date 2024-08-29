import os

# 获取时间
import datetime

year = datetime.datetime.now().year
month = datetime.datetime.now().month

# 获取post名称
post = input("请输入post名称: ")

route = f"""
def app.route("/{year}/{month}/{post}"):
    return "{post}"
"""
with open("app.py", "w") as f:
    f.write(route)
