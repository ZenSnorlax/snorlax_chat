from flask import Flask

app = Flask(__name__)


@app.route("/")
def index():
    return "Hello World"


@app.route("/archives")
def archives():
    return "archives"


@app.route("/2024/8/hello")
def page_0():
    return "index"


@app.route("/2024/8/hekk")
def page_1():
    return "index"



@app.route("/2024/8/j")
def page_2():
    return "index"
