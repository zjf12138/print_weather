#include <DFRobot_GDL.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "black_1.h"
#include "black_2.h"
#include "black_3.h"
#include "black_4.h"
#include "black_5.h"
#include "black_6.h"
#include "qingwa1.h"
#include "qingwa2.h"
#include "qingwa3.h"
#include "qingwa4.h"
#include "qingwa5.h"
#include "qingwa6.h"
HTTPClient http;

const char* ssid="dfrobotOffice";
const char* password="dfrobot2011";
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 28800;
const int daylightOffset_sec = 0;
DynamicJsonDocument doc(1024);
DynamicJsonDocument doc1(1024);

#define TFT_DC  D2
#define TFT_CS  D6
#define TFT_RST D3
#define PICNUMBER 6

uint8_t randNumber;
uint16_t color = 0x00FF;
unsigned long previousMillis = 0;
String weekDays[]={"周日", "周一", "周二","周三", "周四", "周五", "周六"};


DFRobot_ST7789_240x240_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);


//打印输出所在地的时间函数
void printLocalTime(){
 struct tm timeinfo;
 if(!getLocalTime(&timeinfo)){
   Serial.println("Failed to obtian time");
   return ;
 }
}



//每隔多少秒系统时间 使用一次的函数
boolean doDelayMillisTime(long interval , boolean state) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    state = !state;
  }
  return state;
}


//产生的随机数是几号 就播放几号的图片
uint8_t printfrog(uint8_t number){

     struct tm timeinfo;
     if(!getLocalTime(&timeinfo)){
     Serial.println("Failed to obtian time");
//   return ;
    }

    switch(number){
    case 0:
    screen.drawPIC(/*x=*/0,/*y=*/0,/*w=*/240,/*h=*/240,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_qingwa1);//显示的随机图片
    delay(2000);
    break;
    case 1:
    screen.drawPIC(/*x=*/0,/*y=*/0,/*w=*/240,/*h=*/240,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_qingwa2);
    delay(2000);
    break;
    case 2:
    screen.drawPIC(/*x=*/0,/*y=*/0,/*w=*/240,/*h=*/240,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_qingwa3);
    delay(2000);
    break;
    case 3:
    screen.drawPIC(/*x=*/0,/*y=*/0,/*w=*/240,/*h=*/240,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_qingwa4);
    delay(2000);
    break;
    case 4:
    screen.drawPIC(/*x=*/0,/*y=*/0,/*w=*/240,/*h=*/240,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_qingwa5);
    delay(2000);
    break;
    case 5:
    screen.drawPIC(/*x=*/0,/*y=*/0,/*w=*/240,/*h=*/240,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_qingwa6);
    delay(2000);
    break;
    }
    screen.fillScreen(COLOR_RGB565_BLACK);  //刷新一次屏幕
    screen.setFont(&simkaiFont72pt );
    screen.setCursor(/*x=*/6,/*y=*/0);
    screen.println(&timeinfo,"%H");
    screen.setCursor(/*x=*/6,/*y=*/55);
    screen.println(&timeinfo,"%M");
    
  }


