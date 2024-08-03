import requests as r

from bs4 import BeautifulSoup

def get_grid(url):
    html = r.get(url)
    soup = BeautifulSoup(html.text)
    table = soup.table
    values = []
    trs = table.find_all('tr')
    trs = trs[1:]
    for row in trs:
        spans = row.find_all('span')
        rowVals = []
        for span in spans:
            rowVals.append(span.string)
        values.append(rowVals)

    maxX = 1
    maxY = 1

    for row in values:
        row[0] = int(row[0])
        row[2] = int(row[2])
        maxX = max(row[0], maxX)
        maxY = max(row[2], maxY)

    # create grid space
    grid = []

    for y in range(maxY+1):
        grid.append([" "] * (maxX+1))
    
    for row in values:
        x = row[0]
        y = maxY - row[2]
        v = row[1]
        grid[y][x] = v

    gridString = ""

    for row in grid:
        gridString += "".join(row) + "\n"

    print(gridString)

url = "https://docs.google.com/document/d/e/2PACX-1vSHesOf9hv2sPOntssYrEdubmMQm8lwjfwv6NPjjmIRYs_FOYXtqrYgjh85jBUebK9swPXh_a5TJ5Kl/pub"

get_grid(url)

    