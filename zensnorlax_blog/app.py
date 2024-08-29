from flask import Flask

app = Flask(__name__)


@app.route("/")
def index():
    return "Hello World"


@app.route("/archives")
def archives():
    return "archives"


@app.route("/2024/8/index")
def index():
    return "index"


@app.route("/2024/8/test")
def inde():
    return "index"
