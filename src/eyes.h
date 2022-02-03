#ifndef eyes_h
#define eyes_h

extern int PIN_SER;
extern int PIN_LATCH;
extern int PIN_CLK;

extern byte column[8];
extern byte zero[8];

extern byte getByte(String target);
extern void setBytes(String target);
extern void setRandomBytes();
extern void lightOn();
extern void lightOff();
extern void lightOnWait(float seconds);

#endif