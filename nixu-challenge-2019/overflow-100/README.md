## Device Control Pwnel

**Categories:** 2019, pwnable
**Points:** 100
**Description:**

>  You found an exposed device controller interface...
>  
>  nc overflow.thenixuchallenge.com 20191
>  
>  device.tgz
>  


## Write-up

There are two buffer overflow vulnerabilities in this challenge which is divided in two parts. The first part is a simple buffer overflow, where the program uses the secure function `fgets`, but with a value of 127 for the maximum number of characters to read. The characters are stored in an array of 8 bytes, which allows us to overflow and write the value of the local variable `int id` to zero, which gives access the admin menu and the first flag.

```python
python -c 'print("ABCDEFGH\00\00\00\00\n8")' | nc overflow.thenixuchallenge.com 20191
```

```
NIXU{pr3tty_s1mpl3_0v3rfl0w}
```
