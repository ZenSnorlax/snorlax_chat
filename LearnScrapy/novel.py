import re
import requests
from urllib3.util.retry import Retry
from requests.adapters import HTTPAdapter
from concurrent.futures import ThreadPoolExecutor, as_completed
from tqdm import tqdm
import os

# Define User-Agent
headers = {
    "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/127.0.0.0 Safari/537.36"
}


# Create a session with retry strategy
def create_session() -> requests.Session:
    session = requests.Session()
    retry = Retry(total=5, backoff_factor=2, status_forcelist=[500, 502, 503, 504])
    adapter = HTTPAdapter(max_retries=retry)
    session.mount("http://", adapter)
    session.mount("https://", adapter)
    return session


# Extract chapter URLs using regex
def extract_chapter_urls(book_url: str) -> list[str]:
    session = create_session()
    try:
        response = session.get(url=book_url, headers=headers)
        response.raise_for_status()
    except requests.RequestException as e:
        print(f"Failed to fetch book URL: {e}")
        return []

    content = response.content.decode("utf-8")
    with open("test.html", "w", encoding="utf-8") as f:
        f.write(content)

    pattern = r'<dd>\s*<a\s+href\s*=["\'](.*?)["\']\s*>.*?</a>\s*</dd>'
    #  pattern = r'.*'
    urls = re.findall(pattern, content)

    if not urls:
        print("未能提取到章节 URL!")
        return []

    return [f"https://bqgui.cc{url}" for url in urls]


# Fetch chapter content using regex
def fetch_chapter_content(chapter_url: str) -> str:
    session = create_session()
    try:
        response = session.get(url=chapter_url, headers=headers)
        response.raise_for_status()
    except requests.RequestException as e:
        print(f"Failed to fetch chapter URL: {e}")
        return ""

    content = response.content.decode("utf-8")
    pattern = re.compile(
        r'<div id="chaptercontent" class="Readarea ReadAjax_content">(.+?)\s*请收藏本站',
        re.S,
    )

    match = pattern.search(content)
    if match:
        chapter_content = match.group(1)
        chapter_content = re.sub(
            r"<br /><br />", "\n", chapter_content
        )  # Handle <br> tags
        return chapter_content
    else:
        print("No content found for URL: ", chapter_url)
        return ""


def save_chapters_as_txt(chapters_content: dict, output_folder: str):

    # Ensure the output folder exists
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    for index in tqdm(sorted(chapters_content.keys()), desc="Saving Chapters"):
        chapter_content = chapters_content[index]
        file_name = os.path.join(output_folder, f"Chapter_{index + 1}.txt")

        with open(file_name, "w", encoding="utf-8") as f:
            f.write(chapter_content + "\n\n")


def main():
    book_url = "https://www.bqgui.cc/book/636/"
    chapter_urls = extract_chapter_urls(book_url)

    if not chapter_urls:
        print("没有找到任何章节。")
        return

    chapters_content = {}  # Store all chapter contents

    # Download chapters with progress bar
    with ThreadPoolExecutor(max_workers=5) as executor:
        futures = {
            executor.submit(fetch_chapter_content, url): index
            for index, url in enumerate(chapter_urls)
        }

        for future in tqdm(
            as_completed(futures), total=len(futures), desc="Downloading Chapters"
        ):
            index = futures[future]
            content = future.result()
            if content:
                chapters_content[index] = content

    # Save chapters to individual TXT files
    output_folder = "chapters"
    save_chapters_as_txt(chapters_content, output_folder)
    print(f"章节文件已保存到文件夹 '{output_folder}'")


if __name__ == "__main__":
    main()
