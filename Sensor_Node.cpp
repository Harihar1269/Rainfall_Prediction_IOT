#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define SS 5
#define RST 14
#define DIO0 2
#define DHTPIN 4
#define DHTTYPE DHT11  

Adafruit_MPU6050 mpu;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    while (!Serial);
    
    Serial.println("Initializing Node 1 (LoRa Sender)...");

    SPI.begin(18, 19, 23, SS);
    LoRa.setPins(SS, RST, DIO0);

    if (!LoRa.begin(433E6)) {
        Serial.println("LoRa initialization failed!");
        while (1);
    }
    Serial.println("LoRa Initialized!");

    Wire.begin();
    if (!mpu.begin()) {
        Serial.println("MPU6050 not found! Check wiring.");
        while (1);
    }
    Serial.println("MPU6050 Initialized!");

    dht.begin();
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float ax = a.acceleration.x;
    float ay = a.acceleration.y;
    float az = a.acceleration.z;

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("DHT11 read failed!");
        return;
    }

    Serial.println("Sending LoRa packet...");
    LoRa.beginPacket();
    LoRa.print("2"); // Node ID 2
    LoRa.print(",");
    LoRa.print(temperature);
    LoRa.print(",");
    LoRa.print(humidity);
    LoRa.print(",");
    LoRa.print(ax);
    LoRa.print(",");
    LoRa.print(ay);
    LoRa.print(",");
    LoRa.print(az);
    LoRa.endPacket();

    Serial.println("Packet Sent!");
    delay(5000);
}
