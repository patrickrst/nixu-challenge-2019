#!/usr/bin/env python3

import os
import requests
from lxml import html

CTF = 'nixu-challenge-2019'
URL = 'https://thenixuchallenge.com/c/'

page = requests.get(URL)
tree = html.fromstring(page.content)

links = tree.xpath('/html/body/div[2]/div/a/@href')
names = tree.xpath('/html/body/div[2]/div/a/p[1]/text()')
points = tree.xpath('/html/body/div[2]/div/a/div/div/text()[1]')
tags = []

for p in tree.xpath('/html/body/div[2]/div/a/div/p'):
    tags.append(p.xpath('./span/text()'))

print('---')
print('Found {} challenges.'.format(len(links)))
print('---')

try:
    os.makedirs(CTF)
except FileExistsError:
    pass

for link,point,name,tag in zip(links,points,names,tags):
    link = link[3:].strip('/')
    point = point.strip().strip(' pts /')
    filename = '{}-{}'.format(link, point)
    try:
        os.makedirs(CTF + '/' + filename)
    except FileExistsError:
        pass

    page = requests.get(URL + link)
    tree = html.fromstring(page.content)

    description = tree.xpath('/html/body/div[2]/p/text()')
    desc = ''.join(tree.body[5][0].itertext())
    desc2 = ''
    for line in desc.split('\n'):
        desc2 += '>  ' + line + '\n'

    readme = ('## {}\n\n' +
              '**Categories:** {}\n' +
              '**Points:** {}\n' +
              '**Description:**\n\n' + 
              '{}\n\n' +
              '## Write-up\n\n' +
              'blabla\n\n' +
              '').format(name, ', '.join(tag), point, desc2)

    with open(CTF + '/' + filename + '/README.md', 'w') as out:
        out.write(readme)
