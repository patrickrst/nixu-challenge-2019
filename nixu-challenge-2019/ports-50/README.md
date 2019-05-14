## Ports

**Categories:** pcap, first steps, 2019
**Points:** 50
**Description:**

>  The ports might be interesting, is there a way to hide information into numbers?
>  
>  
>  ports.pcap
>  


## Write-up

Based on the name of the challenge it seemed obvious that we should look into the port numbers. Using Wireshark we exported the port numbers from the pcap file into plain text.

```bash
tshark -r ports.pcap -T fields -e tcp.dstport > ports.txt
```

We then tried to translate the decimal numbers to ASCII. The result looked like a typical base64 string, a good sign that we're on the right track.

```
QVZLSHtmbHpvYnlmX25hcV9haHpvcmVmX25lcl9zaGFfZ2Jf
Y3lubF9qdmd1fQ==
```

The formating of the decoded base64 string assured us that we're almost done. Using ROT13, a version of the classic Caesar cipher, we recovered the key.

```
AVKH{flzobyf_naq_ahzoref_ner_sha_gb_cynl_jvgu}
NIXU{symbols_and_numbers_are_fun_to_play_with}
```

### Analysis

This challenge, which is functioning as an introduction to the Nixu Challenge, don't have many real world applications. The challenge introduce analysis of network traffic using programs like Wireshark and basic encodings but the solutions are straight-forward and don't require much thinking. While it is obviously possible to send information encoded as port numbers it is cumbersome and the erratic behaviour would easily be detected, and most likely blocked, by the most basic network security system.

