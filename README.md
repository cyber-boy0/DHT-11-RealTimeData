# Real-Time Firebase Data Project

## Overview
This project demonstrates how to display real-time data from Firebase on a website. The data is collected using an ESP32 microcontroller with a DHT11 sensor and sent to Firebase. Additionally, the project includes a way to monitor Arduino's serial output.

## Features
- Real-time data updates using Firebase
- Web interface to display sensor data
- Connection with Arduino's serial monitor
- Uses ESP32 and DHT11 sensor for data collection

## Technologies Used
- **Hardware:** ESP32, DHT11 Sensor
- **Software:** Arduino IDE, Firebase, JavaScript (for web display)

## Installation and Setup
1. **Hardware Setup:**
   - Connect the DHT11 sensor to the ESP32.
   - Upload the firmware to the ESP32 using Arduino IDE.

2. **Firebase Setup:**
   - Create a Firebase project.
   - Configure Firebase Realtime Database.
   - Get the Firebase API key and update the ESP32 code.

3. **Website Setup:**
   - Develop a simple web page to retrieve and display data from Firebase.
   - Ensure the Firebase SDK is properly linked in your web project.

## Usage
- Power on the ESP32 and ensure it's connected to Wi-Fi.
- Data from the DHT11 sensor will be sent to Firebase.
- The website fetches data from Firebase and updates in real time.
- Monitor serial output using the Arduino IDE's Serial Monitor.

## Future Improvements
- Add support for more sensors.
- Improve the UI of the web interface.
- Implement authentication for Firebase access.

## Contributing
Contributions are welcome! Feel free to fork this repository and submit pull requests.

