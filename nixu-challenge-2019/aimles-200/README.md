## AIMLES - staging

**Categories:** forensics, crypto, Disobey!, 2019
**Points:** 200
**Description:**

>  AIMLES is going public soon and they are preparing for a final
>  security audit. Their local OpSecDevSecOp guy went through the
>  systems before the real auditors arrive and some things may be
>  indeed to be corrected. We managed to get hold of some traffic in
>  that network, see if you can do some pro-bono!
>  
>  preaudit.pcap
>  
>  The server is running at aimles.thenixuchallenge.com 6022.
>  
>  (This challenge was part of the Disobey 2019 CTF.)
>  


## Write-up

We are given a network capture in the form of a `.pcap` and a url:port pair to a server running SSH.
Trying to SSH into the server gives an error about no matching ciphers.
Therefore, we decide to look at the network capture which consists of SSH traffic.
Looking around in the packets, we can see that the shell session is not encrypted.
We use `strings` on the pcap file to extract the readable text, which gives us some commands that were run on the server and an email about the security audit, which contains 4 hints.
The fourth hint in the email confirms our doubt that there is no encryption cipher offered by the SSH server.
We need to compile the OpenSSH client with a small modification to allow us to connect to the SSH server using the `none` cipher [@stackoverflow_openssh].
Once we try to connect, we need to authenticate using a key.
Another hint from the email tells us that the encryption key used by the two employees to connect to the server may have a weakness.
After having extracted the public keys from the network capture, we used RsaCtfTool to perform an attack against the two public keys to find a common factor and recover the private keys [@rsactftool].
We are now able to go one step further, but the server asks for a time-based one-time password (TOTP).
Using the other hints in the email, we know the validity of the TOTP is 5 minutes.
Also, the user ran a command on the file containing the TOTP secret that gives us what number appears in the secret and that there is only consonants and numbers.
The user also ran `ls`, which gives us the length (8 chars) of the secret and he ran `md5sum`, which gives us the MD5 hash of the secret.
Using Hashcat mask attack and the hints we have about the secret, we brute forced the MD5 hash to find the value of the TOTP secret [@hashcat_mask].
With the secret, we are able to generate a TOTP that is valid for 5 minutes and finally connect to the SSH server to retrieve the flag!

### Analysis

This challenge consists of multiple steps that need to be solved in order to obtain the flag. This feels more realistic than other CTF challenges, as there are multiple skills involved and there is a process to go through instead of just solving a specific task. It resembles more to what a penentration tester job may look like (the challenge description refers to a security audit). The challenge requires to have networking skills (analyzing a .pcap with Wireshark, understanding the SSH protocol) and an understanding of encryption/authentification (how OpenSSH works, the flaws in RSA key generation, Time-based one time password). Such a challenge demonstrates that a chain of multiple exploitable flaws in a system may allow to obtain access to it.

