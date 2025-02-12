# https://en.wikipedia.org/wiki/2020_Summer_Olympics_medal_table

import requests
from bs4 import BeautifulSoup
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

url = 'https://en.wikipedia.org/wiki/2020_Summer_Olympics_medal_table'
html_content = requests.get(url).text
soup = BeautifulSoup(html_content, "lxml")

gdp_table = soup.find("table", attrs={"class": "wikitable sortable plainrowheaders jquery-tablesorter"})
gdp_table_data = gdp_table.tbody.find_all("tr")  # contains 2 rows

headings = []
for td in gdp_table_data[0].find_all("th"):
    # remove any newlines and extra spaces from left and right
    headings.append(td.text.replace('\n', ' ').strip())

print(headings)

data = []

for i in range(1, len(gdp_table_data)):
    tds = gdp_table_data[i].find_all("td")
    fds = gdp_table_data[i].find_all("a")
    try:
        fds=fds[0].text
    except:
        break

    values = [td.text.replace('\n', ' ').strip() for td in tds]
    values.insert(1,fds)
    data.append(values)

# print(data)
    
df = pd.DataFrame(data, columns=headings)

df['Rank'] = pd.to_numeric(df['Rank'])
df['Gold'] = pd.to_numeric(df['Gold'])
df['Silver'] = pd.to_numeric(df['Silver'])
df['Bronze'] = pd.to_numeric(df['Bronze'])
df['Total'] = pd.to_numeric(df['Total'])
df['NOC'] = df['NOC'].astype(str)

print(df.head())

