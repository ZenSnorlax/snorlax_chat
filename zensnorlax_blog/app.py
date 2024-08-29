from flask import Flask, render_template

app = Flask(__name__)


@app.route("/")
def index():
    return "Hello World"


@app.route("/archives")
def archives():
    return "archives"


@app.route("/2024/8/29")
def page_5():
    # 渲染模板 '2024_8_29.html' 并返回其内容
    return render_template("2024_8_29.html")
