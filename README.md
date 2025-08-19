# IoT-Based Automatic Inhalation Ventilator

## Project Overview
This project is an **Arduino-based automatic ventilator system** designed to simulate controlled breathing cycles. It uses **servo motors, sensor inputs, and an LCD display** to provide real-time monitoring and patient-specific ventilation settings. The system allows safe and adjustable ventilation suitable for educational and prototyping purposes.

## Key Features
- **Automated Ventilation:** Servo motor controls inhalation and exhalation cycles based on predefined breath parameters.
- **Adjustable Parameters:** Volume, pressure, and breath rate can be configured using potentiometers.
- **Real-Time Feedback:** A LiquidCrystal I2C display shows current settings and selected patient age group (Adult, Child, Infant).
- **Safety Mechanisms:**
  - Sensor-based current monitoring to detect abnormal operation.
  - Automatic halt and visual alerts via red/green LEDs.
- **IoT Integration Potential:** Can be extended with IoT modules for remote monitoring and logging.

## Hardware Components
- Arduino Uno
- Servo Motor
- LiquidCrystal I2C display
- Push buttons for start/stop and age selection
- LED indicators

## Software / Libraries
- Arduino IDE (C++)
- Servo.h
- LiquidCrystal_I2C.h

## How It Works
1. Connect hardware components according to the schematic.
2. Upload the Arduino code to the microcontroller.
3. Configure ventilation settings using potentiometers and buttons.
4. The ventilator executes inhalation/exhalation cycles automatically, updating the display and monitoring current.

## Applications
- Educational and research prototyping
- IoT-enabled healthcare device experiments
- Emergency ventilator system simulations

## Disclaimer
This project is intended for **educational and prototyping purposes only** and is **not a certified medical device**.
