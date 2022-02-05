#ifndef eyes_h
#define eyes_h

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

extern void eyes_init();
extern void eyes_init(int ser, int latch, int clock);
extern byte getByte(String target);
extern void setBytes(String target);
extern void setRandomBytes();
extern void columnShift(bool isRight);
extern void rowShift(bool isDown);
extern void lightOn();
extern void lightOff();
extern void lightOnWait(float seconds);

#endif