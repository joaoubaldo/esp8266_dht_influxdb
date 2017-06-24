#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "DHT.h"

#define DHTPWRPIN D3
#define DHTPIN D4     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors
// #define USE_SERIAL

char buffer[128];

DHT dht(DHTPIN, DHTTYPE);
HTTPClient http;

void setup() {
    pinMode(DHTPWRPIN, OUTPUT);

    #ifdef USE_SERIAL
        Serial.begin(9600);
        Serial.setTimeout(2000);

        // Wait for serial to initialize.
        while(!Serial) {}
        Serial.println("Device Started");
    #endif

    digitalWrite(DHTPWRPIN, HIGH);
    dht.begin();

    WiFi.begin(WIFI_SSID, WIFI_PASSWD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    #ifdef USE_SERIAL
        Serial.println("WiFi connected");
    #endif
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    digitalWrite(DHTPWRPIN, LOW);

    if (isnan(h) || isnan(t) || isnan(f)) {
        #ifdef USE_SERIAL
            Serial.println("Failed to read from DHT");
        #endif
        ESP.deepSleep(5e6);
    }

    http.begin(INFLUXDB_URI);
    sprintf(buffer, "humidity%s value=%d.%02d", INFLUXDB_TAGS, (int)h, (int)(h*100)%100);
    http.POST(buffer);
    http.end();
    http.begin(INFLUXDB_URI);
    sprintf(buffer, "temperature%s value=%d.%02d", INFLUXDB_TAGS, (int)t, (int)(t*100)%100);
    http.POST(buffer);
    http.end();
    delay(1000);
    ESP.deepSleep(DEEPSLEEP); // 20e6 is 20 microseconds
}

void loop() {
}
