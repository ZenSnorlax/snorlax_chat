from selenium import webdriver
from selenium.webdriver.chrome.service import Service as ChromeService
from selenium.webdriver.chrome.options import Options as ChromeOptions
import time

# 配置Chrome选项
chrome_options = ChromeOptions()
chrome_options.add_argument("--disable-gpu")
chrome_options.add_argument("--no-sandbox")
chrome_options.add_argument(
    "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/127.0.0.0 Safari/537.36"
)

# 设置ChromeDriver路径
webdriver_service = ChromeService("/usr/bin/chromedriver")

# 启动Chrome浏览器
driver = webdriver.Chrome(service=webdriver_service, options=chrome_options)


def add_cookies(driver, cookies):
    """
    将cookie字符串转换为字典并添加到浏览器中
    """
    for cookie in cookies.split("; "):
        name, value = cookie.split("=", 1)
        driver.add_cookie({"name": name, "value": value})


try:
    # 初始访问页面
    driver.get("https://www.zhihu.com")

    # 添加初始的cookie
    initial_cookies = '_xsrf=zb8Pw7zI2qj5JIIjs2F5WybliDlDkNc7; _zap=20f21498-0c31-4955-a38f-00177fed2b4d; d_c0=AADSX8uZzRiPThaNqMgD4mFUnueLmKzLmlo=|1718894493; __zse_ck=001_qBD8xd4VuBymZ6xBNcbf7Rd9B586LhZs+4Mlz/O9zV59OfcEYdvxX6Mqe3cHoU/fZaCCXC=84OTLeJEj47aVsFK0u/7mRD5+1=mbPTSt/Z+AYrlEFqQca5=LODU4CIdl; __snaker__id=v6D6dZPklLbUmW7E; q_c1=a9fc6a59949b460f8973dcf975b1a805|1724250803000|1724250803000; l_cap_id="MzkzN2JhMWJlNTZiNDQ2ZmE2YjI5OTU0NGNhMjg4NTU=|1724251324|781410e947bbf127f796ec99a73bd3fe8dc649fb"; r_cap_id="ZDliMjc1MWI4MDY3NDE4ZmFiNmMzY2Q0Yjc2ZTUxYjc=|1724251324|6070bdccb7298f4a1dc01ee8c811db254b7d06d5"; cap_id="NTMzZGQwNjNjYzJiNDZlMzhlNGVlMjcxYzUxMzNmNjk=|1724251324|ddcb1c85bfd043a040c01e854be5aea77846670c"; gdxidpyhxdE=wpsdhS14O55tBklzVBvXvR2yjRVY%5CASvZnZ3O9Kp9b3zC%5Ckqf6QN%5CKiHYJ9skcdVM%2Bn1C6NkcqA8gP5JezvxYYspV05ibyc5VBOwNYekQ6%2F67bPyXZBZf91s%5CoQ%2Fj1nafoGH9u%2Fptzx%5CUN64oWKefPWYijkPyZWsX%2Ftm%2BiBUaCxHGGmv%3A1724253725477; captcha_ticket_v2=2|1:0|10:1724252975|17:captcha_ticket_v2|728:eyJ2YWxpZGF0ZSI6Ik5BTlBfZVN0QzZfU01fRTVtUXpKUjA2cU4udDIubTl2bjg1WlpBVTJ5WDY4dDN5Y1ZFcXQyVmhWUERxcTBxOXI4bUgxTmhyMmlFNDIxcldvUmZ0RGZ6cTJvcThCaVNqbC5yWXJxdjg4SDUzYldBS28qYmlZRipldkpBYk9YYVVpanhxLk1hSHMwSU1JQ3hKNTZfQWZ5YW5NQzNvTGFfbFBzaTY0MmtiVHZCbk9EWlRDMnhjSi5LQld0M2dHNkMyOWs1Mk5oWGtIUGtydFdNT0tLa01yY2JNa0NvOVZuWW54Z2FiMnBXWklqRGpzZE9WZThxOG82SlRxZU1fNjNPeUhsbVduMGJFbXhpMkVJOWduOEtVZUdZZmhScUtLNEoxWWQ0a3NmSUMuQjAxWjA2OF8qdnFwS1JBUGJBT05pZWdzc1JLeUJPMmw2bk92MU5Pei5jWDNucFpOdktnZUNPSXJzM1dWYzhsS1B1ZmNISVNmODRsY1lrSCo4OTNqdXEqRjJ2QTRZOF96T1paQ1Nnd1h2bUg4a0NweFF0TjlsQU56Uyp4SXdMNVlKQ2wuU0VDRypMMG5oVHFpOS5WM1hQSjNEYXVDQzFwZHh1QzNieElQVjlycEZmalBsWDEyOUNjMSpsaE1iT2VCV1F5ajBNKjNTMHpXMjVDbHNpR0UxYmVPTDFEa2RVTFZIdlk3N192X2lfMSJ9|bc2684daba8c726ed92a947eb5ff8f88a41d5b9477a723c796ceb2bb17cc69c4; captcha_session_v2=2|1:0|10:1724252977|18:captcha_session_v2|88:WktQbGRiU3J4blk2TWNOOGVKMDhmalVmV1M0OENFcmlLTmNsQVYvUHkxRlA3R0RobmRaNGpIajEvdnBqZ1BPRw==|11c3642f488c62a72f4f07d9bdddde9d53b9f74184ae7ef948390a2521353848; z_c0=2|1:0|10:1724285914|4:z_c0|92:Mi4xY1hMYlBBQUFBQUFBQU5KZnk1bk5HQmNBQUFCZ0FsVk5BMUt6WndDTk9BTkJ4M3REdm4tVHBRaVVxNHdGaUVmSWt3|aae933ae35063b6db20476a4cc3f5ea7ee26dd7a0a5596773702b26d9cf973d2; BEC=b7b0f394f3fd074c6bdd2ebbdd598b4e; SESSIONID=wgYBLJ4zRvItEW9SgRsFSI90wJKVmE5ZH3r9HceeBNN; tst=r'  # 初始cookies省略
    add_cookies(driver, initial_cookies)
    time.sleep(1)  # 等待页面加载

    # 访问目标页面
    driver.get("https://www.zhihu.com/host")

    # 添加目标页面的cookie
    additional_cookies = '_xsrf=zb8Pw7zI2qj5JIIjs2F5WybliDlDkNc7; _zap=20f21498-0c31-4955-a38f-00177fed2b4d; d_c0=AADSX8uZzRiPThaNqMgD4mFUnueLmKzLmlo=|1718894493; __zse_ck=001_qBD8xd4VuBymZ6xBNcbf7Rd9B586LhZs+4Mlz/O9zV59OfcEYdvxX6Mqe3cHoU/fZaCCXC=84OTLeJEj47aVsFK0u/7mRD5+1=mbPTSt/Z+AYrlEFqQca5=LODU4CIdl; __snaker__id=v6D6dZPklLbUmW7E; q_c1=a9fc6a59949b460f8973dcf975b1a805|1724250803000|1724250803000; l_cap_id="MzkzN2JhMWJlNTZiNDQ2ZmE2YjI5OTU0NGNhMjg4NTU=|1724251324|781410e947bbf127f796ec99a73bd3fe8dc649fb"; r_cap_id="ZDliMjc1MWI4MDY3NDE4ZmFiNmMzY2Q0Yjc2ZTUxYjc=|1724251324|6070bdccb7298f4a1dc01ee8c811db254b7d06d5"; cap_id="NTMzZGQwNjNjYzJiNDZlMzhlNGVlMjcxYzUxMzNmNjk=|1724251324|ddcb1c85bfd043a040c01e854be5aea77846670c"; gdxidpyhxdE=wpsdhS14O55tBklzVBvXvR2yjRVY%5CASvZnZ3O9Kp9b3zC%5Ckqf6QN%5CKiHYJ9skcdVM%2Bn1C6NkcqA8gP5JezvxYYspV05ibyc5VBOwNYekQ6%2F67bPyXZBZf91s%5CoQ%2Fj1nafoGH9u%2Fptzx%5CUN64oWKefPWYijkPyZWsX%2Ftm%2BiBUaCxHGGmv%3A1724253725477; captcha_ticket_v2=2|1:0|10:1724252975|17:captcha_ticket_v2|728:eyJ2YWxpZGF0ZSI6Ik5BTlBfZVN0QzZfU01fRTVtUXpKUjA2cU4udDIubTl2bjg1WlpBVTJ5WDY4dDN5Y1ZFcXQyVmhWUERxcTBxOXI4bUgxTmhyMmlFNDIxcldvUmZ0RGZ6cTJvcThCaVNqbC5yWXJxdjg4SDUzYldBS28qYmlZRipldkpBYk9YYVVpanhxLk1hSHMwSU1JQ3hKNTZfQWZ5YW5NQzNvTGFfbFBzaTY0MmtiVHZCbk9EWlRDMnhjSi5LQld0M2dHNkMyOWs1Mk5oWGtIUGtydFdNT0tLa01yY2JNa0NvOVZuWW54Z2FiMnBXWklqRGpzZE9WZThxOG82SlRxZU1fNjNPeUhsbVduMGJFbXhpMkVJOWduOEtVZUdZZmhScUtLNEoxWWQ0a3NmSUMuQjAxWjA2OF8qdnFwS1JBUGJBT05pZWdzc1JLeUJPMmw2bk92MU5Pei5jWDNucFpOdktnZUNPSXJzM1dWYzhsS1B1ZmNISVNmODRsY1lrSCo4OTNqdXEqRjJ2QTRZOF96T1paQ1Nnd1h2bUg4a0NweFF0TjlsQU56Uyp4SXdMNVlKQ2wuU0VDRypMMG5oVHFpOS5WM1hQSjNEYXVDQzFwZHh1QzNieElQVjlycEZmalBsWDEyOUNjMSpsaE1iT2VCV1F5ajBNKjNTMHpXMjVDbHNpR0UxYmVPTDFEa2RVTFZIdlk3N192X2lfMSJ9|bc2684daba8c726ed92a947eb5ff8f88a41d5b9477a723c796ceb2bb17cc69c4; captcha_session_v2=2|1:0|10:1724252977|18:captcha_session_v2|88:WktQbGRiU3J4blk2TWNOOGVKMDhmalVmV1M0OENFcmlLTmNsQVYvUHkxRlA3R0RobmRaNGpIajEvdnBqZ1BPRw==|11c3642f488c62a72f4f07d9bdddde9d53b9f74184ae7ef948390a2521353848; z_c0=2|1:0|10:1724285914|4:z_c0|92:Mi4xY1hMYlBBQUFBQUFBQU5KZnk1bk5HQmNBQUFCZ0FsVk5BMUt6WndDTk9BTkJ4M3REdm4tVHBRaVVxNHdGaUVmSWt3|aae933ae35063b6db20476a4cc3f5ea7ee26dd7a0a5596773702b26d9cf973d2; tst=h; BEC=32377ec81629ec05d48c98f32428ae46; SESSIONID=x3ET3hZ6nhcVNuvWs89SMkq7VWW5IhLMSMCL4pf6h5J'  # 目标页面cookies省略
    add_cookies(driver, additional_cookies)
    time.sleep(1)  # 等待页面加载

    # 获取页面的HTML内容并保存
    html = driver.page_source
    with open("test.html", "w") as f:
        f.write(html)

finally:
    # 关闭浏览器
    driver.quit()
