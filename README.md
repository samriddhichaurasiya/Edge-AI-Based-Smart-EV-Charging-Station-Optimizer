# Smart EV Charging Station

An IoT and Edge-AI powered multi-bay EV Charging Station management system built on ESP32 microcontrollers and integrated with ThingsBoard Cloud.

## 🚀 Features

- **Multi-Bay Management**: Modular control for individual charging bays (Bay 1, Bay 2, Bay 3).
- **Sensor Monitoring**:
  - Voltage & Current sensing for real-time power monitoring.
  - Temperature & Humidity monitoring via DHT22 sensor.
  - Plug-in / Plug-out detection buttons.
- **Visual Status Indication**: Tri-color LED system (Green, Yellow, Red) for bay status and health.
- **Relay Control**: Automatic and manual switching of charging load relays.
- **Edge AI & Smart Optimization**: Local inference on ESP32 to predict and optimize charging loads.
- **Cloud Connectivity**:
  - MQTT integration with ThingsBoard Cloud (`mqtt.thingsboard.cloud`).
  - Real-time telemetry streaming (Voltage, Current, Power, Temperature, Humidity, State).
  - RPC (Remote Procedure Call) support for remote control & manual override.
  - Real-time clock synchronization via NTP (`pool.ntp.org`).

## 📁 Project Structure

```
Smart EV Charging Station/
├── BAY1/
│   └── esp32_blink_BAY1/      # Bay 1 ESP32 firmware (PlatformIO)
├── BAY2/
│   └── esp32_blink_BAY2/      # Bay 2 ESP32 firmware (PlatformIO)
├── BAY3/
│   └── esp32_BAY3/            # Bay 3 ESP32 firmware (PlatformIO)
├── PlatformIO/
│   └── Projects/              # Additional development modules & prototypes
├── .gitignore                 # PlatformIO & build artifact ignore rules
└── README.md                  # Project documentation
```

## 🛠️ Hardware Requirements

- **Microcontroller**: ESP32 DevKit V1
- **Sensors**:
  - DHT22 (Temperature & Humidity)
  - Voltage Sensor (ADC)
  - Current Sensor (ADC)
- **Actuators & Indicators**:
  - Relay Module (Active HIGH / LOW)
  - Status LEDs (Green, Yellow, Red)
  - Push Buttons (Plug-in, Plug-out)

## 💻 Software & Frameworks

- [PlatformIO](https://platformio.org/) / Arduino Framework
- Libraries:
  - `PubSubClient` (MQTT Client)
  - `DHT sensor library` & `Adafruit Unified Sensor`
  - `ArduinoJson`

## ⚙️ Setup & Flashing

1. Install [VS Code](https://code.visualstudio.com/) and the **PlatformIO IDE** extension.
2. Open the desired bay folder (e.g., `BAY1/esp32_blink_BAY1`) in PlatformIO.
3. Configure your Wi-Fi credentials and ThingsBoard Device Access Token in `src/config.cpp` (or `include/config.h`).
4. Build and upload firmware to the ESP32 board.
