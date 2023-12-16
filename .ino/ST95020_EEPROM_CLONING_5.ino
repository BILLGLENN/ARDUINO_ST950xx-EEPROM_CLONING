

    //      Sprintf reference: See https://www.programmingelectronics.com/sprintf-arduino/ 

    //      CREDITS:

    //      Special thanks to Robert Middleton for his advice and work shared on GitHub:

    //      https://github.com/rm5248/m95-eeprom-arduino/commits?author=rm5248 
   

    // NOTE: Although Arduino's built-in Serial Monitor is adequate for displaying
    // raw data using the Serial.print functionality, Sprintf functions present more elequent
    // (albeit more arduous) data display formatting options.  Simpler, suitable solutions
    // to display data come with the use of external Terminal software such as Terminall
    // and (my personal favorite) Tera Terminal. These external terminals often offer
    // features for simple control and display of the EEPROM read/write data contents.
    // It is free and downloads are available from a wide host of websites. Version 5 is
    // available at my Github repository for your convenience:

    // https://github.com/BILLGLENN/ARDUINO_ST950xx-EEPROM_CLONING/tree/main

#include <SPI.h>

#define csPIN_CLONE   9           // CS pin for "CLONE/DUPLICATE EEPROM"
#define csPIN_MASTER 10         // Arduino's Pin 10 : 

//opcodes for 950xx command register

#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1

    //=========================================
    //  FYI: READ 11 and WRITE 10 (below) are not required for the byte-by-byte read/write
    //  functions used for cloning, i.e., readByteAt() and writeByteAt()
    //=========================================
    // ST95040 may be split:  (512 bytes is split into 2ea 256 byte reads.
    // This is controlled uniquely by setting READ to 11 (if desired)
    
            #define READ  3         // 0000 X011 = 3 for first 64, 128, or 256 of 95010, 20, and 40
    
    //     #define READ 11         // 0000 1011 = 11 for second block of 256 existing in 95040.
    //=========================================
    // The same low/high block access is required for WRITEs as well. 
          
          #define WRITE 2   // 0000 0010      bit 4 = don't care for 95010, 95020. bit 4 =0 means low-block write 95040.

    //   #define WRITE 10 //  0000 1010   for high-block 256 bytes of 95040. 
//=========================================

void setup(){

    Serial.begin(9600);
    digitalWrite(csPIN_MASTER,HIGH);
    digitalWrite(csPIN_CLONE,HIGH);
    pinMode(csPIN_MASTER,OUTPUT);
    pinMode(csPIN_CLONE,OUTPUT);

    SPI.begin();

    Serial.println("<Send 1> : Display Master EEprom's DATA");
    Serial.println("<Send 2> : Display CLONE's Data"); 
    Serial.println("<Send 3> : To compare MASTER & CLONE's Data");
    Serial.println("<Send 6> : BEGIN CLONING. (Duplicate data of MASTER EEPROM to CLONE");
    Serial.println("<Send 9> : N/A - TBD");

    Serial.setTimeout(7000); //sets the readbyte to wait 7 seconds

    }  // end setup()

