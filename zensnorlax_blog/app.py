from flask import Flask, render_template, abort
from models import Post, db
import json
import os
from sqlalchemy import func

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///database.db"
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False
db.init_app(app)


def initialize_database():
    """
    初始化数据库并导入测试数据。
    """
    with app.app_context():
        db.create_all()
        import_posts_from_json("posts.json")


def import_posts_from_json(filepath):
    """
    从 JSON 文件导入文章数据到数据库。
    :param filepath: JSON 文件路径
    """
    with open(filepath) as f:
        posts = json.load(f)

    for post in posts:
        add_post_to_db(post)

    db.session.commit()


def add_post_to_db(post_data):
    """
    将单篇文章数据添加到数据库中。
    :param post_data: 单篇文章数据字典
    """
    if not Post.query.filter_by(title=post_data["title"]).first():
        new_post = Post(
            title=post_data["title"],
            content_path=post_data["content_path"],
            date_created=post_data.get("date_created"),  # 确保传递数据时赋值,
        )
        db.session.add(new_post)


# 初始化数据库
initialize_database()


@app.route("/")
def index():
    posts = Post.query.all()
    return render_template("index.html", posts=posts)


@app.route("/archives")
def archives():
    grouped_posts = (
        db.session.query(Post.year, Post.month, func.count(Post.id).label("count"))
        .group_by(Post.year, Post.month)
        .order_by(Post.year.desc(), Post.month.desc())
        .all()
    )
    return render_template("archives.html", posts=grouped_posts)


@app.route("/post/<int:post_id>")
def post(post_id):
    """
    根据文章ID返回对应的内容页面。
    :param post_id: 文章ID
    """

    # 获取最近的 5 篇文章
    recent_posts = (
        db.session.query(Post).order_by(Post.date_created.desc()).limit(5).all()
    )
    post = Post.query.get_or_404(post_id, description="Post not found")
    content = get_post_content(post.content_path)
    return render_template("post.html", posts=recent_posts, post=post, content=content)


# 路由：显示特定年份和月份的文章
@app.route("/archives/<int:year>/<int:month>")
def archive_posts(year, month):
    posts = Post.query.filter_by(year=year, month=month).all()
    return render_template("archive_posts.html", posts=posts, year=year, month=month)


def get_post_content(content_path):
    """
    获取文章内容。
    :param content_path: 文章内容文件路径
    :return: 文章内容字符串
    """
    full_path = os.path.join("instance", content_path)
    try:
        with open(full_path) as f:
            return f.read()
    except FileNotFoundError:
        abort(404, description="Content file not found")
