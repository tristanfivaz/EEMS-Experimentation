/*
  EEMSDataSend.h - Library for sending live sensor data to Bitpool streams.
  
  EEMSDataSend constructor parameters:
  fingerprint - the ssl certificate Thumbprint of the api.bitpool.com site (with spaces evey 2 digits). (may need to be updated when it expires yearly)
  ssid - the ssid of the wifi network                                     
  password- the password of the wifi network
  streamKey - the stream key of the bitpool stream to send the data to
  authorizationToken - the api key used to access bitpool
  
  sendData Parameters:
  sensorValue - the value to send to the bitpool stream
*/
#include <EEMSDataSend.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#define DHTPIN D3 //select the pin used for the dht11
#define DHTTYPE DHT11 //specify the type of dht sensor here
DHT dht(DHTPIN, DHTTYPE);

int lightpin = A0;    //select the input pin for the light sensor
const int sleepTimeS = 900;   //15 minute sleep interval

EEMSDataSend eemsDataStream1("fingerprint", "ssid", "password", "streamKey", "Bitpool2 authorizationToken");   //stream credentials for temperature readings
EEMSDataSend eemsDataStream2("fingerprint", "ssid", "password", "streamKey", "Bitpool2 authorizationToken");   //stream credentials for humidity readings
EEMSDataSend eemsDataStream3("fingerprint", "ssid", "password", "streamKey", "Bitpool2 authorizationToken");   //stream credentials for light readings

void setup() {
  dht.begin();
  Serial.print("I'm Awake");
  delay(2000);

  DataSending();    //processes sensor reading and uploading to the EEMS

  Serial.println("Back to sleep");
  ESP.deepSleep(sleepTimeS * 1000000);

}

void loop(){}


void DataSending()
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float l = analogRead(lightpin);
  Serial.print(t);
  Serial.print(h);
  Serial.print(l);
  
  eemsDataStream1.sendData(t);
  eemsDataStream2.sendData(h);
  eemsDataStream3.sendData(l);
  }
