#include <SoftwareSerial.h>
const int OUT0=13;
const int OUT1=6;
const int OUT2=2;
const int OUT3=3;
const int OUT4=4;
const int OUT5=5;
const int inp0=A0;
const int inp1=A1;
const int inp2=A2;
const int inp3=A3;
const int inp4=A4;
const int inp5=A5;
const int inp6=0;
const int led1=7;
const int led2=8;
const int led3=9;
int o=0;   //开关机控制
int a=0;  
int b=0;
int c=0;
int m=0;
int l=0;
int Vol=120;
SoftwareSerial midiSerial(10,11);// Control Chip Select Pin (for accessing SPI Control/Status registers
#define VS_RESET  12 //Reset is active low
#define MaxVol 127
#define MinVol 0


void sendMIDI(byte data)
{
    midiSerial.write(data);
}

void talkMIDI(byte cmd, byte data1, byte data2) {
  sendMIDI(cmd);
  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0 || (cmd & 0xF0) >= 0xE0) {
    sendMIDI(data1);
    sendMIDI(data2);
  } else {
    sendMIDI(data1);
  }
}

void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}


void soundadd(){
            Vol += 10;
            if (Vol > MaxVol) Vol = MaxVol;
            l=0;
            delay(100);
  }
void soundcut(){
   Vol -= 10;
            if (Vol < MinVol) Vol = MinVol;
            l=0;
            delay(100);
  }
void soundshutup(int a,int b,int c){
  int n=30;//初始音调
  if(a) while(n>=0){soundoutput(1,n);n-=5;delay(200);}
  else if(b) while(n>=0){soundoutput(2,n);n-=5;delay(200);}
  else if(c) while(n>=0){soundoutput(3,n);n-=5;delay(200);}
  else  while(n>=0){soundoutput(1,n);n-=5;delay(200);a=1;}
  }
void soundstarup(int a,int b,int c){
  int n=0;//初始音调
  if(a) while(n<=30){soundoutput(1,n);n+=5;delay(200);}
  else if(b) while(n<=30){soundoutput(2,n);n+=5;delay(200);}
  else if(c) while(n<=30){soundoutput(3,n);n+=5;delay(200);}
  else while(n<=30){soundoutput(1,n);n+=5;delay(200);a=1;}
  }
void soundoutput(int d,int n)
{
    Serial.println(n);
  if(!l){
    talkMIDI(0xB0, 0x07, Vol);// put your main code here, to run repeatedly:
  talkMIDI(0xB0, 0, 0x00);
  l=1;
  }
  if(d=1&&m!=2) {
    talkMIDI(0xC0, 3, 0);
    }
  if(d=2&&m!=2) {talkMIDI(0xC0, 41, 0);m=2;}
  if(d=3&&m!=3) {talkMIDI(0xC0, 32, 0);m=3;}
  noteOn(0,30+n, 127);
}

void pino(){

  digitalWrite(OUT3,LOW);
  if(analogRead(inp0)<900) soundoutput(1,14);
  if(analogRead(inp1)<900) soundoutput(1,16);
  if(analogRead(inp2)<900) soundoutput(1,18);
  if(analogRead(inp3)<900) soundoutput(1,20);
  if(analogRead(inp4)<900) soundoutput(1,22);
  if(!digitalRead(inp5)) soundoutput(1,24);
  if(!digitalRead(inp6)) soundoutput(1,26);
  digitalWrite(OUT3,HIGH);
  
  digitalWrite(OUT4,LOW);
  if(analogRead(inp0)<900) soundoutput(1,15);
  if(analogRead(inp1)<900) soundoutput(1,17);
  if(analogRead(inp2)<900) soundoutput(1,19);
  if(analogRead(inp3)<900) soundoutput(1,21);
  if(analogRead(inp4)<900) soundoutput(1,23);
  if(!digitalRead(inp5)) soundoutput(1,25);
  if(!digitalRead(inp6)) soundoutput(1,27);
  digitalWrite(OUT4,HIGH);
  
  digitalWrite(OUT5,LOW);
  if(analogRead(inp0)<900) soundoutput(1,28);
  if(analogRead(inp1)<900) soundoutput(1,30);
  if(analogRead(inp2)<900) soundoutput(1,32);
  if(analogRead(inp3)<900) soundoutput(1,33);
  if(analogRead(inp4)<900) soundoutput(1,34);
  if(!digitalRead(inp5)) soundoutput(1,35);
  if(!digitalRead(inp6)) soundoutput(1,36);
  digitalWrite(OUT5,HIGH);
  
  digitalWrite(OUT2,LOW);
  if(analogRead(inp5)<650) soundoutput(1,29);
  if(!digitalRead(inp6)) soundoutput(1,31);
  digitalWrite(OUT2,HIGH);
  }
  
