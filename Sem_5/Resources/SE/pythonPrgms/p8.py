import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 8. Display Student Result
def display_student_result(marks):
    # Using match-case
    result = sum(marks) / len(marks)
    match result:
        case result if result >= 90:
            result = "I-Division"
        case result if 80 <= result < 90:
            result = "II-Division"
        case result if 70 <= result < 80:
            result = "III-Division"
        case _:
            result = "Fail" 

    return f"Total Marks = {sum(marks)}\nResult = {result}"

rc.print(Panel(display_student_result([95, 85, 86, 92, 91]), title="[green]Assignment-8[/green]"))

while True:
    try:
        marks = list(map(int, input("Enter marks: ").split()))
        print(display_student_result(marks))
    except ValueError:
        print("Please enter a valid number!")
        continue