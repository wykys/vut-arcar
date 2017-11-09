#!/usr/bin/python3
# wykys 9.11.2017
# script that finds in bom.csv url of distributors and
# creates *.csv for individual distributors

url = '../bom/'
boom_file = 'arcar.csv'

fr = open(url + boom_file, 'r')
bom = fr.readlines()
fr.close()

def find_shops():
    states = ('cz', 'en', 'us')
    shops = set()
    for s in bom:
        if 'www.' in s:
            s = s[s.find('www.') + 4:]
        elif 'http://' in s:
            s = s[s.find('http://') + 7:]
        elif 'https://' in s:
            s = s[s.find('https://') + 8:]
        else:
            continue
        s = s.split('.')
        s = s[1] if s[0] in states else s[0]
        shops.add(s)
    return tuple(shops)

shops_name = find_shops()
shops = []
print('FIND SHOPS:')
for i in shops_name:
    print('\t\t-', i)
    shops.append([])

for s in range(len(bom)):
    for i in range(len(shops_name)):
        if not s or shops_name[i] in bom[s]:
            shops[i].append(bom[s])

for i in range(len(shops_name)):
    fw = open(url + shops_name[i] + '.csv', 'w')
    fw.writelines(shops[i])
    fw.close()