void guitar(){
  byte a=0,b=0,c=0,d=0,e=0;
  digitalWrite(OUT2,LOW);
  if(analogRead(inp0)<900) a=0;
  if(analogRead(inp1)<900) b=2;
  if(analogRead(inp2)<900) c=4;
  if(analogRead(inp3)<900) d=6;
  if(!digitalRead(inp4)) e=8;
  digitalWrite(OUT2,HIGH);
  digitalWrite(OUT1,HIGH);
  if(!digitalRead(inp3)) soundoutput(2,14+a+b+c+d+e);
  if(!digitalRead(inp4)) soundoutput(2,24+a+b+c+d+e);
  if(!digitalRead(inp5)) soundoutput(2,34+a+b+c+d+e);
  if(!digitalRead(inp6)) soundoutput(2,44+a+b+c+d+e);
  digitalWrite(OUT1,LOW);
  }
  
void violin(){
  byte a=0,b=0,c=0,d=0,e=0;
  digitalWrite(OUT2,LOW);
  if(analogRead(inp0)<900) a=0;
  if(analogRead(inp1)<900) b=2;
  if(analogRead(inp2)<900) c=4;
  if(analogRead(inp3)<900) d=6;
  if(!digitalRead(inp4)) e=8;
  digitalWrite(OUT2,HIGH);
  digitalWrite(OUT1,HIGH);
  if(!digitalRead(inp3)) soundoutput(2,14+a+b+c+d+e);
  if(!digitalRead(inp4)) soundoutput(2,24+a+b+c+d+e);
  if(!digitalRead(inp5)) soundoutput(2,34+a+b+c+d+e);
  if(!digitalRead(inp6)) soundoutput(2,44+a+b+c+d+e);
  digitalWrite(OUT1,LOW);
  }


void setup() {
  //Serial.begin(57600); //Use serial for debugging 
  //Serial.println("\n******\n");
  //Serial.println("MP3 Shield Example");

  pinMode(OUT0,OUTPUT);
  pinMode(OUT1,OUTPUT);
  pinMode(OUT2,OUTPUT);
  pinMode(OUT3,OUTPUT);
  pinMode(OUT4,OUTPUT);
  pinMode(OUT5,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(inp0,INPUT_PULLUP);
  pinMode(inp1,INPUT_PULLUP);
  pinMode(inp2,INPUT_PULLUP);
  pinMode(inp3,INPUT_PULLUP);
  pinMode(inp4,INPUT_PULLUP);
  pinMode(inp5,INPUT_PULLUP);
  pinMode(inp6,INPUT_PULLUP);
  digitalWrite(OUT0,HIGH);
  digitalWrite(OUT1,LOW);
  digitalWrite(OUT2,HIGH);
  digitalWrite(OUT3,HIGH);
  digitalWrite(OUT4,HIGH);
  digitalWrite(OUT5,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  
 midiSerial.begin(31250);
pinMode(VS_RESET, OUTPUT);

  //Initialize VS1053 chip 
  digitalWrite(VS_RESET, LOW); //Put VS1053 into hardware reset

  delayMicroseconds(1);
  digitalWrite(VS_RESET, HIGH); //Bring up VS1053
}


void loop() {
    //Serial.println(o);
  if(!o){                  //关机状态
    delay(1000);
    digitalWrite(OUT0,LOW);
    if(analogRead(inp0)<600){
  
      delay(1000);

      if(analogRead(inp0)<600) {o=1;soundstarup(a,b,c);}
    }
    digitalWrite(OUT0,HIGH);
  }
  else{
    digitalWrite(OUT0,LOW);
    if(!digitalRead(inp1))  soundadd();//音量调节
    if(!digitalRead(inp2))   soundcut();//音量调节
    digitalWrite(OUT0,HIGH);
    digitalWrite(OUT1,HIGH);
    if(!digitalRead(inp0))  {a=1;b=0;c=0;digitalWrite(led1,LOW);digitalWrite(led2,HIGH);digitalWrite(led3,HIGH);} //打开a模式
    else if(!digitalRead(inp1))   {a=0;b=1;c=0;digitalWrite(led2,LOW);digitalWrite(led1,HIGH);digitalWrite(led3,HIGH);}  //打开b模式
    else if(!digitalRead(inp2))   {a=0;b=0;c=1;digitalWrite(led3,LOW);digitalWrite(led2,HIGH);digitalWrite(led1,HIGH);}  //打开c模式
    digitalWrite(OUT1,LOW);     //状态读取完毕 
    if(a) pino();
    else if(b) violin();
    else if(c)guitar();
    else {a=1;digitalWrite(led1,LOW);digitalWrite(led2,HIGH);digitalWrite(led3,HIGH);pino;}
    //Serial.println(a);
    //Serial.println(b);
    //Serial.println(c);
    digitalWrite(OUT0,LOW);
    if(analogRead(inp0)<600) {delay(1000);if(analogRead(inp0)<600){o=0;soundshutup(a,b,c);digitalWrite(led3,HIGH);digitalWrite(led2,HIGH);digitalWrite(led1,HIGH);}} //按关机键关机
    digitalWrite(OUT0,HIGH);
  }
  

}
