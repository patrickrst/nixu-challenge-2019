## Bad memories - part 2

**Categories:** forensics, 2019
**Points:** 100
**Description:**

>  The lead graphical designer at ACME has noticed some kind of strange
>  activity on her computer. Their IT support believes it is a false
>  positive and the computer will fix itself after turning it off and 
>  on again. However, the user managed to take a memory dump just before
>  the crash. She mentioned something about lost files before the call audio
>  got all garbled.
>  
>  
>  
>  This is part 2 of 5 in a
>  memory dump analysis challenge.
>  The memory dump file can be found from the first part.


## Write-up

In this part of the forensics challenge, we need to look for a lost file.
To do this we need to search for files present in the main memory dump and more importantly files that have been deleted or moved to the recycle bin.
There are multiple commands available in volatility to search for files such as `filescan`, `dumpfiles` and `mftparser` [@volatility_files].
We had success with `mftparser`.
Using the following command `mftparser --dump-dir=output --output-file=badmem_mft.body --output=body`, we get a list of extracted files in `badmem_mft.body` and the extracted files in the `output` folder.
Knowing we are looking for a lost file, we search for the recycle bin like this`cat badmem_mft.body | grep -i "recycle"` which gives us about 10 results.
We try after to display the files in the output and we finally find one that is interesting (`cat output/file.0x286f8400.data0.dmp`).
This content is Base64 encoded which once converted becomes a string of 0 and 1 that can be converted to an ASCII string that is the flag.