void printLocalWeather(){
    http.begin("http://www.weather.com.cn/data/cityinfo/101270101.html");
    int httpCode = http.GET();
    if(httpCode == HTTP_CODE_OK){
      String pageData = http .getString();
      //Serial.println(pageData);
      deserializeJson(doc,pageData);
      JsonObject obj = doc.as<JsonObject>();
      String weatherInfo = obj["weatherinfo"];
      deserializeJson(doc1,weatherInfo);
      JsonObject obj1 = doc1.as<JsonObject>();
      String city = obj1["city"];
      String temp1 = obj1["temp1"];
      String temp2 = obj1["temp2"];
      String weather = obj1["weather"];
      String cityInfo = city;
      String tempInfo =temp1 + "~" + temp2;
      String cityWeatherinfo =weather;
      Serial.println("获得天气情况如下：");
      Serial.print(cityInfo);
      Serial.print(tempInfo);
      Serial.println(cityWeatherinfo);
      
      struct tm timeinfo;
      if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtian time");
      return ;
      }
      Serial.println(&timeinfo, "%F %R %u"); // 格式化输出




//每当有触摸发生就显示图片
   if(touchRead(4)<=20)
   {
    screen.fillScreen(COLOR_RGB565_BLACK);  
    Serial.println("摸到了");
    randNumber =random(PICNUMBER);
    Serial.println(randNumber);//随机数的打印
    printfrog(randNumber);
    
    screen.fillScreen(COLOR_RGB565_BLACK);  
    screen.setFont(&simkaiFont72pt );//Set the font to FreeMono12pt7b
    screen.setCursor(/*x=*/6,/*y=*/0);
    screen.println(&timeinfo,"%H");
    screen.setCursor(/*x=*/6,/*y=*/55);
    screen.println(&timeinfo,"%M");
    }
    else{
      Serial.println("没有摸到");
      }



  
  //每间隔20s刷新一次屏幕
  if (doDelayMillisTime(20000 , false) == true) {
  screen.fillScreen(COLOR_RGB565_BLACK);  
  
  screen.setFont(&simkaiFont72pt );//Set the font to FreeMono12pt7b
  screen.setCursor(/*x=*/15,/*y=*/0);
  screen.println(&timeinfo,"%H");
  screen.setCursor(/*x=*/15,/*y=*/55);
  screen.println(&timeinfo,"%M");
  }

  
//  screen.setTextSize(4);
  screen.setFont(&simkaiFont72pt );//Set the font to FreeMono12pt7b
  screen.setCursor(/*x=*/0,/*y=*/0);
  screen.setTextColor(COLOR_RGB565_LGRAY);
  screen.setTextWrap(true);



  screen.setFont(&simkaiFont48pt );//Set the font to FreeMono12pt7b
//  screen.setTextSize(2);
  screen.setCursor(/*x=*/124,/*y=*/0);
  screen.println(weekDays[timeinfo.tm_wday]);

    
  screen.setFont(&simkaiFont24pt );//设置字体大小 为24像素点大小
  screen.setCursor(/*x=*/130,/*y=*/70); //设置显示光标
  screen.println(cityWeatherinfo);//屏幕显示天气状况，如多云转晴类字样
  screen.drawPIC(/*x=*/125,/*y=*/200,/*w=*/24,/*h=*/24,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_black6);//屏幕显示位置图标


  screen.setFont(&simkaiFont36pt );//设置字体大小 为36像素点大小
  screen.setCursor(/*x=*/120,/*y=*/135);//设置显示光标
  screen.println(tempInfo);//屏幕显示温度信息
  screen.setCursor(/*x=*/204,/*y=*/135);
  screen.println("°");//显示温度的符号
  screen.setCursor(/*x=*/150,/*y=*/190);
  screen.println(cityInfo);//屏幕显示你所在城市的位置信息
  

  //旋转太空人的屏幕显示
  screen.drawPIC(/*x=*/0,/*y=*/124,/*w=*/124,/*h=*/124,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_black1);
  delay(100);
  screen.drawPIC(/*x=*/0,/*y=*/124,/*w=*/124,/*h=*/124,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_black2);
  delay(100);
  screen.drawPIC(/*x=*/0,/*y=*/124,/*w=*/124,/*h=*/124,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_black3);
  delay(100);
  screen.drawPIC(/*x=*/0,/*y=*/124,/*w=*/124,/*h=*/124,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_black4);
  delay(100);
  screen.drawPIC(/*x=*/0,/*y=*/124,/*w=*/124,/*h=*/124,/*bitmap gImage_Bitmap=*/( uint8_t*)gImage_black5);

  

    }else{
      Serial.println("GET ERR");
    }
    http.end();
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  screen.begin();

  Serial.printf("Connecting to %s",ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);


}

void loop() {

    if(WiFi.status() == WL_CONNECTED){
    printLocalWeather();  
  }else{
    Serial.println("WiFi  Disconnect");
   }
}
