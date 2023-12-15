# ARDUINO_ST950xx-EEPROM_CLONING
Use Arduino to CLONE contents of a known-good ST950xx EEPROM directly, byte-for-byte in real time. There is no need to create BIN, HEX, or ASCII data files although the code provides simple ways to do so if desired.  

The genesis of this project stems from the fact that many automobile 'Body Control Modules' (BCM) use this series of ST Micro EEPROM to save the vehicles' accessory and engine operating parameters. Additionally, the EEPROMs are coded with the applicable vehicle's VIN number.

Often, when a BCM fails, so often goes the vehicle's anti-theft lockout logic and thus rendering the vehicle unstartable.  The anti-theft logic inhibits the engine's fuel controller from operating. Symptoms such as the car not starting, or starting momentarily but then shutting down within a few seconds, are indications that the car's anti-theft system is in control. This is both a normal function (actual theft deterrent) and on unintended consequence when the BCM fails. 

In the case of an actual failure of the Body Control Module, this BCM fails to communicate with the automobile's computer bus and all sorts of weird indications and functions occur. For most owners, if the vehicle will not start, towing to a repair station is the usual solution. This can be expensive process since the owner is at the mercy of the repair station, be it a dealer or otherwise. Prices for replacement new BCM modules can be very expensive with prices fluctuating wildly. In addition, there are embedded charges to "re-program" the new BCM's EEPROM such that it contains the correct VIN and hopefully, the correct odometer log.

What if, as a DIYer, one could obtain a good used and working BCM? The problem is that the EEPROM inside the used unit contains the data from the vehicle to which it was installed and used doesn't contain data related to YOUR vehicle. But, by removing and replacing the EEPROM chip with the chip from one's non-working BCM module, there is no need to tow the car to a dealer to have the BCM programmed. Simple put, the replacement BCM now becomes "plug & play".

Obviously, by removing and replacing the new BCM's EEPROM with the one from one's original (failed) BCM will work, I decided not to risk accidentally damaging my VIN's EEPROM. Thus, it made sense to come up with a way to simply CLONE the master EEPROM with a few spares and use them instead. Then, save and preserve the original (MASTER) EEPROM and its data for safekeeping. 

ABOUT THE CLONING ARDUINO SOFTWARE
__________________________________

The CLONING software is simple to use but only works if a pair of EEPROMs are connected to Arduino per the schematic diagram provided. I soldered the original EEPROM (MASTER) to a SOI8 PC board. As for the CLONE targets, I use a Zero-Insertion-Force socket (ZIF) as pictured. These sockets are available on Amazon for about $4.  I made 3 or 4 CLONES. Chips are cheap and good insurance for clumsy seniors like myself.

The CLONING routine reads the MASTER's data, one byte at a time, and then WRITES that byte to the exact, corresponding address location on the CLONE 9504xx chip. Using the .ino provided, this process to clone a 4K, 95040 EEPROM, requires less than 3 seconds.  An added feature of the sketch includes a "VERIFICATION" of the cloned data. This verification is a byte-for-byte comparison between the MASTER's data and the data written to the CLONE. Any discrepancies are noted but this should only occur if the CLONE chip is faulty. I ordered my 95040 chips from Digikey ($.34 cents USD each) and have had no failures on the 10 chips I received from Digikey. These are STMicrotronics brand chips.

More will be added to this Readme as necessary.

/*  FOREWORD:
 * 
 * Special thanks to Robert Middleton for his advice and work shared on GitHub:
 *
 * https://github.com/rm5248/m95-eeprom-arduino/commits?author=rm5248 
 *   
 * and help with GitHub to complete a personal project that directly "CLONEs" an known-good eeprom's
 * contents. Adding to his work (and that of others to whom he gives credit for helping him),
 * I expanded Robert's Arduino-based EEPROM Reader/Writer to include connections to a second EEPROM. 
 * The purpose of my circuitry was to enable 'CLONING' the content of the original EEPROM's data.
 * This CLONE was to be an address-to-address / data-to-data copy (CLONE) of the "MASTER" ST95040 EEPROM.
 * Once the CLONING code has run, supplemental routines are included to VERIFY byte-for-byte data match.
 * Any data mismatch between the MASTER and CLONE is flagged and displayed during the verification 
 * process. At the time of this submission, ten new ST95040 (4k EEPROMs) were cloned - each on the first
 * attempt without errors. Thus, I do consider the design stable. That said, I seek to provide a more elegant
 * code within the limits of my minimal coding experience.  Improvements are always welcomed with the
 * hope that, for those who lack high skillsets, contributors will consider this a teaching moment and
 * shower the code with abundant commentary to enhance other's experience. Thank you in advance for this.
 * 
 *  Regards,
 *  Bill Glenn
*/
