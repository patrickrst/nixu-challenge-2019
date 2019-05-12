## Exfiltration

**Categories:** pcap, 2019
**Points:** 100
**Description:**

>  A file was exfiltrated using common protocol. In fact if this
>  protocol didn't exist using internet would be annoying.
>  
>  Can you find the header and then extract the file?
>  
>  
>  exfiltration.pcap
>  


## Write-up

This challenge offers a network capture containing mostly SSL and DNS traffic.
From the hint in the description (using internet would be annoying if this protocol did not exist), we can assume it is about DNS (would be annoying to use an IP address instead of a domain name).
Looking at the DNS packets, we can see a lot of legitimate traffic, but also many TXT, MX and CNAME queries to a domain name ending with `malicious.pw`.
We can filter those queries using this expression `dns && dns.qry.name contains "malicious.pw"` in Wireshark.

From there, we can assume that the data in encoded in the numbers in the domain name.
Looking up on the web, we can find a DNS tunnel named dnscat2 that seems to be the one in use [@dnscat2][@dnscat_writeup].
We export the DNS queries from Wireshark to a text file, keep only the domain name and strip the `malicious.pw` ending.
By converting the series of number to ASCII, we can find a session in a UNIX shell and a file named `flag.png`, which seems to have also been transfered in the same DNS tunnel session.
Indeed, we can also find the header of a PNG file, starting with `89 50 4E 47`.
Using a Python script and the library `dpkt`, we parse the network capture and keep only the data from the DNS queries that contains `PNG` to the end of the image, the packet containing `IEND`.
We also need to strip a few bytes that are used by the dnscat2 protocol.
Writing the image bytes to a file results in a valid PNG (after a few tries) which contains the flag `NIXU{just_another_tunneling_technique}`.

