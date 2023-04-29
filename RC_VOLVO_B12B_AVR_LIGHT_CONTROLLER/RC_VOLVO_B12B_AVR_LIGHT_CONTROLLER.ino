/*
Slave Controller.

Microcontroller: Arduino Nano
Reveives commands via IIC.

Author: Matthew Picone
Date: 24/Jun/2021

Description: Receives an integer and checks conditions against the 
predetermined actions and resonds accordingly. This controller looks
after all of the lighting, the MP3 player, and the buzzer.
*/

#include <Wire.h>

#include <SoftwareSerial.h>
#include <RedMP3.h>
#define LCU_REVERSE_OFF 41
// AVR settings for slave receiver.

#define SLAVE_ADDR 0x75


// PIN SETUP
#define BUZ     12
#define NSIND   11
#define OSIND   10
#define NSWW     9
#define OSWW     8
#define NSLB     7
#define OSLB     6
#define REV      5
#define CL       4
#define HB       3


// COMMAND ASSIGNMENTS
#define LCU_REVERSE         20
#define LCU_REVERSE_OFF     21
#define LCU_WIGWAG_2       22
#define LCU_WIGWAG_1      23
#define LCU_NSIND           24
#define LCU_NSIND_OFF       25
#define LCU_OSIND           26
#define LCU_OSIND_OFF       27
#define LCU_HEADLIGHTS      28
#define LCU_HEADLIGHTS_OFF  29
#define LCU_HIGHBEAM        30
#define LCU_HIGHBEAM_OFF    31
#define PLAYSOUND_1         32
#define PLAYSOUND_2         33
#define PLAYSOUND_3         34
#define PLAYSOUND_4         35
#define PLAYSOUND_5         36
#define PLAYSOUND_6         37
#define PLAYSOUND_7         38
#define PLAYSOUND_8         39
#define PLAYSOUND_9         40
#define PLAYSOUND_10        41
#define PLAYSOUND_11        42
#define PLAYSOUND_12        43
#define PLAYSOUND_13        44
#define PLAYSOUND_14        45
#define PLAYSOUND_15        46
#define PLAYSOUND_16        47
#define PLAYSOUND_17        48
#define PLAYSOUND_18        49
#define PLAYSOUND_19        50
#define PLAYSOUND_20        51

#define LCU_LOOP_RESET      100


// CIRCUIT STATES
int BUZ_STATE = false;
int NSIND_STATE = LOW;
int OSIND_STATE = LOW;
int NSWW_STATE = LOW;
int OSWW_STATE = LOW;
int NSLB_STATE = LOW;
int OSLB_STATE = LOW;
int REV_STATE = LOW;
int CL_STATE = LOW;
int HIGHBEAM_STATE = LOW;

//Command States
int CMDSTATE_REVERSE = false;
int CMDSTATE_WIGWAG2 = true;
int CMDSTATE_WIGWAG1 = true;
int CMDSTATE_NSIND = false;
int CMDSTATE_OSIND = false;
int CMDSTATE_HEADLIGHTS = false;
int CMDSTATE_HIGHBEAM = false;
unsigned long WIGWAG_COUNTER = 0;
// TIMER VARIABLES
unsigned long previousMillis = 0;
const long INTERVAL = 500;

// COMMAND VALUE & RECEIVE FUNCTION
int CV;
void receiveEvent() {
  CV = Wire.read();
}

// MP3 PLAYER SETTINGS
#define MP3_RX 2
#define MP3_TX 0
MP3 mp3(MP3_RX, MP3_TX);
int8_t volume = 0x1e;
int8_t folderName = 0x01;
int8_t DOORS_CLOSING = 0x01;
int8_t TRACK_2 = 0x02;
int8_t TRACK_3 = 0x03;
int8_t TRACK_4 = 0x04;
int8_t TRACK_5 = 0x05;
int8_t TRACK_6 = 0x06;
int8_t TRACK_7 = 0x07;
int8_t TRACK_8 = 0x08;
int8_t TRACK_9 = 0x09;
int8_t TRACK_10 = 0xA;
int8_t TRACK_11 = 0xB;
int8_t TRACK_12 = 0xC;
int8_t TRACK_13 = 0xD;
int8_t TRACK_14 = 0xE;
int8_t TRACK_15 = 0xF;

