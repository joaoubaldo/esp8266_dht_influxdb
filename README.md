# Overview
ESP8266 DHT sensor probe that pushes readings to influxdb

## Build requirements
- PlatformIO  
- ESP8266 board (only tested with D1 Mini)

### Connections diagram

![Connections](/connections.png)


## Usage requirements
- influxdb accessible from the wifi network where the probe connects to

## Required build flags
- WIFI_SSID - wifi ssid
- WIFI_PASSWD - wifi password
- INFLUXDB_URI - influxdb write endpoint url, as in `http://INFLUXDB_HOST:INFLUXDB_PORT/write?db=INFLUXDB_DB`
- INFLUXDB_TAGS - influxdb tags to use for all readings. Use "" if none is needed. Be careful with length! Internal string buffer is 128 bytes.
- DEEPSLEEP - Time to deep sleep (usecs). 15e6 is 15 seconds

## Building
    PLATFORMIO_BUILD_FLAGS='-DWIFI_SSID=\"MY_SSID\" -DWIFI_PASSWD=\"MY_PASSWD\" -DINFLUXDB_URI=\"http://INFLUXDB_HOST:INFLUXDB_PORT/write?db=INFLUXDB_DB\" -DINFLUXDB_TAGS=\",KEY1=VALUE,KEY2=VALUE\" -DDEEPSLEEP="15e6"' platformio run

## Uploading
    PLATFORMIO_BUILD_FLAGS='-DWIFI_SSID=\"MY_SSID\" -DWIFI_PASSWD=\"MY_PASSWD\" -DINFLUXDB_URI=\"http://INFLUXDB_HOST:INFLUXDB_PORT/write?db=INFLUXDB_DB\" -DINFLUXDB_TAGS=\",KEY1=VALUE,KEY2=VALUE\" -DDEEPSLEEP="15e6"' platformio run -t upload
