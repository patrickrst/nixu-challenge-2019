## Bad memories - part 1

**Categories:** forensics, 2019
**Points:** 50
**Description:**

>  The lead graphical designer at ACME has noticed some kind of strange
>  activity on her computer. Their IT support believes it is a false
>  positive and the computer will fix itself after turning it off and 
>  on again. However, the user managed to take a memory dump just before
>  the crash. Could you help us recover the documentation she was working on?
>  
>  
>  This is part 1 of 5 in a memory dump analysis challenge found in
>  mem.7z.  The parts are numbered loosely according to the 
>  difficulty level. (If something doesn't work, just try elsewhere.)
>  


## Write-up

This is the first part of a five parts challenge on forensics, where it is needed to recover information from a memory dump. 
To analyse the memory dump, we use the Python tool `Volatility Framework` and its many commands [@volatility_commands].

The first step is to find what type of operating system was the memory capture was done on, which we can find with the command `imageinfo`.

```
volatility -f mem.dmp imageinfo
```

We find that the memory dump is from a Windows 7 operating system. From there, we can list the processes that were active during the captutre with either `pslist` or `pstree`.

```
volatility -f mem.dmp --profile=Win7SP1x64 pslist
```

The first part tells to recover the user documentation, which would hints at a text editor. There is a `notepad.exe` process running with PID 700, so we dump the VADs (Virtual Address Descriptors) and look at the VAD tree to find memory regions of heap (in yellow).

```
volatility -f mem.dmp --profile=Win7SP1x64 vaddump -p 700 -D ./vads/
volatility -f mem.dmp --profile=Win7SP1x64 vadtree --output=dot --output-file=./vads/graph.dot -p 700
```

To do that, we can use `strings` to find text in the heap memory.

```
strings -e l vads/notepad.exe.8c45060.0x0000000000390000-0x000000000048ffff.dmp 
```

After looking throught a few files, we can find the flag in ROT13 `AVKH{guvf_j4f_gu3_rnfl_bar}`, which results in a valid flag `NIXU{this_w4s_th3_easy_one}`.

