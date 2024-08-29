from flask import Flask

app = Flask(__name__)


@app.route("/")
def index():
    return "Hello World"


@app.route("/archives")
def archives():
    return "archives"


@app.route("/<year>/<month>/<post>")
def article(year, month, post):
    return "year: %s, month: %s, article: %s" % (year, month, post)

