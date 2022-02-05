#include "src/eyes.h"

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

void _delay(float seconds)
{
    long endTime = millis() + seconds * 1000;
    while (millis() < endTime)
        _loop();
}

void setup()
{
    eyes_init();
    for (int count = 0; count < 10; count++)
    {
        // バイト配列生成
        setBytes("0010000001000100001000100000001000000010001000100100010000100000");
        // 待機時間まで光る
        lightOnWait(1);
        // 消灯
        lightOff();
    }

    while (true)
    {
        // ランダムに光る
        setRandomBytes();
        lightOnWait(0.1);
    }
}

void _loop()
{
}

void loop()
{
    _loop();
}