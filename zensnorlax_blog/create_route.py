import os

# 获取时间
import datetime

year = datetime.datetime.now().year
month = datetime.datetime.now().month

# 获取post名称
post = input("请输入post名称: ")

# 自动根据日期生成函数路由名称
route_name = f"{post}_{year}_{month}"

route = f"""\n\n\n@app.route("/{year}/{month}/{post}")
def {route_name}():
    return "index"
"""
with open("app.py", "a") as f:
    f.write(route)
