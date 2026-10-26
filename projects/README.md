# Veritas Data Center Temp 1.0

A final-year Computer Science project exploring real-time environmental monitoring for a data-center environment. The prototype uses an ESP32 microcontroller and four DHT11 sensors to collect temperature and relative humidity, sends readings to Firebase Realtime Database, and presents sensor values through a web dashboard.

## Architecture
1. Four DHT11 sensors connect to an ESP32.
2. Firmware reads temperature and humidity from each sensor.
3. Valid readings are written to Firebase Realtime Database under `sensor1` through `sensor4`.
4. A web dashboard can read the stored values and display current temperatures.

## Technology
- ESP32 / Arduino C++
- DHT11 temperature and humidity sensors
- Firebase Realtime Database
- HTML, CSS, JavaScript

## Repository contents
- `cloud.ino` — sanitized example firmware. Credentials have been replaced with placeholders.
- `screenshots/` — selected interface screenshots from the original project files.

## Setup notes
1. Install the ESP32 board support package and the `DHT sensor library` and `Firebase ESP Client` libraries used by the original firmware.
2. Copy `cloud.ino` into your Arduino IDE project.
3. Replace `YOUR_WIFI_SSID`, `YOUR_WIFI_PASSWORD`, `YOUR_FIREBASE_API_KEY`, and the database URL with values from a private local configuration.
4. Configure Firebase Authentication and Realtime Database rules for your environment before connecting hardware.
5. Never commit Wi-Fi passwords, service credentials, private keys, or unrestricted database rules.

## Security and reproducibility
The source archive provided for review contained real-looking Wi-Fi and Firebase configuration values. Those values are not included in this portfolio copy. Firebase web API keys are not traditional server secrets, but should still be restricted appropriately and paired with secure Authentication and database rules. Rotate any credentials that were exposed in a public repository or shared archive.

## Scope
This is a portfolio presentation of an academic prototype, not a claim of production deployment. Confirm hardware wiring, database rules, and dashboard connectivity against your own setup before reuse.
