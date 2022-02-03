# これは何?

Kumanのキットでついていた8x8 LEDで遊んでみた記録

# 8 x8 LED

1588BSというものだった

↓こんなかんじにLEDが（物理的に）配置されている

| ↓アノード/カソード→ | Col 1 | Col 2 | Col 3 | Col 4 | Col 5 | Col 6 | Col 7 | Col 8 |
|-----------|-------|-------|-------|-------|-------|-------|-------|-------|
| Row 1     | ○     | ○     | ○     | ○     | ○     | ○     | ○     | ○     |
| Row 2     | ○     | ○     | ○     | ○     | ○     | ○     | ○     | ○     |
| Row 3     | ○     | ○     | ○     | ○     | ○     | ○     | ○     | ○     |
| Row 4     | ○     | ○     | ○     | ○     | ○     | ○     | ○     | ○     |
| Row 5     | ○     | ○     | ○     | ○     | ○     | ○     | ○     | ○     |
| Row 6     | ○     | ○     | ○     | ○     | ○     | ○     | ○     | ○     |
| Row 7     | ○     | ○     | ○     | ○     | ○     | ○     | ○     | ○     |
| Row 8     | ○     | ○     | ○     | ○     | ○     | ○     | ○     | ○     |

Pinは16本しかないので（厳密に）同時に光らせることができるのは、8個のLED

それを高速に行うことで見た目にはずっと光って見えるようにする（残像を利用した）方式


Pin配置は下記だった

|Row/Col|Pin No|
|-----|-----|
|Row 1|Pin 9|
|Row 2|Pin 14|
|Row 3|Pin 8|
|Row 4|Pin 12|
|Row 5|Pin 1|
|Row 6|Pin 7|
|Row 7|Pin 2|
|Row 8|Pin 5|
|Col 1|Pin 13|
|Col 2|Pin 3|
|Col 3|Pin 4|
|Col 4|Pin 10|
|Col 5|Pin 6|
|Col 6|Pin 11|
|Col 7|Pin 15|
|Col 8|Pin 16|

アノード側をHigh、カソード側をLowにするとそれに対応するLEDが点灯する

1行目(Row 1)の1列目を点灯する場合、

Pin 9 = High, Pin 13= Lowで点灯する（ハズ）

# 配線

Pinの数が多いので、節約のため、シフトレジスタを使用

74HC595（x 2）を準備した

カソード側に220Ωの抵抗を配置


# wsl + vscode + arduino 

↓WSL2でUSBシリアル↓

https://qiita.com/baggio/items/28c13ed8ac09fc7ebdf1

usbipd-win + カーネルのリコンパイル

違い  
→USBが /dev/ttyACM0だった

/dev/ttyACM0はroot:rootだった  
→sudo usermod -a -G root axt  
↑rootグループに参加した  

WSL2再起動のたびに下記必要そう?

```
sudo chmod a+rw /dev/ttyACM0
```

Serialにインテリセンス効かなかった↓下記で解決

https://github.com/microsoft/vscode-arduino/issues/808

