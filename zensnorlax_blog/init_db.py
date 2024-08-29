# init_db.py
import sqlite3


def initialize_database():
    # 连接到数据库（如果不存在则创建）
    conn = sqlite3.connect("page_numbers.db")
    cursor = conn.cursor()

    # 创建表（如果不存在）
    cursor.execute(
        """
    CREATE TABLE IF NOT EXISTS page_info (
        id INTEGER PRIMARY KEY,
        page_number INTEGER
    )
    """
    )

    # 初始化page_number（仅第一次执行）
    cursor.execute("SELECT COUNT(*) FROM page_info")
    if cursor.fetchone()[0] == 0:
        cursor.execute("INSERT INTO page_info (page_number) VALUES (0)")

    conn.commit()
    conn.close()


if __name__ == "__main__":
    initialize_database()
