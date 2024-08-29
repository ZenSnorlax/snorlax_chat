import os

# 获取时间
import datetime

year = datetime.datetime.now().year
month = datetime.datetime.now().month

# 获取post名称
post = input("请输入post名称: ")
page = 0

# 自动根据page + 累加的数字生成路由函数
route_name = "page" + str(page)

route = f"""\n\n\n@app.route("/{year}/{month}/{post}")
def {route_name}():
    return "index"
"""
with open("app.py", "a") as f:
    f.write(route)
