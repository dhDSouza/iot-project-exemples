#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int number1 = random(0,100);
int number2 = random(0,100);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);

}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Tentando conectar a rede: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConectado.");
  }

  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);
  
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if(x == 200){
    Serial.println("Update realizado com sucesso.");
  }
  else{
    Serial.println("Erro de requisição HTTP: " + String(x));
  }
  
  number1 = random(0,100);
  number2 = random(0,100);
  
  delay(20000);
}
