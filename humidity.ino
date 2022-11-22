/* Hardware: NodeMCU and DHT11
*
*
*
*
*
*/
#define BLYNK_TEMPLATE_ID           "TMPLUBF7APzW"
#define BLYNK_DEVICE_NAME           "Quickstart Device"

#define BLYNK_PRINT Serial

 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
 

char auth[] = "G_C2xIhqfeOPOIli6NggxkuvyM3fem_x";

char ssid[] = "PyTorch";
/*char pass[] = "";
*/
 
#define DHTPIN 0          // D3
 

#define DHTTYPE DHT11     // DHT 11
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}
 
void setup()
{
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  timer.setInterval(500L, sendSensor);
}
void loop() {
  Blynk.run();
  timer.run();
}
