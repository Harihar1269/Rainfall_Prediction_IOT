# 🌦️ IoT Weather Analytics System

This project is an end-to-end IoT-based weather monitoring and analytics system. It gathers environmental and motion data from remote sensor nodes and transmits them over **LoRa** to a central server, which then uploads and analyzes the data using a **Flask-based API** and **PostgreSQL** database.

---

## 📌 Project Overview

- 📡 **Sensor Nodes** (Node 1 & Node 2) collect:
  - 🌡️ Temperature  
  - 💧 Humidity  
  - 📈 Accelerometer data (x, y, z)

- 📶 Data is transmitted wirelessly using **LoRa**.

- 🌐 A **central receiver** connected to WiFi:
  - Parses incoming LoRa packets
  - Uploads the data to a **cloud-based API**

- 🧠 The **Flask backend**:
  - Stores the data in a **PostgreSQL database**
  - Provides REST API endpoints for real-time access and analytics

---

## 🔧 Key Technologies Used

- 🐍 **Python + Flask** – Web server for data upload and retrieval  
- 📡 **LoRa (SX1278)** – Long-range wireless communication  
- 🐘 **PostgreSQL** – Reliable and scalable database  
- 🌍 **WiFi** – For internet connectivity of the receiver node  
- 🌐 **Render.com** – Cloud hosting for the API backend  
- 🔓 **CORS-enabled API** – For cross-origin frontend or dashboard access

---

## 🚀 What the System Can Do

- ✅ Collect real-time environmental data  
- ✅ Upload it securely to a cloud database  
- ✅ Analyze and summarize the readings by day  
- ✅ Access the latest sensor data from anywhere  
- ✅ Differentiate data based on the sensor node ID  

---

## 🌍 Example Use Cases

- 🌧️ **Rainfall prediction** based on humidity and motion changes  
- 🏕️ **Remote environmental monitoring** in agriculture or wildlife zones  
- 🏫 **Educational IoT projects** for smart sensing and analytics  
- 🏠 **Home automation systems** for condition-based alerts  

---

## 🛡️ Future Enhancements (Ideas)

- 📲 Mobile/web dashboard for live graphing  
- 🔔 Alerts for extreme temperature or vibration  
- 🛰️ GPS integration for location-based readings  
- ☁️ Weather forecasting using AI models  
