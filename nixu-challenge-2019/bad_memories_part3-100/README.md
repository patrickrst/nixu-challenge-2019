## Bad memories - part 3

**Categories:** forensics, 2019
**Points:** 100
**Description:**

>  The lead graphical designer at ACME has noticed some kind of strange
>  activity on her computer. Their IT support believes it is a false
>  positive and the computer will fix itself after turning it off and 
>  on again. However, the user managed to take a memory dump just before
>  the crash. Could you help us recover the new design she was working on?
>  
>  
>  This is part 3 of 5 in a
>  memory dump analysis challenge.
>  The memory dump file can be found from the first part.


## Write-up

This time, the information that needs to be recovered from the memory dump is the "new design" that the user was working on.
This hints us to search for a graphic image.
Using `pslist`, we can confirm that a `mspaint` program was running on the machine.
Using `cmdscan` and `console`, we can see there exist a `flag.bmp` file in the system of the user, but we were unable to extract it from the memory dump.
Therefore, we do a `memdump` of the Paint process and look into that.

```
volatility -f mem.dmp --profile=Win7SP1x64 memdump -p 2816 -D ./dump/
```

We rename the extension from `.dmp` to `.data` to be able to use GIMP to view the raw data.
Doing this, we are able to move along the process memory and search visually for an image [@volatility_paint].
After a lot of trial and error and looking at random bits of data, we were able to find a few images that made sense, such as the desktop of the user and an image containing the flag `NIXU{c4n_you_3nhanc3_this}`.

