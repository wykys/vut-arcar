#!/usr/bin/python3

url = '../bom/'
boom_file = 'arcar.csv'
shops_name = ('tme', 'farnell')

shops = []
for i in shops_name:
    shops.append([])

fr = open(url + boom_file, 'r')
bom = fr.readlines()
fr.close()

for s in range(len(bom)):
    for i in range(len(shops_name)):
        if not s or shops_name[i] in bom[s]:
            shops[i].append(bom[s])

for i in range(len(shops_name)):
    fw = open(url + shops_name[i] + '.csv', 'w')
    fw.writelines(shops[i])
    fw.close()
