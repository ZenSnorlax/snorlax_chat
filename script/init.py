import subprocess

# define the MySQL connection details
user = 'abs'
password = '1510017673'
database = 'snorlax_chat'
sql_file = 'setup.sql'

# construct the command
command = f'mysql -u {user} -p{password} {database} < {sql_file}'

try:
    subprocess.run(command, shell=True, check=True)
    print("SQL file executed successfully.")
except subprocess.CalledProcessError as e:
    print(f"Error executing SQL file: {e}")
