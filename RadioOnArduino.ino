#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_ST7789.h>
#include <Arduino.h> 

#define TFT_CS 11
#define TFT_DC 7 
#define TFT_RST 8 

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
 
int sum = 0;
int idx = 1;
// Массивы радиостанций
float mas[] = {89.5, 96.8, 102.5, 103.0, 104.7, 105.7, 106.2};
char* name_station[] = {"Megapolis FM", "Deti FM", "Camedi   Radio", "Radio    Shanson", "7 na semi holmah", "Russkoe  Radio", "Evropa   Plus"};
// массив для отправки I2C
byte arr[5]={0,0,0xB0,0x10,0x00};
 
void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP); //Кнопка
  pinMode(4, INPUT_PULLUP); //Кнопка
  tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
  tft.setRotation(2);                           // Поворот экрана  
  tft.fillScreen(ST77XX_BLACK);                 // Цвет заливки
  
}
void loop() {
  boolean button1 = !digitalRead(3);
  boolean button2 = !digitalRead(4);
  if (button1 == 1) {
    sum++;
    idx++;
    tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
    tft.setRotation(2);                           // Поворот экрана  
    tft.fillScreen(ST77XX_BLACK);                 // Цвет заливки
    delay(1000);
  }
  if (button2 == 1) {
    sum--;
    idx--;
    tft.init(240, 240, SPI_MODE2);                //  ST7789 дисплей 240x240 px  
    tft.setRotation(2);                           // Поворот экрана  
    tft.fillScreen(ST77XX_BLACK);                 // Цвет заливки
    delay(1000);
  }
  if (sum > 6) {
    sum = 0;
  }
  if (sum < 0) {
    sum = 6;
  }
  Wire.begin();
  // запуск радио
  unsigned int freqB = 4 * (mas[sum] * 1000000 + 225000) / 32768;
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
  tft.print(mas[sum]);
  tft.setCursor(155, 5);
  tft.setTextSize(4);                             
  tft.print("MHz");

  tft.setTextSize(4);
  tft.setCursor(3, 100);                            
  tft.print(name_station[sum]);

  tft.setTextSize(4);
  tft.setCursor(5, 210);                            
  tft.print("Chanal- ");
  tft.setTextSize(4);
  tft.setCursor(180, 210);
  tft.print(idx);
  
  Serial.println(mas[sum]);
  
}
