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
We use `strings` on the pcap file to extract the readable text, which gives us some commands that were run on the server and a email about the security audit, which contains 4 hints.
The fourth hint in the email confirms our doubt that there is no encryption cipher offered by the SSH server.
We need to compile the openssh client with a small modification to allow us to connect to the SSH server using the `none` cipher [@stackoverflow_openssh].
Once we try to connect, we need to authenticate using a key.
An other hint from the email tell us that the encryption key used by the two employees to connect to the server may have a weakness.
After having extracted the public keys from the network capture, we used RsaCtfTool to performs an attack against the two public keys to find a common factor and recover the private keys [@rsactftool].
We are now able to go one step further, but the server asks for a time-based one-time password (TOTP).
Using the other hints in the email, we know the validity of the TOTP is 5 minutes.
Also, the user ran a command on the file containing the TOTP secret that gives us what number appears in the secret and that there is only consonants and numbers.
The user also ran `ls`, which gives us the length (8 chars) of the secret and he ran `md5sum`, which gives us the MD5 hash of the secret.
Using hashcat mask attack and the hints we have about the secret, we brute forced the MD5 hash to find the value of the TOTP secret [@hashcat_mask].
With the secret, we are able to generate a TOTP that is valid for 5 minutes and finaly connect to the SSH server to retreive the flag!

