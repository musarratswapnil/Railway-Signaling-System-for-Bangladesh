# Smart Railway Traffic Control System for Bangladesh
This is a project for the course CSE3200: System Development Project

## Project Overview
This project involves the development of an automated railway signaling system prototype for Bangladesh Railway. The goal is to improve safety and operational efficiency by automating train detection, signaling, and track switching. The system uses ESP-32 microcontrollers, Arduino, DC-based track circuits, and servo motors to simulate a small-scale railway junction.

## Features
- Real-time train detection using DC-based track circuits on four tracks
- Automated signal control for Outer, Home, Starter, and Advanced Starter signals
- Servo motor-operated point machines for manual track switching
- Manual override for station master control
- Prototype designed as a cost-effective model representing Bangladesh Railway signaling logic

## Components
- ESP-32 Microcontroller as the central control unit
- Arduino Uno for power supply and auxiliary I/O control
- DC-based track circuits with infrared sensors for train presence detection
- Servo motors simulating point machines for track switching
- LED arrays representing railway signals
- Manual switches for point machine manual control

## System Workflow
1. Train enters a track segment; the track circuit detects occupancy.
2. ESP-32 processes occupancy data and updates signal states automatically.
3. Point machines operated manually by station master via servo motors for track switching.
4. Signal states reflect real-time track status, with manual intervention capability.
5. System resets signals and status once the train clears the track segment.

## Installation & Usage
- Upload the ESP-32 microcontroller code using Arduino IDE.
- Connect components (track circuits, servo motors, LEDs, switches) as per the circuit diagram.
- Power the system with a DC supply.
- Monitor system states through the serial interface; manually operate switches for track switching.

## Results
- Achieved 100% success rate in train detection, signal control, and servo motor synchronization during testing.
- Reduced human errors in train signaling via automation.
- Demonstrated practical, scalable model for smart railway signaling in Bangladesh.

## Limitations & Future Work
- Current prototype is limited to a small-scale four-track model.
- Track switching remains manual; plans to incorporate full automation.
- Future expansion to integrate real-time monitoring, analytics, and centralized control for larger railway networks.

## Acknowledgements
Special thanks to Dr. Muhammad Sheikh Sadi for his invaluable guidance and to the railway officers at Ishwardi Railway Station for their support during field visits.

## Contributors

- [Asif Akbar](https://github.com/AsifAkbar106)  
  Roll: 2007106

- [Shaeer Musarrat Swapnil](https://github.com/musarratswapnil)  
  Roll: 2007116

