# ST950xx EEPROM CLONING USING ARDUINO UNO
Project Goal: Use Arduino to CLONE (make an exact duplicate) of the contents of a known-good ST950xx EEPROM directly, byte-for-byte in real time, without the need to create and minipulate or otherwise transfer BIN, HEX, or ASCII files. Simply put, from each address location, we read a byte one-by-one from the MASTER EEPROM chip and write the byte to the corresponding address location on a blank "CLONE chip". When done, we have two (or more if desired) EEPROMs with identical contents. 

The genesis of this project stems from the fact that many automobile 'Body Control Modules' (BCM) use this series of ST Micro EEPROM to save the vehicles' accessory and engine operating parameters. Additionally, the EEPROMs are coded with the applicable vehicle's VIN number.

Often, when a BCM fails, so often goes the vehicle's anti-theft lockout logic and thus rendering the vehicle unstartable.  The anti-theft logic inhibits the engine's fuel controller from operating. Symptoms such as the car not starting, or starting momentarily but then shutting down within a few seconds, are indications that the car's anti-theft system is in control. This is both a normal function (actual theft deterrent) and on unintended consequence when the BCM fails. 

In the case of an actual failure of the Body Control Module, this BCM fails to communicate with the automobile's computer bus and all sorts of weird indications and functions occur. For most owners, if the vehicle will not start, towing to a repair station is the usual solution. This can be expensive process since the owner is at the mercy of the repair station, be it a dealer or otherwise. Prices for replacement new BCM modules can be very expensive with prices fluctuating wildly. In addition, there are embedded charges to "re-program" the new BCM's EEPROM such that it contains the correct VIN and hopefully, the correct odometer log.

What if, as a DIYer, one could obtain a good used and working BCM for less than $100 USD? The problem is that the 950xx EEPROM inside the used BCM unit contains the data of the vehicle from which it was removed and thus doesn't contain data related to YOUR personal VIN and other unique vehicle data. So, by removing and replacing this EEPROM chip with your EEPROM chip (or better yet, a clone) from the non-working BCM module, there is no need to tow the car to a dealer to have the BCM programmed. Simple put, the replacement/new BCM now becomes a "plug and play" unit. Note: Statistically, the failure mode of BCMs is not related to failure of the EEPROM. Yes, it's possible but very highly unlikely that your original EEPROM has failed. What IS possible is that in the process of cloning a good EEPROM from the BCM, one is careless or mishandles the static-sensitive chip, the chip may be damaged. It is highly recommended that DIYers build up this CLONING circuitry and verify its operation by using pairs of new EEPROMs.

New chips are approx. $.34 USD each and cheap insurance avoiding damaging the ONLY MASTER copy of data you have. Build the electrical breadboard, upload the .ino, and play with a couple of spare EEPROMs to become familiar with the process and to become confident in wiring and functionality of your programmer/cloner.  Happy Days.  

Obviously, by removing the new/replacement BCM's EEPROM with the actual EEPROM from one's original (failed) BCM will work, I decided not to risk accidentally damaging my original VIN's EEPROM. Thus, it made sense to come up with this Arduino solution - a way to simply CLONE the master EEPROM to few blank spares and use one of them instead. Then, save and preserve the original (MASTER) EEPROM for preservation of the data. I also just created a couple of CLONEs just for safekeeping. 

ABOUT THE CLONING ARDUINO SOFTWARE
__________________________________

NOTE: A complete electrical schematic is included in this repository's DOCS folder for those wishing to build/modify/expand the basic design. AUTODESK EAGLE was used for designing and creating the circuitry. That file is included and recognizable by the unique ".sch" file extention. There is also a standard .pdf version for printing and reference.

The CLONING software is simple to use but only works if a pair of EEPROMs are connected to Arduino per the schematic diagram provided. I soldered the original EEPROM (MASTER) to a SOI8 PC board. As for the CLONE targets, I use a HiLetgo brand SIO8 Zero-Insertion-Force socket (ZIF) as pictured and available on Amazon for approximately $4.50 USD each. I easily produced 3 or 4 CLONES of various MASTER chips using these ZIF sockets. They work very well. 

The CLONING routine reads the MASTER's data, one byte at a time, and then WRITES that byte to the exact, corresponding address location on the CLONE 9504xx chip. Using the .ino provided, this process to clone a 4K, 95040 EEPROM, requires less than 3 seconds.  An added feature of the sketch includes a "VERIFICATION" of the cloned data. This verification is a byte-for-byte comparison between the MASTER's data and the data written to the CLONE. Any discrepancies are noted but this should only occur if the CLONE chip is faulty. I ordered my 95040 chips from Digikey ($.34 cents USD each) and have had no failures on the 10 chips I received from Digikey. These are STMicrotronics brand chips.

More will be added to this Readme as necessary.


Special thanks to Robert Middleton for his advice and work shared on GitHub:

https://github.com/rm5248/m95-eeprom-arduino/commits?author=rm5248 
  
Adding to Robert Middleton's work (and that of others to whom he gives credit in helping him),
I expanded the existing Arduino-based EEPROM Reader/Writer to include connections to a second EEPROM (to be the target for CLONING). The purpose of my circuitry was to enable 'CLONING' of the content of the original EEPROM's data. This CLONE was to be an address-to-address / data-to-data copy (CLONE) of the "MASTER" ST95040 EEPROM.Once the CLONING code has run, supplemental routines are included to VERIFY byte-for-byte data match.Any data mismatch between the MASTER and CLONE is flagged and displayed during the verification process. At the time of this submission, ten new ST95040 (4k EEPROMs) were cloned - each on the firstattempt without errors. Thus, I do consider the design stable. That said, I seek to provide a more elegant code within the limits of my minimal experience.  Improvements are always welcomed in the hope that, for the benefit of those who lack high skillsets, contributors will consider this a teaching moment and adorn the lines of code with commentary. Thank you in advance for this.

Regards,
Bill Glenn

