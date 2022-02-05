#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "eyes.h"

int PIN_SER = 8;
int PIN_LATCH = 9;
int PIN_CLK = 10;

byte column[8];
byte zero[8];

/**
 * @brief
 * 初期化
 */
void eyes_init()
{
  pinMode(PIN_SER, OUTPUT);
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);

  Serial.begin(9600);
}

/**
 * 8文字列（01010101など）を1バイトに
 */
byte getByte(String target)
{
  Serial.print(target);
  Serial.print(':');
  byte result = 0;
  for (int i = 0; i < 8; i++)
  {
    if (target.substring(i, i + 1) == "1")
    {
      result += 1 << (8 - i - 1);
    }
  }
  char s[2];
  sprintf(s, "%02X", result);
  Serial.println(s);
  return result;
}

/**
 * 64 string '1000000001000000000000000000000000000000000000000000000000000000'
 * 8文字づつ区切ってByteに変換
 */
void setBytes(String target)
{
  for (int i = 0; i < 8; i++)
  {
    column[i] = getByte(target.substring(8 * i, 8 * i + 8));
  }
  return;
}

/**
 * ランダムに64bitを生成
 */
void setRandomBytes()
{
  for (int i = 0; i < 8; i++)
  {
    column[i] = (byte)random(0, 256);
    char s[2];
    sprintf(s, "%02X", column[i]);
    if (i == 7)
    {
      Serial.println(s);
    }
    else
    {
      Serial.print(s);
    }
  }
  return;
}

/**
 * @brief
 * 右に1ドットシフト
 *
 * @param isRight 右方向
 */
void rowShift(bool isRight)
{
  int direction = 1;

  if (!isRight)
  {
    for (int i = 0; i < 8; i++)
    {
      column[i] = column[i] >> direction;
    }
  }
  else
  {
    for (int i = 0; i < 8; i++)
    {
      column[i] = column[i] << direction;
    }
  }

  return;
}

/**
 * @brief
 * 下にシフト
 *
 * @param isDown
 */
void columnShift(bool isDown)
{
  if (isDown)
  {
    for (int i = 6; i >= 0; i--)
    {
      column[i + 1] = column[i];
    }
    column[0] = 0;
  }
  else
  {
    for (int i = 0; i <= 6; i++)
    {
      column[i] = column[i + 1];
    }
    column[7] = 0;
  }

  return;
}

/**
 * ライトオン
 */
void lightOn()
{
  for (int i = 0; i < 8; i++)
  {
    byte Row = 0;
    if (column[i] > 0)
    {
      Row = 1 << (8 - i - 1);
    }

    digitalWrite(PIN_LATCH, LOW);
    shiftOut(PIN_SER, PIN_CLK, LSBFIRST, ~Row);
    shiftOut(PIN_SER, PIN_CLK, LSBFIRST, column[i]);
    digitalWrite(PIN_LATCH, HIGH);
  }
}

/**
 * ライトオフ
 */
void lightOff()
{
  for (int i = 0; i < 8; i++)
  {
    byte Row = 0;
    if (zero[i] > 0)
    {
      Row = 1 << (8 - i - 1);
    }

    digitalWrite(PIN_LATCH, LOW);
    shiftOut(PIN_SER, PIN_CLK, LSBFIRST, ~Row);
    shiftOut(PIN_SER, PIN_CLK, LSBFIRST, zero[i]);
    digitalWrite(PIN_LATCH, HIGH);
  }
}

/**
 * 待機時間までライトオン
 */
void lightOnWait(float seconds)
{
  long endTime = millis() + seconds * 1000;
  while (millis() < endTime)
    lightOn();
}