# ST950xx EEPROM CLONING USING ARDUINO UNO
Project Goal: Use Arduino to CLONE (make an exact duplicate) of the contents of a known-good ST950xx EEPROM directly, byte-for-byte in real time, without the need to create and minipulate or otherwise transfer BIN, HEX, or ASCII files. Simply put, from each address location, we read a byte one-by-one from the MASTER EEPROM chip and write the byte to the corresponding address location on a blank "CLONE chip". When done, we have two (or more if desired) EEPROMs with identical contents. 

The genesis of this project stems from the fact that many automobile 'Body Control Modules' (BCM) use this series of ST Micro EEPROM to save the vehicles' accessory and engine operating parameters. Additionally, the EEPROMs are coded with the applicable vehicle's VIN number.

When a BCM fails, so often goes the vehicle's anti-theft lockout logic and thus rendering the vehicle unstartable.  The anti-theft logic inhibits the engine's fuel controller from operating. Symptoms such as the car not starting, or starting momentarily but then shutting down within a few seconds, are indications that the car's anti-theft system is in control. This is both a normal function (actual theft deterrent) and on unintended consequence when the BCM fails. 

In the case of an actual failure of the Body Control Module, it fails to communicate with connected devices on the automobile's computer bus. Most notibly, the instrument cluster and warning lights usually behave erratically. If the vehicle will not start, towing to a repair station is the usual solution. Even upon the best of circumstances (close to home vs. traveling), this can be an expensive process subject to the the mercy and integrity of the repair station, be it a dealer or otherwise. Prices for replacement BCM modules fluctuating wildly. Additionally, there are tack-on charges to "re-program" the new BCM's EEPROM such that it contains the correct VIN, correct odometer log, etc.

What if, as a DIYer, one could obtain a good used and working BCM for less than $100 USD and do this programming at home.  The challenge is that the 950xx EEPROM inside the replacement BCM unit contains the data of the vehicle from which it was removed and thus doesn't contain data related to one's personal VIN and other unique vehicle data. So, we must remove the existing EEPROM chip (soldering skills required) and replace it with our MASTER EEPROM chip (or better yet, a CLONED copy of it).   Simply put, the newly purchased BCM essentially becomes a "plug and play" unit. 

Note: Statistically, the failure mode of these BCMs is not related to a failure of the subject EEPROM. BCMs are complex electronics units and judging from the ones I've seen, the manufacturing Q/A has much to be desired.   Yes, it's possible that your original EEPROM has failed but unlikely. One must not be careless or otherwise mishandle these static-sensitive chips. It is highly recommended that DIYers build up this CLONING circuitry and verify its operation by using pairs of new EEPROMs as the first step. Only then does it make sense to begin any other steps and work related to these actual BCM challenges. I would rate this project in the DIFFICULT, EXPERT category. The Arduino-related tasks are simple but without skills to solder/unsolder SOI8 Chip sizes, the liklyhood of a successful outcome here is very low. Just saying. 

New chips are approx. $.34 USD each and cheap insurance avoiding damaging the ONLY MASTER copy of data you have. Build the electrical breadboard, upload the .ino, and play with a couple of spare EEPROMs to become familiar with the process and to become confident in wiring and functionality of your programmer/cloner.  Happy Days.  

Obviously, by removing the new/replacement BCM's EEPROM with the actual EEPROM from one's original (failed) BCM will work, I decided not to risk accidentally damaging my original VIN's EEPROM. Thus, it made sense to come up with this Arduino solution - a way to simply CLONE the master EEPROM to few blank spares and use one of them instead. Then, save and preserve the original (MASTER) EEPROM for preservation of the data. I also just created a couple of CLONEs just for safekeeping. 

ABOUT THE CLONING ARDUINO SOFTWARE
__________________________________

NOTE: A complete electrical schematic is included in this repository's DOCS folder for those wishing to build/modify/expand the basic design. AUTODESK EAGLE was used for designing and creating the circuitry. That file is included and recognizable by the unique ".sch" file extention. There is also a standard .pdf version for printing and reference.

The CLONING software is simple to use but only works if a pair of EEPROMs are connected to Arduino per the schematic diagram provided. I soldered the original EEPROM (MASTER) to a SOI8 PC board. As for the CLONE targets, I use a HiLetgo brand SIO8 Zero-Insertion-Force socket (ZIF) as pictured and available on Amazon for approximately $4.50 USD each. I easily produced 3 or 4 CLONES of various MASTER chips using these ZIF sockets. They work very well. 

The CLONING routine reads the MASTER's data, one byte at a time, and then WRITES that byte to the exact, corresponding address location on the CLONE 9504xx chip. Using the .ino provided, this process to clone a 4K, 95040 EEPROM, requires less than 3 seconds.  An added feature of the sketch includes a "VERIFICATION" of the cloned data. This verification is a byte-for-byte comparison between the MASTER's data and the data written to the CLONE. Any discrepancies are noted but this should only occur if the CLONE chip is faulty. I ordered my 95040 chips from Digikey ($.34 cents USD each) and have had no failures on the 10 chips I received from Digikey. These are STMicrotronics brand chips.

More will be added to this Readme as necessary.


Special thanks to Robert Middleton for foundation work shared on GitHub:

https://github.com/rm5248/m95-eeprom-arduino/commits?author=rm5248 
  
Adding to Robert Middleton's work (and that of others to whom he gives credit in helping him),
I expanded the existing Arduino-based EEPROM Reader/Writer to include connections to a second EEPROM (to be the target for CLONING). The purpose of my circuitry was to enable 'CLONING' of the content of the original EEPROM's data. This CLONE was to be an address-to-address / data-to-data copy (CLONE) of the "MASTER" ST95040 EEPROM.Once the CLONING code has run, supplemental routines are included to VERIFY byte-for-byte data match.Any data mismatch between the MASTER and CLONE is flagged and displayed during the verification process. At the time of this submission, ten new ST95040 (4k EEPROMs) were cloned - each on the firstattempt without errors. Thus, I do consider the design stable. That said, I seek to provide a more elegant code within the limits of my minimal experience.  Improvements are always welcomed in the hope that, for the benefit of those who lack high skillsets, contributors will consider this a teaching moment and adorn the lines of code with commentary. Thank you in advance for this.

Regards,
Bill Glenn