//=============================================================
    void loop(){
        
        if(Serial.available() > 0){
            
            char letter = Serial.read();    // Monitor the serial port for user keyboard input/<send>

        // Check to see which menu choice selected, i.e.,  1, 2, 3, 6, or 9(TBA)
        //------------------------------------------------------------------------------
        //  For MENU : <Send 1> : Display Master EEprom's DATA
        //-----------------------------------------------------------------------
            
            if(letter == '1'){               // Via Serial Monitor (or Tera Term) keyboard input '1' SENT 

            char ch[30];  

                for (uint16_t i=0;i<512;i++){       //read each of 512 bytes of 95040 (0-511)

                    sprintf(ch,"%02X",readByteAt(csPIN_MASTER,i));  // sprintf format "%02X" X= unsigned hex, uppercase.  %02x = same but lowercase

                    Serial.print(ch);  //prints each byte (OUTPUT TO EITHER SERIAL MONITOR OR TERA TERM (E:DRIVE) PROGRAM
                } 

             Serial.println();
             
             Serial.println();Serial.println("End of Master EEPROM contents.");

        }       // end if  (letter == 1) 
       
        //-----------------------------------------------------------------------
        // For MENU <Send 2> : Display CLONE's Data
        //-----------------------------------------------------------------------
        
            if(letter == '2'){  
    
            char ch[30];  // wjg: appears to declare a char array of length 29 + 1 array terminator. See Arduino Arrays.

                for (uint16_t i=0;i<512;i++){       //read all 512 bytes (0-511)

                    sprintf(ch,"%02X",readByteAt(csPIN_CLONE,i));  // sprintf format "%02X" X= unsigned hex, uppercase.  %02x = same but lowercase

                    Serial.print(ch);  //prints each byte (OUTPUT TO EITHER SERIAL MONITOR OR TERA TERM (E:DRIVE) PROGRAM
                }   
    
            Serial.println();Serial.println("End of CLONE EEPROM's content display.");
          
        }  // end  (letter == 2)

     //-----------------------------------------------------------------------
     // For MENU <Send 3> : Compare MASTER & CLONE's Data for match
     //-----------------------------------------------------------------------   
     
        if(letter == '3'){      // Verify successful cloning process
                     
             Serial.println("Address-for-address CLONE DATA verification in progress...");Serial.println();
             
             int DATA_ERROR_CNT = 0;
             
             for (uint16_t i=0;i<512;i++){       //compare all 512 bytes (0-511)
                
                    delay(10);  // works without this but 10ms has soothing display effect.

                        if (readByteAt(csPIN_CLONE,i) != (readByteAt(csPIN_MASTER,i)))
                            {
                            Serial.print("Error @ address loc :\t "); Serial.print(i); Serial.print("\t Master's DATA:\t");Serial.print(readByteAt(csPIN_MASTER,i)); 
                            Serial.print("\t  CLONE's DATA:\t");Serial.println(readByteAt(csPIN_CLONE,i));
                            
                            DATA_ERROR_CNT++;                          
                            }         
                    }         
                    if(DATA_ERROR_CNT == 0){    // Successful clone created
                        Serial.println("MASTER & CLONE Data 100% MATCH");
                    }
                    else{           // Alert that clone process failed & contains errors.
                    Serial.print("CLONE mismatch data errors = ");Serial.println(DATA_ERROR_CNT);
                    }
        
        }    // end  (if letter == '3')

     //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     // For MENU <Send 6> : BEGIN CLONING. (Duplicate data of MASTER EEPROM to CLONE");
     //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        if(letter == '6'){    // CLONE 95040 MASTER EEPROM to a blank 95040 EEPROM

            Serial.println("Processing CLONE. Please wait until complete (approx. 15 secs)" );Serial.println();
    
            char ch[30];  // wjg: appears to declare a char array of length 29 + 1 array terminator. See Arduino Arrays.

                    for (uint16_t i=0;i<512;i++){       //read all 512 bytes (0-511)

                        // readByte from MASTER and writeByte to CLONE
                            
                            writeByteAt(csPIN_CLONE, i, (readByteAt(csPIN_MASTER,i)));  // one byte at a time
                        } 
                        
            //=============  CONFIRM CLONE

                    for (uint16_t i=0;i<512;i++){       //read all 512 bytes (0-511)

                        //READ bytes from CLONE 95040 EEPROM
                        //========================================
    
                        sprintf(ch,"%02X",readByteAt(csPIN_CLONE,i));  // sprintf format "%02X" X= unsigned hex, uppercase.  %02x = same but lowercase

                        Serial.print(ch);  //prints each byte (OUTPUT TO EITHER SERIAL MONITOR OR TERA TERM (E:DRIVE) PROGRAM

                    } // end of 'for' loop through all memory addresses

                Serial.println();Serial.print("Cloning process completed. ");

        }   // end "if (letter == 6)
 
     //-----------------------------------------------------------------------
     // For MENU <Send 9> : Unassigned. TBA
     //-----------------------------------------------------------------------       
        if(letter == '9'){    // To be added at a later date.                   
            Serial.println("Key '9' is not implemented. TBA." );Serial.println();        
        } 
        delay(10);
    //-----------------------------------------------------------------------
        
  }  // end if (serial.available)

 }  // end of loop()


// ============  F U N C T I O N S ===============


//-------------------------------------------
//  Convert ASCII to Hex
//-------------------------------------------
        
        int8_t intValueOfHexaKey(char c){
            if ((c >= '0') && (c <= '9')) return c - '0';
            if ((c >= 'A') && (c <= 'F')) return c - 'A' + 10;
            return -1; // error should not happen though...               
            } // end of function to convert ASCII to HEX


    //------------------------------------------------------------------------------------
    //      SPI read a single byte from the chip selected (cs) and from location (adr) 
    //------------------------------------------------------------------------------------

    uint8_t readByteAt(uint8_t cs,uint16_t adr){   // call with chip select pin (cs) and address loc (adr) 
        
        SPI.beginTransaction(SPISettings(4000000,MSBFIRST,SPI_MODE0));   // baud rate, byte order, mode

        digitalWrite(cs,LOW);                // select the chip
        uint8_t b=highByte(adr);
        b = b <<3;                               //move address bit 8 to bit 11
        b = b | READ;                           // (wjg notes that this is an : AND operation with READ instruction) read command
        SPI.transfer(b);                       // send the READ cmd + address bit 8
        SPI.transfer(lowByte(adr));      // low byte of address
        b= SPI.transfer(0);                  // read the actual data byte
        
        digitalWrite(cs,HIGH);              // de-select the chip
        SPI.endTransaction();
        
        return b;  // return the data byte read from "adr" location
    
    }       // end function SPI  "readByteAt()"

        //---------------------------------------------------------------------------------
        //   SPI write a single byte to the selected chip (cs) and TO the location (adr)  
        //---------------------------------------------------------------------------------

        uint8_t writeByteAt(uint8_t cs,uint16_t adr, char d){

        SPI.beginTransaction(SPISettings(4000000,MSBFIRST,SPI_MODE0));

        // First, send a WREN byte command to enable 'writing'
        digitalWrite(cs,LOW);
        SPI.transfer(WREN);         //write enable 
        digitalWrite(cs,HIGH);       // deselect (cycle a HIGH state)
        delay(10);                         //settle
 
        digitalWrite(cs,LOW);        // re-select on this next LOW cycle
        uint8_t a=highByte(adr);
        a = a <<3;  //move address bit 8 to bit 11
        a = a | WRITE;  // write command
        SPI.transfer(a); // send the WRITE cmd + address bit 8
        SPI.transfer(lowByte(adr)); // low byte of address
        a= SPI.transfer(d); // read (WJG: or should this be 'write') the actual byte

        digitalWrite(cs,HIGH); 
        delay(15); // wait.. I was too lazy to make read status byte to verify write completed the byte. Could've used the op code check.
        SPI.endTransaction();

        return a;

    }   // end  of SPI  "writeByteAt()"

//---------------------------------------------------------------------------






    
