from flask import Flask, render_template
from models import db, Post

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///instance/database.db"
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

db.init_app(app)


@app.route("/")
def index():
    posts = Post.query.order_by(Post.created_at.desc()).all()
    recent_posts = posts[:5]  # 获取最近的5篇文章
    return render_template("index.html", posts=posts, recent_posts=recent_posts)


@app.route("/post/<int:post_id>")
def post(post_id):
    post = Post.query.get_or_404(post_id)
    return render_template("post.html", post=post)


@app.route("/archives")
def archives():
    posts = Post.query.order_by(Post.created_at.desc()).all()
    return render_template("archives.html", posts=posts)
