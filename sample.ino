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
    // バイト配列生成
    setBytes("0010000001000100001000100000001000000010001000100100010000100000");
    // 待機時間まで光る
    lightOnWait(5);

    for (int i = 0; i < 8; i++)
    {
        columnShift(true);
        // 待機時間まで光る
        lightOnWait(0.1);
    }

    // バイト配列生成
    setBytes("0010000001000100001000100000001000000010001000100100010000100000");
    // 待機時間まで光る
    lightOnWait(1);

    for (int i = 0; i < 8; i++)
    {
        rowShift(true);
        // 待機時間まで光る
        lightOnWait(0.1);
    }

    while (true)
    {
        // ランダムに設定
        setRandomBytes();
        // 待機時間まで光る
        lightOnWait(0.5);
        int r = random(0, 4);
        switch (r)
        {
        case 0:
            Serial.println('v');
            break;
        case 1:
            Serial.println('^');
            break;
        case 2:
            Serial.println('>');
            break;
        case 3:
            Serial.println('<');
            break;
        }
        for (int i = 0; i < 8; i++)
        {
            switch (r)
            {
            case 0:
                //↓にシフト
                rowShift(true);
                break;
            case 1:
                //↑にシフト
                rowShift(false);
                break;
            case 2:
                //→にシフト
                columnShift(true);
                break;
            case 3:
                //←にシフト
                columnShift(false);
                break;
            }
            // 待機時間まで光る
            lightOnWait(0.2);
        }
    }
}

void _loop()
{
}

void loop()
{
    _loop();
}