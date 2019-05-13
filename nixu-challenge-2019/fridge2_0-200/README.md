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

For this challenge, we get the firmware of an IOT device that is part of a Cloud network.
We started by reversing the firmware using the tool Radare2 and afterwards Ghidra.
From the binary, we can see that the device connect to an external server to do a JSON request.
The URL that the device sends a request to is encryption inside the firmware.
However, the key used by the encryption is also stored in the firmware, so we are able to decrypt it using AES to recover the URL.
The recovered URLs are `https://fridge2_0.thenixuchallenge.com/api/register` and `https://fridge2_0.thenixuchallenge.com/api/temp` which are part of the API to register a new IOT device and control the temperature of the device.
However, we have not been able to go farther from there.
We have tried to find other interesting pages/protocols on the server and also tried to exploit and do fuzzing on the API, but with no success.

