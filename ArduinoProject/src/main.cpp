#include <Arduino.h>
#include <SD.h>
#include <dht11.h>
#include <SPI.h>
#include <ds1302.h>

dht11 sensor;

int wait_time = 1;

void SetTime();
void Wait();
void WriteData();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  DS1302_Init();
  SetTime();
  pinMode(13, OUTPUT);
  while (!SD.begin(4, 11, 12, 10))
  {
    Serial.println("初始化失败");
    digitalWrite(13, HIGH);
  }
  digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  WriteData();
  Wait();
}

void SetTime()
{
  DS1302_ON_OFF(0);     //关闭振荡
  DS1302Buffer.Year=0;
  DS1302Buffer.Month=0;
  DS1302Buffer.Day=0;
  DS1302Buffer.Week=0;
  DS1302Buffer.Hour=0;
  DS1302Buffer.Minute=0;
  DS1302Buffer.Second=0;
  DS1302_SetTime( 0x8c , DS1302Buffer.Year );
  DS1302_SetTime( 0x88 , DS1302Buffer.Month );
  DS1302_SetTime( 0x86 , DS1302Buffer.Day );
  DS1302_SetTime( 0x8a , DS1302Buffer.Week );
  DS1302_SetTime( 0x84 , DS1302Buffer.Hour );
  DS1302_SetTime( 0x82 , DS1302Buffer.Minute );
  DS1302_SetTime( 0x80 , DS1302Buffer.Second );
  DS1302_ON_OFF(1);
}

void Wait()
{
  SetTime();
  while (true)
  {
    DS1302_GetTime(&DS1302Buffer);
    if (DS1302Buffer.Minute == wait_time)
    {
      return;
    }
    else
    {
      delay(1000);
    }
  }
}

void WriteData()
{
  File data = SD.open("data.txt", FILE_WRITE);
  sensor.read(8);
  data.print(sensor.temperature);
  data.print(",");
  data.println(sensor.humidity);
  data.close();
}
