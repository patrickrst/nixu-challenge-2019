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

Indeed, in the default password key we can find the challenge flag `NIXU{was_it_even_hard_for_you?}`.

### Analysis

The Bad memories series of challenges is about forensics and memory dump analysis. This is a common category in capture the flag competitions where the goal is to extract flags from a main memory dump (the RAM content) of an operating system. It also relates to real-world situations such as data recovery and digital/computer forensics. The same skill set applies for both cases, except that for forensics, it is not only sufficient to recover the information, but also to find evidence with metadata in order to present facts for legal reasons. From a memory dump, there is a lot of information that can be retrieved like running processes, active network connections, files that are being edited, usernames, passwords, etc. and also more data from sources such as the Windows registry or any databases. The skill set is also important in the field of computer security where memory analysis, for example, might be necessary to understand the nature of a more advanced attack where the attacker tries to hide their trail, somewhat similarly to the challenge where the memory dump was taken just before the computer crashed under mysterious circumstances. Encryption at different levels can be a way to hinder the process of memory dump analysis, but this was not part of the challenges.

