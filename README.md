# IoT Plant Environment Management System [PEMS]

An ESP8266-based IoT automation prototype designed for smart plant environment control using a responsive web dashboard and real-time relay management.

## Overview

PEMS (Plant Environment Management System) is an open-source IoT project that combines embedded systems, web technologies, and environmental automation into a single platform.

The system allows users to control plant lighting, water supply, and environmental activation devices directly from a browser over Wi-Fi using an ESP8266 NodeMCU.
## Features
1. Login-protected Web Dashboard
2. Dark / Light Mode UI
3. ESP8266 Async Web Server
4. Dual Plant Light Control
5. Water Supply Control
6. Air Humidifier Control
7. Buzzer Feedback System
8. Responsive Minimal UI
9. Local Network Browser Access
10. Real-time Relay Switching

### Hardware
1. ESP8266 NodeMCU
2. 4-Channel opto-isolated Relay Design
3. Active Buzzer
4. Wi-Fi Network

### Programming Languages
1. Arduino C++
2. HTML
3. CSS
4. JavaScript
5. ESPAsyncWebServer Library

# Android Application
To improve accessibility and user experience, a dedicated Android application was developed for the PEMS ecosystem. The mobile application allows users to:
1. Connect directly to the ESP8266 local server
2. Access the control dashboard without manually typing the IP address
3. Control environmental modules remotely through a simplified mobile interface
4. Improve usability for daily plant monitoring operations
The Android application acts as a lightweight remote controller for the IoT system over a local Wi-Fi network.

# Windows Desktop Application
A standalone Windows desktop application was also developed using Python for desktop-based monitoring and control.

### Desktop Application Features
1. Quick access to the ESP8266 dashboard
2. Simplified desktop interaction
3. Faster local device management
4. Lightweight executable (.exe) application
5. No browser dependency required

## Programs used
1. Python
2. GUI-based desktop interface
3. Executable packaging for Windows systems
The desktop application was designed to provide a more convenient control environment for long-term monitoring and testing purposes.

# Multi-Platform Ecosystem
PEMS now supports multiple control platforms:

| Platform | Function |
|---|---|
| Web Dashboard | Browser-based Control |
| Android App | Mobile Access |
| Windows Application | Desktop Monitoring |
| ESP8266 Server | Core IoT Controller |
This creates a flexible multi-platform IoT ecosystem for smart environmental management.

## ESP8266 NodeMCU Pinout
<img width="1920" height="1080" alt="ESP8266 PINOUT" src="https://github.com/user-attachments/assets/daea9ed2-2653-4520-b5db-50cbbf4182c7" />

## Circuit Schematic Diagram
<img width="3996" height="2250" alt="SCHEMATICS" src="https://github.com/user-attachments/assets/ac08b77e-e000-43af-92d2-158115cb7abf" />

## Top and Bottom Layer PCB Designing
<img width="1920" height="1080" alt="PCB 2D VIEW" src="https://github.com/user-attachments/assets/50187cda-036a-488f-aab8-d32bba6bf488" />


## PCB 2D View
<img width="1920" height="1080" alt="PCB 2D VIEW" src="https://github.com/user-attachments/assets/e3f70eeb-715e-4fac-b2eb-c3a42a9c298d" />


## USB to TTL Interface Header
<img width="4000" height="2250" alt="USB TO TTL" src="https://github.com/user-attachments/assets/28a78492-252b-4d3c-aa23-e2a58deb13c6" />

## Web UI in Desktop Browser
<img width="4000" height="2250" alt="WEB IP UI" src="https://github.com/user-attachments/assets/40cb26dc-bde4-4591-ac91-b86d5a1ef0f9" />

## Web UI Activation Dashboard in Desktop Browser
<img width="1920" height="1080" alt="WEB IP UI_ACTIVATION SYSTEM" src="https://github.com/user-attachments/assets/112df334-3c69-47f8-8d34-f0306d188244" />

## Windows App UI
<img width="4000" height="2250" alt="WINDOWS APP UI" src="https://github.com/user-attachments/assets/a6f970e1-1463-43ff-8ba0-ac75174eee10" />

## Android Mobile App UI
<img width="4045" height="2250" alt="MOBILE APP UI" src="https://github.com/user-attachments/assets/0e981ae1-bcd3-4376-9462-eb582b41bd87" />

## Web, PC, and Android App also in Black Theme by Toggle the Moon Icon
<img width="4000" height="2250" alt="WEB, PC and MOBILE APP black theme UI" src="https://github.com/user-attachments/assets/b63df10f-287c-4f90-bb09-632eb0e03061" />


# Future Expansion Goals
Planned future developments include:
1. Real-time sensor analytics
2. Cloud connectivity
3. MQTT communication
4. Notification system
5. AI-assisted automation
6. Historical environmental data logging
7. Cross-platform synchronization
8. OTA firmware updates
9. Smart scheduling system
10. Mobile push notifications

# Project Vision
The goal of PEMS is to evolve into a scalable smart environmental management ecosystem capable of integrating embedded systems, automation, responsive web technologies, desktop software, and mobile applications into a unified IoT platform.
