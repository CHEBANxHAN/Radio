#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_ST7789.h>
#include <Arduino.h> 
#include <GyverEncoder.h>

#define TFT_CS 11
#define TFT_DC 7 
#define TFT_RST 8

#define CLK 5
#define DT 6
#define SW 9

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Encoder enc(CLK, DT, SW);
 
int sum = 0;
int idx = 1;
float val = 76.0;
boolean flag = true;
// массив для отправки I2C
byte arr[5]={0,0,0xB0,0x10,0x00};
 
void setup() {
  Serial.begin(9600);
  enc.setType(TYPE2);
  
  tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
  tft.setRotation(2);                           // Поворот экрана  
  tft.fillScreen(ST77XX_BLACK);                 // Цвет заливки
  
}
void loop() {
  enc.tick();
  if(enc.isClick()){
    flag = !flag;
  }
  if(enc.isTurn()){
    if (flag == true) {
      if(enc.isRight()){
        val += 1.0;
        tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
        tft.setRotation(2);                           // Поворот экрана  
        tft.fillScreen(ST77XX_BLACK);                // Цвет заливки
        delay(100);
      }
      if(enc.isLeft()) {
        val -= 1.0;
        tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
        tft.setRotation(2);                           // Поворот экрана  
        tft.fillScreen(ST77XX_BLACK);                // Цвет заливки
        delay(100);
      }
    }
    if (flag == false) {
      if(enc.isRight()) {
        val += 0.1;
        tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
        tft.setRotation(2);                           // Поворот экрана  
        tft.fillScreen(ST77XX_BLACK);                // Цвет заливки
        delay(100);
      }
      if(enc.isLeft()) {
        val -= 0.1;
        tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
        tft.setRotation(2);                           // Поворот экрана  
        tft.fillScreen(ST77XX_BLACK);                // Цвет заливки
        delay(100);
      }
    }
    if(enc.isRightH()){
        val += 10.0;
        tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
        tft.setRotation(2);                           // Поворот экрана  
        tft.fillScreen(ST77XX_BLACK);                 // Цвет заливки
        delay(100);
      }
      if(enc.isLeftH()) {
        val -= 10.0;
        tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
        tft.setRotation(2);                           // Поворот экрана  
        tft.fillScreen(ST77XX_BLACK);                // Цвет заливки
        delay(100);
      }
    Serial.println(val);
  }
  if (val <= 76.0) {
    val = 76.0;
  }
  if (val >= 108.0) {
    val = 108.0;
  }
  Wire.begin();
  // запуск радио
  unsigned int freqB = 4 * (val * 1000000 + 225000) / 32768;
  byte freqH = freqB >> 8;
  byte freqL = freqB & 0XFF;
  arr[0]= freqH;
  arr[1]= freqL;
  Wire.beginTransmission(0x60);
  for(int i=0;i<5;i++) {
    Wire.write(arr[i]);
  }
  Wire.endTransmission();

  //Вывод информации на дисплей
  tft.setTextSize(4);
  tft.setCursor(0, 5);                            
  tft.print("Radio On  Arduino");
  
  tft.setTextSize(4);
  tft.setCursor(0, 100);                            
  tft.print(val);
  tft.setCursor(155, 100);
  tft.setTextSize(4);                             
  tft.print("MHz");
  
  
}
