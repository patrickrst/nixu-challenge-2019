## fridge 2.0

**Categories:** 2019, reversing, web
**Points:** 200
**Description:**

>  Recently you jumped on the smart home bandwagon and ordered an
>  intelligent fridge from a promising startup company.  The letter
>  which accompanied the device says: "Congratulations for choosing our
>  intelligent cloud-connected heat removal solution for consumables!
>  Note that we are in an early phase, which means that our operations
>  staff is keeping an extremely close eye on the fleet management
>  portal, monitoring all device registrations."
>  
>  
>  In addition you also got a CD-ROM(!) with the firmware updater for
>  the fridge along with the current firmware.
>  
>  
>  Firmware: iotfridge
>  
>  Architecture diagram: fridge_2.0.png
>  
>  Update (2019-01-02): for some reason DNS does not work in the R&D
>  network, could be because of the very restricive firewall...
>  


## Write-up

For this challenge, we get the firmware of an IoT-device that is part of a Cloud network.
We started by reversing the firmware using the tool Radare2 and afterwards Ghidra.
From the binary, we can see that the device connects to an external server to do a JSON request.
The URL that the device sends a request to is encryption inside the firmware.
However, the key used by the encryption is also stored in the firmware, so we are able to decrypt it using AES to recover the URL.
The recovered URLs are `https://fridge2_0.thenixuchallenge.com/api/register` and `https://fridge2_0.thenixuchallenge.com/api/temp` which are part of the API to register a new IOT device and control the temperature of the device.
However, we have not been able to go farther from there.
We have tried to find other interesting pages/protocols on the server and also tried to exploit and do fuzzing on the API, but with no success.

### Analysis

As this challenge is about insecure IoT-devices, it might be the challenge with most real world relevance of them all. According to experts there will be 75 billion IoT devices in the world by 2025 [@iotforall] and IoT-devices have a history of lacking security. By comparison the device in this challenge is reasonably secure. Its real life counterparts often operate with well-known default login credentials that are the same for all devices and just like the device in the challenge they are often delivered with insecure firmware that is seldom patched. A good example of the destructive potential of insecure IoT-devices is the Mirai botnet, consisting of only IoT-devices, which in late autumn 2016 was used to launch a massive DDoS attack against a company responsible for parts of the Domain Name System. The attack lasted for more than a day, reached traffic levels of more than a terabit per second against the targets and brought down numerous major websites and services, including major websites like Twitter, the Guardian and CNN [@guardian_ddos].

