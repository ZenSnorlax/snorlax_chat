from flask import Flask

app = Flask(__name__)


@app.route("/")
def index():
    return "Hello World"


@app.route("/archives")
def archives():
    return "archives"

@app.route("/2024/8/你的敏感,就是你的天赋")
def page_4():
    return "index"
