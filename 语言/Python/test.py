from pathlib import Path
import json


def get_stored_number(path):
    if path.exists():
        contents = path.read_text()
        favorite_number = json.loads(contents)
        return favorite_number
    else:
        return None


def get_new_number(path):
    favorite = input("what's your favorite number? ")
    contents = json.dumps(favorite)
    path.write_text(contents)
    return contents


def greet_user():
    path = Path('favorite_number.json')
    favarote_number = get_stored_number(path)
    if favarote_number:
        print(f"welcome!\n\tyour favarite number is : {favarote_number}")
    else:
        favarote_number = get_new_number(path)
        print(f"we'll rember your favorite number when you back")


greet_user()
