#include <Arduino.h>
#include <WiFi.h>
#include <WiFiServer.h>

const char *ssid = "CMCC-35F1"; //你的网络名称
const char *password = "35F110!@"; //你的网络密码

WiFiServer wifiServer(11451);

void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //打印模块IP
  wifiServer.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = wifiServer.available();
  if (client) {
    Serial.println(">>>>>");
    while (client.connected()) {
      delay(50);
      while (client.available()>0) {
        char c = client.read();
        Serial.println(c);
        switch(c){
          case 'a':
            Serial.println("1");
            if(digitalRead(32)){
              digitalWrite(2,LOW);
              digitalWrite(32,LOW);
              client.println("off");
            }else{
              digitalWrite(2,HIGH);
              digitalWrite(32,HIGH);
              client.println("on");
            }
            break;
          case 'b':
            Serial.println("2");
            if(digitalRead(33)){
              digitalWrite(33,LOW);
              client.println("off");
            }else{
              digitalWrite(33,HIGH);
              client.println("on");
            }
            break;
          case 'c':
            Serial.println("3");
            if(digitalRead(25)){
              digitalWrite(25,LOW);
              client.println("off");
            }else{
              digitalWrite(25,HIGH);
              client.println("on");
            }
            break;
          case 'd':
            if(digitalRead(26)){
              digitalWrite(26,LOW);
              client.println("off");
            }else{
              digitalWrite(26,HIGH);
              client.println("on");
            }
            break;
          case 'e':
            if(digitalRead(27)){
              digitalWrite(27,LOW);
              client.println("off");
            }else{
              digitalWrite(27,HIGH);
              client.println("on");
            }
            break;
          case 'r':
            Serial.println("r");
            if(digitalRead(32)){
            client.println("1on\n");
            }else{
            client.println("1off\n");
            }
            if(digitalRead(33)){
            client.println("2on\n");
            }else{
            client.println("2off\n");
            }
            if(digitalRead(25)){
            client.println("3on\n");
            }else{
            client.println("3off\n");
            }
            if(digitalRead(26)){
            client.println("4on\n");
            }else{
            client.println("4off\n");
            }
            if(digitalRead(27)){
            client.println("5on\n");
            }else{
            client.println("5off\n");
            }
            break;
          default:
            break;
          }
          delay(50);
        }
      client.println("done\n");
      client.stop();
      Serial.println("+++++");
    } 
  }
}