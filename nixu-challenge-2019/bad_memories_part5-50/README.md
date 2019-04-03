## Bad memories - part 5

**Categories:** forensics, 2019
**Points:** 50
**Description:**

>  The lead graphical designer at ACME has noticed some kind of strange
>  activity on her computer. Their IT support believes it is a false
>  positive and the computer will fix itself after turning it off and 
>  on again. During the earlier investigation, it turned out that our
>  user has forgotten her password. She only remembers it was very strong.
>  
>  
>  This is part 5 of 5 in a
>  memory dump analysis challenge.
>  The memory dump file can be found from the first part.


## Write-up

In this part, the goal is to recover the user password from the system. We started with the `hashdump` command.

```
volatility -f mem.dmp --profile=Win7SP1x64 hashdump
```

We get a list of the users and the NTLM hash of their password. We tried to reverse find the hash on a few online websites, but with no success. So, we try this second command `lsadump`, which extracts secret keys from the registry, such as the default password for Windows.

```
volatility -f mem.dmp --profile=Win7SP1x64 lsadump
```

Indeed, in the default password key we can find the challenge flag.

```
NIXU{was_it_even_hard_for_you?}
```
