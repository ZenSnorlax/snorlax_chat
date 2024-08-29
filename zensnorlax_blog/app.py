from flask import Flask, render_template
from models import db, init_db, add_post, get_recent_posts, get_archives, get_post_by_id

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///database.db"
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

# 初始化数据库
init_db(app)


@app.route("/")
def index():
    recent_posts = get_recent_posts()
    archives = get_archives()
    return render_template("index.html", recent_posts=recent_posts, archives=archives)


@app.route("/post/<int:post_id>")
def post(post_id):
    post = get_post_by_id(post_id)
    if post:
        recent_posts = get_recent_posts()
        archives = get_archives()
        return render_template(
            "post.html", post=post, recent_posts=recent_posts, archives=archives
        )
    else:
        return "Post not found", 404


@app.route("/archives")
def archives():
    recent_posts = get_recent_posts()
    archives = get_archives()
    return render_template(
        "archives.html", recent_posts=recent_posts, archives=archives
    )


if __name__ == "__main__":
    app.run(debug=True)
