import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()


# 15. Check if Two Files Have the Same Contents
def are_files_equal(file1, file2):
    try:
        return f"Files are equal: {filecmp.cmp(file1, file2)}"
    except:
        return f'404: File Not Found'

# print("Assignment 15")
rc.print(Panel(are_files_equal('cmp1.txt', 'cmp2.txt'), title="[green]Assignment-15[/green]"))