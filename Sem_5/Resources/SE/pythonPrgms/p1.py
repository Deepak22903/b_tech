import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 1. Find Profit or Loss
def calculate_profit_or_loss(cost_price, selling_price):
    if cost_price < selling_price:
        return f"Cost Price = {cost_price} \nSelling Price = {selling_price}\nProfit"
    elif cost_price > selling_price:
        return f"Cost Price = {cost_price} \nSelling Price = {selling_price}\nLoss"
    else:
        return f"Cost Price = {cost_price} \nSelling Price = {selling_price}\nNo Profit No Loss"
       
# print("Assignment 1")
rc.print(Panel(calculate_profit_or_loss(500, 50), title="[green]Assignment-1[/green]"))
rc.print(Panel(calculate_profit_or_loss(500, 55555), title="[green]Assignment-1[/green]"))
rc.print(Panel(calculate_profit_or_loss(500, 500), title="[green]Assignment-1[/green]"))

while True:
    sp=int(input("Enter Selling Price: "))
    cp=int(input("Enter Cost Price: "))
    rc.print(Panel(calculate_profit_or_loss(cp, sp), title="[green]Assignment-1[/green]"))