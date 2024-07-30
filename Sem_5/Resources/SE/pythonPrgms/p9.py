import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 9. Check and Write to a File
def check_and_write_to_file(filename):
    if os.path.exists(filename):
        with open(filename, 'a') as file:
            file.write("hello world\n")
    else:
        with open(filename, 'w') as file:
            file.write("hello world\n")

def display_file_contents(filename):
    string=""
    if os.path.exists(filename):
        with open(filename, 'r') as file:
            for line in file:
                string += line
    else:
        return f"File '{filename}' does not exist."
    return string

# print("Assignment 9")
check_and_write_to_file('test_file.txt')
rc.print(Panel(display_file_contents('test_file.txt'), title="[green]Assignment-9[/green]"))
