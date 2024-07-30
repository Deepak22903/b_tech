import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 11. Read and Display File Contents Line by Line
def read_and_display_file(filename):
    string=""
    if os.path.exists(filename):
        with open(filename, 'r') as file:
            for line in file:
                string += line
    else:
        return f"File '{filename}' does not exist."
    return string

# print("Assignment 11")
rc.print(Panel(read_and_display_file('test_file.txt'), title="[green]Assignment-11[/green]"))

