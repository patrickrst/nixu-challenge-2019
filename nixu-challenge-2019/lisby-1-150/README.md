## lisby-1

**Categories:** reversing, 2019
**Points:** 150
**Description:**

>  On a slow day we were digging through our graveyard of long-forgotten
>  computers. These were from an era when a computer still meant a massive
>  construction with wires all over the place. And what did we find?! A LISBY
>  DEVICE! The grumpy greybeards have spoken of such marvelous things! In the
>  distant past, programmers of the old would use such special hardware optimized
>  just for running programs made with the LISBY language.
>  
>  Alas, the hardware itself has long since been rendered inoperable by decades
>  of neglect, but we were able to salvage the contents of some of the magnetic
>  tapes, which seem to contain programs. Sadly, we have no time to figure out
>  how they work, so perhaps you will help us to rediscover the old ways.
>  
>  Our search for documentation was mostly a failure, but we managed to find a
>  one crucial part: A brief architecture guide!
>  
>  Our cursory investigation reveals that the LISBY DEVICE seems to contain a
>  large variety of different op codes, but probably not all of are needed to
>  understand or run the programs. Perhaps successfully decompiling the programs
>  is a good start!
>  
>  README
>  bin
>  


## Write-up

This is the first challenge in a serie of three challenges based on reversing programs from an old computer architecture.
We are given a manual of how the architecture works and what are the instructions and opcodes.
We started by dividing the bytes manually into the appropriate sections and translating progressively the instructions.
Soon enough, we can understand what the program does and find a pattern in the instructions.
The program push two numbers to the stack and substract them, which gives an ASCII char and by doing a few of the substrations manually, we can see the string as the format of the flag (NIXU...).
We wrote a small Python script to read the binary, find the substraction instruction and do in operation on the numbers, which allowed us to recover the full flag.

### Analysis

A fake computer architecture is describe in this challenge which is used to reverse a binary to assembly code in order to understand what the program is doing and recover the flag. Reversing engineering is an important skill in security and may be used in multiple situations, such as malware analysis or to understand how a program/protocol works. While the Lisby architecture is fake, the general concepts of reversing a binary still apply as there exists a lot of different ISA like x86, ARM, MIPS, RISC-V, etc. which each has some differences. On the opposite of those architures, the Lisby device is unknown, therefore there is no toolchain around it (assembler, compiler, debugger, emulator, etc.) and reversing tools such as radare2 does not support it. Either we need to do the dissaembly by hand or write some tool to help us.

