from flask import Flask, url_for

app = Flask(__name__)


@app.route("/")
def index():
    return "Hello World"


@app.route("/archives")
def archives():
    return "archives"


@app.route("/2024/8/29")
def page_5():
    # 使用 url_for 生成指向静态文件的 URL
    file_url = url_for("static", filename="2024_8_29.html")
    return f"<a href='{file_url}'>Open the file</a>"
