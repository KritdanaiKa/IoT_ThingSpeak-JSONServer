#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

float temperature;
float humidity;
DHT dht14(D4,DHT11);

const char*  writeKey = "E79LF445GCFAHY6G";
unsigned long channelID = 2337703;
unsigned long timeDelay = 15000;

WiFiClient client;

void init_wifi(String ssid, String password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial. print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(){
  Serial.begin(9600);
  init_wifi("Miss Shadopay","krittscabello");
  dht14.begin();
  temperature = 0;
  humidity = 0;
  ThingSpeak.begin(client);
}

void getSensor(){
  humidity = (dht14.readHumidity());
  temperature = (dht14.readTemperature());
  ThingSpeak.setField(1, humidity);
  ThingSpeak.setField(2, temperature);
}

void loop(){
  getSensor();
  int x = ThingSpeak.writeFields(channelID, writeKey);
  if(x == 200) {
    Serial.println("sent humidity and temperature to ThingSpeak");
  } else {
    Serial.println("Problem sending to ThingSpeak");
  }
  delay(timeDelay);
}