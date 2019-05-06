#!/usr/bin/env python3

FILENAME = 'bin'

hexdata = ''

with open(FILENAME, 'rb') as f:
    hexdata = f.read().hex()

beg = 0
while True:
    pos = hexdata.find('0a', beg)
    first = hexdata[pos+2:pos+4]
    if first == '00':
        beg = pos+2
        continue
    beg = pos+2
    pos = hexdata.find('0a', beg)
    second = hexdata[pos+2:pos+4]
    #print(first)
    #print(second)
    first = int(first, 16)
    second = int(second, 16)
    ans = second - first
    #print(ans)
    ans = str(chr(ans))
    print(ans, end='')
    if ans == '}':
        break
    beg = pos+2
