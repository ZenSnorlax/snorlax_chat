from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

from datetime import datetime

class Post(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(80), nullable=False)
    content_path = db.Column(db.String(80), nullable=False)
    date_created = db.Column(db.String(80), nullable=False)
    year = db.Column(db.Integer, nullable=False)
    month = db.Column(db.Integer, nullable=False)

    def __init__(self, title, content_path, date_created=None):
        self.title = title
        self.content_path = content_path
        self.date_created = date_created or datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.year = int(self.date_created[:4])
        self.month = int(self.date_created[5:7])
