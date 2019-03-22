## Device Control Pwnel - part 2

**Categories:** 2019, pwnable
**Points:** 150
**Description:**

>  The Device Control Pwnel challenge
>  contains another flag; this is the place to turn it into points.
>  


## Write-up

This is the second part of the buffer overflow challenge using the same C source code. The idea is similar, 256 bytes of inputs are allowed while the description field in the struct is of size 128 bytes. The array is copied using the unsecure funtion `strcpy` which allows us to write over the field `id` of the device struct. The goal is to write the device master ID `0x8100ca33c1ab7daf` to a device to get the flag. The only problem is that the number contains a null byte `\x00` which is the character that will cause `strcpy` to stop copying. Therefore, we need to first create a new device with the first part of the ID `81` and after edit the same device to add the rest of the ID `00ca33c1ab7daf`.

```python
python -c 'print("2\n" + "name\n" + "A"*128+"1234567\x81\n" + "3\n1\n" + "name\n" + "A"*128+"\xaf\x7d\xab\xc1\x33\xca\x00\n" + "1\n4")' | ./devices
```

```
NIXU{h0w_t0_d3al_w1th_null_byt3s\x00}
```
