import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()


# 13. Check if a String is Palindrome
def is_palindrome(string):
    string = string.lower().replace(" ", "")
    if string == string[::-1]:
        return f"String = {string}\nPalindrome"
    else:
        return f"String = {string}\nNot Palindrome"
    
# print("Assignment 13")
rc.print(Panel(is_palindrome('aba')+"\n"+is_palindrome('abasd'), title="[green]Assignment-13[/green]"))

while True:
    string=input("Enter String: ")
    print(is_palindrome(string))