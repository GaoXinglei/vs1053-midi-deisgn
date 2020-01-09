---
Description: This is the vs1053 use midi model with arduino.
---
# VS1053 模块开启midi 模式并且链接arduino nano进行电子琴设计。
# 引脚定义
OUT0=13;/r
OUT1=6;
OUT2=2;
OUT3=3;
OUT4=4;
OUT5=5;
inp0=A0;
inp1=A1;
inp2=A2;
inp3=A3;
inp4=A4;
inp5=A5;
inp6=0;
六个输出 七个输入作为按钮的扫描 从而链接了36个按键以及一个开关和三个触摸开关

SoftwareSerial midiSerial(10,11);// Control Chip Select Pin (for accessing SPI Control/Status registers
#define VS_RESET  12 
10 11 12三个作为VS1053的通讯端口
