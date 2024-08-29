from models import db, Post
from app import app

with app.app_context():
    db.create_all()

    # Example: Adding a sample post
    if not Post.query.first():
        sample_post = Post(
            title="First Post", content="This is the content of the first post."
        )
        db.session.add(sample_post)
        db.session.commit()
