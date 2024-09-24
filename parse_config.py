import json
import subprocess
import os

with open('config.json', 'r') as f:
    config = json.load(f)

mysql_user = config['mysql']['username']
mysql_password = config['mysql']['password']
mysql_database = config['mysql']['database']

subprocess.run([
    'mysql',
    '-u', mysql_user,
    '-p' + mysql_password,
    '-e', f'CREATE DATABASE IF NOT EXISTS {mysql_database}'
])


sql_files = ['sql/user.sql', 'sql/message.sql']

for sql_file in sql_files:
    subprocess.run([
        'mysql',
        '-u', mysql_user,
        '-p' + mysql_password,
        mysql_database,
        '-e', f'source {sql_file}'
    ])

print(config['mysql']['username'])
print(config['mysql']['password'])
print(config['mysql']['database'])
