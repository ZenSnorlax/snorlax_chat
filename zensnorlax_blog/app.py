from flask import Flask, render_template_string

app = Flask(__name__)

# 假设这些页面信息从数据库或配置文件中读取
pages = [
    {"name": "home", "url": "/", "content": "Welcome to the home page!"},
    {"name": "about", "url": "/about", "content": "This is the about page."},
    {"name": "contact", "url": "/contact", "content": "Contact us here."},
]

# 动态生成路由
for page in pages:

    def make_route(content):
        def route():
            return render_template_string("<h1>{{ content }}</h1>", content=content)

        return route

    app.add_url_rule(page["url"], page["name"], make_route(page["content"]))

