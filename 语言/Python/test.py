import urllib.request
import random
from bs4 import BeautifulSoup
import time


def request_html(url):

    headers={'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.90 Safari/537.36'}
    request = urllib.request.Request(url, headers=headers)
    return request

def parse_html(html, f):
    # 生成soup对象
    soup = BeautifulSoup(html, 'lxml')
    # 查找所有的章节链接和标题内容
    list_name = soup.select('.book-mulu > ul > li > a')
    # 遍历每一个列表中的tag对象，获取链接个目录
    for item in list_name:
        # 获取链接
        #item: <a href="/book/liangjinyanyi/1.html">自序</a>
        #拼接目录链接,此处item类型为<class 'bs4.element.Tag'>，使用下面方法可以值获取href属性值
        href = 'http://www.shicimingju.com' + item['href']
        # 获取标题
        title = item.text
        print('正在下载:-**--%s--**-......' % title)
        # 获取章节内容函数
        text = get_text(href)
        # 写入文件
        f.write(title + '\n' + text)
        print('结束下载:-**--%s--**-' % title)
        time.sleep(random.uniform(0,1))

# 提取章节内容
def get_text(href):
    #创建请求对象
    request = request_html(href)
    content = urllib.request.urlopen(request).read().decode('utf8')
    soup = BeautifulSoup(content, 'lxml')
    # 查找包含内容的tag--div
    artist = soup.find('div', class_='chapter_content')
    #获取tag标签中的文本内容
    return artist.text

def run():
    # 打开文件
    f = open('两晋演义.txt', 'w', encoding='utf8')
    url = 'http://www.shicimingju.com/book/liangjinyanyi.html'
    # 构建请求对象
    request = request_html(url)
    # 发送请求，得到响应，转换为HTML对象
    html = urllib.request.urlopen(request).read().decode('utf8')
    # 解析内容
    parse_html(html,f)
    #关闭文件
    f.close()

if __name__ == '__main__':
    run()