// MP3 PLAYER CONTROL FUNCTION
void PLAY_SOUND(int TRACK_SELECT)
{ mp3.playWithFileName(folderName, TRACK_SELECT);
}

void setup() {
  delay(500); // TIME FOR MP3 PLAYER TO INITIALISE

  // SET PREDEFINED VOLUME
  mp3.setVolume(volume);

  // SET PINS TO OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZ, OUTPUT);
  pinMode(NSIND, OUTPUT);
  pinMode(OSIND, OUTPUT);
  pinMode(NSWW, OUTPUT);
  pinMode(OSWW, OUTPUT);
  pinMode(NSLB, OUTPUT);
  pinMode(OSLB, OUTPUT);
  pinMode(REV, OUTPUT);
  pinMode(CL, OUTPUT);
  pinMode(HB, OUTPUT);

  // IIC SLAVE RECEIVER FUNTION SETUP
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
}
void loop() {
  // Checks value of CV - Cmmand Value. 
  // TODO - CONVERT TO SWITCH 
  if (CV == PLAYSOUND_1) {
    PLAY_SOUND(DOORS_CLOSING);
  }

  if (CV == PLAYSOUND_2) {
    PLAY_SOUND(TRACK_2);
  }

  if (CV == PLAYSOUND_3) {
    PLAY_SOUND(TRACK_3);
  }

  if (CV == PLAYSOUND_4) {
    PLAY_SOUND(TRACK_4);
  }

  if (CV == PLAYSOUND_5) {
    PLAY_SOUND(TRACK_5);
  }

  if (CV == PLAYSOUND_6) {
    PLAY_SOUND(TRACK_6);
  }

  if (CV == PLAYSOUND_7) {
    PLAY_SOUND(TRACK_7);
  }

  if (CV == PLAYSOUND_8) {
    PLAY_SOUND(TRACK_8);
  }

  if (CV == PLAYSOUND_9) {
    PLAY_SOUND(TRACK_9);
  }

  if (CV == PLAYSOUND_10) {
    PLAY_SOUND(TRACK_10);
  }

  if (CV == PLAYSOUND_11) {
    PLAY_SOUND(TRACK_11);
  }

  if (CV == PLAYSOUND_12) {
    PLAY_SOUND(TRACK_12);
  }

  if (CV == PLAYSOUND_13) {
    PLAY_SOUND(TRACK_13);
  }

  if (CV == PLAYSOUND_14) {
    PLAY_SOUND(TRACK_14);
  }

  if (CV == PLAYSOUND_15) {
    PLAY_SOUND(TRACK_15);
  }

  if (CV == PLAYSOUND_20) {
    tone(BUZ, 1500);
    delay(50);
    noTone(BUZ);
    delay(50);
    tone(BUZ, 1500);
    delay(50);
    noTone(BUZ);
    delay(50);
    tone(BUZ, 1200);
    delay(100);
    noTone(BUZ);
  }

// Lighting
  if (CV == LCU_REVERSE) {
    CMDSTATE_REVERSE = true;
    REV_STATE = true;
  }

  if (CV == LCU_REVERSE_OFF) {
    CMDSTATE_REVERSE = false;
    REV_STATE = false;
  }

  if (CV == LCU_WIGWAG_2) {
    WIGWAG_COUNTER = 100;
//      CMDSTATE_WIGWAG2 = true;
    }
    if (CV == LCU_WIGWAG_1) {
      
      WIGWAG_COUNTER = 15;
    }

  if (CV == LCU_NSIND) {
    CMDSTATE_NSIND = true;
  }

  if (CV == LCU_NSIND_OFF) {
    CMDSTATE_NSIND = false;
  }

  if (CV == LCU_OSIND) {
    CMDSTATE_OSIND = true;
  }

  if (CV == LCU_OSIND_OFF) {
    CMDSTATE_OSIND = false;
  }

  if (CV == LCU_HEADLIGHTS) {
    CL_STATE = HIGH;
    NSLB_STATE = HIGH;
    OSLB_STATE = HIGH;
  }

  if (CV == LCU_HEADLIGHTS_OFF) {
    CL_STATE = LOW;
    NSLB_STATE = LOW;
    OSLB_STATE = LOW;
  }

  if (CV == LCU_HIGHBEAM) {
    HIGHBEAM_STATE = HIGH;
  }

  if (CV == LCU_HIGHBEAM_OFF) {
    HIGHBEAM_STATE = LOW;
  }

// Blink Lights
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;
   if (WIGWAG_COUNTER == 0) {
    if (CL_STATE == LOW) {
      NSLB_STATE = LOW;
      OSLB_STATE = LOW;
      NSWW_STATE = LOW;
      OSWW_STATE = LOW;
    } else {
      NSLB_STATE = HIGH;
      OSLB_STATE = HIGH;
      NSWW_STATE = LOW;
      OSWW_STATE = LOW;
    }
  } else if (WIGWAG_COUNTER >= 1 && WIGWAG_COUNTER <= 30) {
      if (CL_STATE == LOW) {
      NSLB_STATE = LOW;
      OSLB_STATE = LOW;
    } else {
      NSLB_STATE = HIGH;
      OSLB_STATE = HIGH;
    }
    

    if (NSWW_STATE == LOW ) {
      NSWW_STATE = HIGH;
      OSWW_STATE = LOW;
      WIGWAG_COUNTER--;
    } else {
      NSWW_STATE = LOW;
      OSWW_STATE = HIGH;

    }
    }
   else if (WIGWAG_COUNTER >=31) {
      if (NSWW_STATE == LOW) {
          NSWW_STATE = HIGH;
          OSWW_STATE = LOW;
          NSLB_STATE = LOW;
          OSLB_STATE = HIGH;
          WIGWAG_COUNTER = 100;
        } else {
          NSWW_STATE = LOW;
          OSWW_STATE = HIGH;
          NSLB_STATE = HIGH;
          OSLB_STATE = LOW;
        }

      }
  
   
      if (CMDSTATE_REVERSE == true) {
      if (BUZ_STATE == false) {
          BUZ_STATE = true;
        } else {
          BUZ_STATE = false;
        }
      } else {
        BUZ_STATE = false;
      }

      if (CMDSTATE_NSIND == true) {
      if (NSIND_STATE == LOW) {
          NSIND_STATE = HIGH;
        } else {
          NSIND_STATE = LOW;
        }
      } else {
        NSIND_STATE = LOW;
      }
      if (CMDSTATE_OSIND == true) {
      if (OSIND_STATE == LOW) {
          OSIND_STATE = HIGH;
        } else {
          OSIND_STATE = LOW;
        }
      } else {
        OSIND_STATE = LOW;
      }
    
    
    if (BUZ_STATE == true) {
      tone(BUZ, 1800);
    } else {
      noTone(BUZ);
    }
  }
  // Write Values to pins
    digitalWrite(NSIND, NSIND_STATE);
    digitalWrite(OSIND, OSIND_STATE);
    digitalWrite(NSWW, NSWW_STATE);
    digitalWrite(OSWW, OSWW_STATE);
    digitalWrite(NSLB, NSLB_STATE);
    digitalWrite(OSLB, OSLB_STATE);
    digitalWrite(REV, REV_STATE);
    digitalWrite(CL, CL_STATE);
    digitalWrite(HB, HIGHBEAM_STATE);

  }
