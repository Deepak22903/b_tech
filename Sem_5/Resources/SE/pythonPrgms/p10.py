import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 10. Create a Directory
def create_directory(directory_name):
    if not os.path.exists(directory_name):
        os.mkdir(directory_name)
        return f"Directory '{directory_name}' created successfully."
    else:
        return f"Directory '{directory_name}' already exists."

# print("Assignment 10")
rc.print(Panel(create_directory('test_dir'), title="[green]Assignment-10[/green]"))


