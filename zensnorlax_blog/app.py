from flask import Flask, render_template
from models import db, Post

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///database.db"
db.init_app(app)


@app.route("/")
def index():
    posts = Post.query.order_by(Post.date.desc()).all()
    return render_template("index.html", posts=posts)


@app.route("/archives")
def archives():
    posts = Post.query.order_by(Post.date.desc()).all()
    return render_template("archives.html", posts=posts)


@app.route("/post/<int:post_id>")
def post(post_id):
    post = Post.query.get_or_404(post_id)
    return render_template("post.html", post=post)


if __name__ == "__main__":
    app.run(debug=True)
