# generate_route.py
import os
import sqlite3
from datetime import datetime

# 获取当前时间
now = datetime.now()
year = now.year
month = now.month
day = now.day

# 连接到数据库
conn = sqlite3.connect("page_numbers.db")
cursor = conn.cursor()

# 获取当前的page_number
cursor.execute("SELECT page_number FROM page_info WHERE id = 1")
page_number = cursor.fetchone()[0]

# 生成新的路由
route_name = f"page_{page_number}"

route = f"""\n\n@app.route("/{year}/{month}/{day}")
def {route_name}():
    return "index"
"""

# 将路由写入文件
with open("app.py", "a") as f:
    f.write(route)

# 增加page_number并更新数据库
cursor.execute("UPDATE page_info SET page_number = page_number + 1 WHERE id = 1")
conn.commit()
conn.close()
