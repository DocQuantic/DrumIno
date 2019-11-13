#include "MIDIUSB.h"

const int maxVelocity = 100;

const int hhTone = 42;
const int snareTone = 40;
const int kickTone = 41;

const int hhPin = A0;
const int snarePin = A1;
const int kickPin = A2;

int hhThreshold = 200;
int snareThreshold = 200;
int kickThreshold = 200;

int hhValue = 0;
int snareValue = 0;
int kickValue = 0;

int hhVelocity = 0;
int snareVelocity = 0;
int kickVelocity = 0;

bool hhActivated = false;
bool snareActivated = false;
bool kickActivated = false;

int hhMaxValue = 0;
int snareMaxValue = 0;
int kickMaxValue = 0;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  /*hhValue = analogRead(hhPin);
  if(hhValue>hhThreshold){
    hhActivated = true;
    if(hhValue>hhMaxValue){
      hhMaxValue = hhValue;
    }
    else if(hhActivated && hhValue<hhMaxValue){
      hhVelocity = mapMaxValueToVelocity(hhMaxValue);
      noteOn(0, hhTone, hhVelocity);
    }
  } 
  else if(hhActivated && hhValue<hhThreshold){
    hhMaxValue = 0;
    hhActivated = false;
    noteOff(0, hhTone, hhVelocity);
  }
  hhLastValue = hhValue;*/

  snareValue = analogRead(snarePin);
  if(snareValue>snareThreshold){
    snareActivated = true;
    if(snareValue>snareMaxValue){
      snareMaxValue = snareValue;
    }
    else if(snareValue<snareMaxValue){
      snareVelocity = mapMaxValueToVelocity(snareMaxValue);
      noteOn(0, snareTone, snareVelocity);
    }
  }
  else if(snareActivated && snareValue<snareThreshold){
    snareActivated = false;
    noteOff(0, snareTone, snareVelocity);
    snareMaxValue = 0;
  }

  /*kickValue = analogRead(kickPin);
  if(kickValue>kickThreshold){
    kickActivated = true;
    if(kickValue<kickLastValue-15){
      kickVelocity = mapMaxValueToVelocity(kickMaxValue);
      noteOn(0, kickTone, kickVelocity);
    }
  }
  if(kickActivated && kickValue<kickThreshold)
      kickActivated = false;
      noteOff(0, kickTone, kickVelocity);
    }
  }
  kickLastValue = kickValue;*/
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

int mapMaxValueToVelocity(int value){
  int velocity = value*maxVelocity/1023;
  return velocity;
}