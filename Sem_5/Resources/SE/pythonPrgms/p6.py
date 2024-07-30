import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 6. Simple Calculator
def calculator(operand1, operator, operand2):
    if operator == '+':
        return f"{operand1} {operator} {operand2} = {operand1 + operand2}"
    elif operator == '-':
        return f"{operand1} {operator} {operand2} = {operand1 - operand2}"
    elif operator == '*':
        return f"{operand1} {operator} {operand2} = {operand1 * operand2}"
    elif operator == '/':
        if operand2 == 0:
            return f"{operand1} {operator} {operand2} = {operand1 / operand2}\nCannot divide by zero"
        return f"{operand1} {operator} {operand2} = {operand1 / operand2}"
    else:
        return f"Invalid Operator"
    
# print("Assignment 6")
rc.print(Panel(calculator(50,  '+', 60)+"\n"+calculator(50,  '-', 60)+"\n"+calculator(50,  '*', 60)+"\n"+calculator(500, '/', 60), title="[green]Assignment-6[/green]"))

while True:
    try:
        operand1 = int(input("Enter operand1: "))
        operator = input("Enter operator: ")
        operand2 = int(input("Enter operand2: "))
        print(calculator(operand1, operator, operand2))
    except ValueError:
        print("Please enter a valid number!")
        continue