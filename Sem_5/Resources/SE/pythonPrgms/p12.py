import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 12. Check Leap Years
def find_leap_years(start_year, num_years):
    leap_years = []
    while num_years:
        if (start_year % 4 == 0 and start_year % 100 != 0) or (start_year % 400 == 0):
            leap_years.append(start_year)
            num_years -= 1 
        start_year += 1

    return f"Leap Years = {leap_years}"

# print("Assignment 12")
rc.print(Panel(find_leap_years(2000, 10), title="[green]Assignment-12[/green]"))

while True:
    try:
        start_year = int(input("Enter Start Year: "))
        num_years = int(input("Enter Number of Years: "))
        print(find_leap_years(start_year, num_years))
    except ValueError:
        print("Please enter a valid number!")
        continue