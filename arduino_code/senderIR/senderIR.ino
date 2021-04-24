#include <Arduino.h>

#include "PinDefinitionsAndMore.h"

#include <IRremote.h>
/*https://github.com/Arduino-IRremote/Arduino-IRremote*/

#define DELAY_AFTER_SEND 2000
#define DELAY_AFTER_LOOP 5000
#define DELAY_AFTER_Z906_START 3000

unsigned int valPin11 = 0;
unsigned int valPin12 = 0;
unsigned int count_loop = 0;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(11, INPUT); //TV
    pinMode(12, INPUT); //RADIO
    /*Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)  || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first printout
#endif*/
    
    IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK); // Specify send pin and enable feedback LED at default feedback LED pin

   /*Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);*/

#if defined(USE_SOFT_SEND_PWM) && !defined(ESP32) // for esp32 we use PWM generation by hw_timer_t for each pin

    IrSender.enableIROut(38);

    /*Serial.print(F("Send signal mark duration is "));
    Serial.print(IrSender.periodOnTimeMicros);
    Serial.print(F(" us, pulse correction is "));
    Serial.print((uint16_t) PULSE_CORRECTION_NANOS);
    Serial.print(F(" ns, total period is "));
    Serial.print(IrSender.periodTimeMicros);
    Serial.println(F(" us"));*/
#endif
}

/*uint16_t sAddress = 0x0102;
uint8_t sCommand = 0x34;*/
uint8_t sRepeats = 0;


void loop() {
    /*Serial.println();
    Serial.print(F(" repeats="));
    Serial.println(sRepeats);
    Serial.println();
    Serial.println();
    Serial.flush();*/

    /*IrSender.sendNECRaw(0xC0340102, sRepeats);
     IrSender.sendNECRaw(0xAE517F80, sRepeats); //code for POWER ON Beelink GT1
     IrSender.sendNECRaw(0x7F80A002, sRepeats); // POWER Z906 
     IrSender.sendNECRaw(0x7D82A002, sRepeats); // input 2 Z906
     IrSender.sendNECRaw(0xF30CA002, sRepeats); // input 3 Z906*/

    valPin11 = digitalRead(11);
    valPin12 = digitalRead(12);
    /*Serial.print(F("Pin 11 = "));
    Serial.println(valPin11, DEC);
    Serial.print(F("Pin 12 = "));
    Serial.println(valPin12, DEC);*/

    if(valPin11 == 1 && valPin12 == 0 && count_loop == 0) {        
       // Serial.println(F("Send NECRaw(0xAE517F80)"));
       // Serial.flush();
        IrSender.sendNECRaw(0xAE517F80, sRepeats); /* code for POWER ON Beelink GT1 */
        digitalWrite(LED_BUILTIN, HIGH);
        delay(DELAY_AFTER_SEND);
        digitalWrite(LED_BUILTIN, LOW);

     //   Serial.println(F("Send NECRaw(0x7F80A002)"));
     //   Serial.flush(); 
        IrSender.sendNECRaw(0x7F80A002, sRepeats); // POWER Z906
        digitalWrite(LED_BUILTIN, HIGH);
        delay(DELAY_AFTER_Z906_START);
        digitalWrite(LED_BUILTIN, LOW); 

     //   Serial.println(F("Send NECRaw(0x7D82A002)"));
//        Serial.flush(); 
        IrSender.sendNECRaw(0xF30CA002, sRepeats); // input 3 Z906
        digitalWrite(LED_BUILTIN, HIGH);
        delay(DELAY_AFTER_SEND);
        digitalWrite(LED_BUILTIN, LOW);
        //delay(DELAY_AFTER_LOOP); 
    }

    if(valPin11 == 0 && valPin12 == 1 && count_loop == 0) {
     //   Serial.println(F("Send NECRaw(0x7F80A002)"));
     //   Serial.flush(); 
        IrSender.sendNECRaw(0x7F80A002, sRepeats); // POWER Z906
        digitalWrite(LED_BUILTIN, HIGH);
        delay(DELAY_AFTER_Z906_START);
        digitalWrite(LED_BUILTIN, LOW); 

     //   Serial.println(F("Send NECRaw(0x7D82A002)"));
     //   Serial.flush(); 
        IrSender.sendNECRaw(0x7D82A002, sRepeats); // input 2 Z906
        digitalWrite(LED_BUILTIN, HIGH);
        delay(DELAY_AFTER_SEND);
        digitalWrite(LED_BUILTIN, LOW);
       // delay(DELAY_AFTER_LOOP); 
    }

    count_loop = count_loop + 1 ;
    
    //delay(2000); // additional delay at the end of each loop
}
