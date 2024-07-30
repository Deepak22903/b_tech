import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()


# 17. Modify and Display a File Using grep
def modify_and_display_file(filename):
    f = open("filename", 'w')
    # Random Names Of Cities
    s= """
    Mumbai
    Delhi
    Bangalore
    Hyderabad
    Ahmedabad
    Chennai
    Kolkata
    """.split()

    s = [line for line in s if "a" not in line]
    f.writelines('\n'.join(s))
    f.close()

    f = open("filename", 'r')
    string = ""
    for line in f:
        string += line
    f.close()
    return string

# print("Assignment 17")
rc.print(Panel(modify_and_display_file('test_file.txt'), title="[green]Assignment-17[/green]"))

