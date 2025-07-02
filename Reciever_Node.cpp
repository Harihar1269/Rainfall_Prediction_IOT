#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define SS 5
#define RST 14
#define DIO0 2

const char* ssid = "Jackass";
const char* password = "12345667";
const char* serverURL1 = "https://rain-prediction-backend-1.onrender.com/upload";  // Node 1 API
const char* serverURL2 = "https://rain-prediction-backend-1.onrender.com/upload2"; // Node 2 API

void setup() {
    Serial.begin(115200);
    while (!Serial);
    
    Serial.println("Initializing LoRa Receiver...");

    SPI.begin(18, 19, 23, SS);
    LoRa.setPins(SS, RST, DIO0);

    if (!LoRa.begin(433E6)) {
        Serial.println("❌ LoRa initialization failed!");
        while (1);
    }
    Serial.println("✅ LoRa Initialized!");

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ WiFi connected!");
}

void sendToBackend(String jsonPayload, String serverURL) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonPayload);
    if (httpResponseCode > 0) {
        Serial.println("✅ Data sent to backend successfully!");
    } else {
        Serial.println("❌ Error sending data to backend.");
    }
    http.end();
}

void loop() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        Serial.print("📡 Received packet: ");
        
        String receivedData = "";
        while (LoRa.available()) {
            receivedData += (char)LoRa.read();
        }
        Serial.println(receivedData);

        // Extract values from received data
        int nodeID;
        float temperature, humidity, ax, ay, az;
        sscanf(receivedData.c_str(), "%d,%f,%f,%f,%f,%f", &nodeID, &temperature, &humidity, &ax, &ay, &az);

        // Prepare JSON payload
        String jsonPayload = "{";
        jsonPayload += "\"temperature\":" + String(temperature) + ",";
        jsonPayload += "\"humidity\":" + String(humidity) + ",";
        jsonPayload += "\"ax\":" + String(ax) + ",";
        jsonPayload += "\"ay\":" + String(ay) + ",";
        jsonPayload += "\"az\":" + String(az);
        jsonPayload += "}";

        // Send data to the correct backend URL
        if (nodeID == 1) {
            sendToBackend(jsonPayload, serverURL1);
        } else if (nodeID == 2) {
            sendToBackend(jsonPayload, serverURL2);
        } else {
            Serial.println("⚠ Unknown Node ID! Ignoring this data.");
        }
    }
}
