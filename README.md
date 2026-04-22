# LE-Arm Robotic Arm Control (Arduino)

This project explores custom control of the LE-Arm robotic system using Arduino. The original system was controlled through a default company application, which limited flexibility in movement and coordination.

To overcome these limitations, I connected the robotic arm to an Arduino microcontroller and implemented custom movement logic, enabling more dynamic and programmable control over joint behavior.

---

## Overview

The goal of this project was to improve movement flexibility, control precision, and system reliability by replacing preset actions with programmable motion sequences.

This project demonstrates how software-level control directly impacts the behavior of a multi-joint physical system.

---

## Key Work

- Implemented multi-joint servo control using Arduino  
- Developed movement sequences for pick-and-place style tasks  
- Tuned motion timing to reduce jerky or inconsistent behavior  
- Debugged hardware and control issues including wiring instability and angle misalignment  

---

## Improvements Over Default Control

- Coordinated multi-joint motion instead of isolated step-based actions  
- Smooth transitions between positions using gradual movement logic  
- Adjustable speed and timing parameters  
- Continuous motion patterns instead of fixed presets  

---

## Demonstration: Pick and Pour Sequence

This implementation includes a basic motion sequence simulating a pick-and-pour workflow:

- Move to source position  
- Grip object using controlled gripper movement  
- Lift and reposition to target location  
- Tilt wrist joint to simulate pouring action  
- Return to neutral state  

The sequence uses gradual servo transitions to improve stability and reduce abrupt movements.

---

## Challenges and Observations

- Maintaining consistent positioning required careful tuning of servo angles  
- Small timing variations significantly affected movement stability  
- Grip control required balancing between slippage and excessive force  
- Physical system behavior introduced variability not present in simulation  

---

## Demo

Short demo showing robotic arm control, movement sequencing, and tilt-based pouring behavior:

[Watch demo here](https://sofiauniversity-my.sharepoint.com/:v:/g/personal/santosh_bogati_sofia_edu/IQCmalUl8AzDQaL0s3DU5xB8AdFR2FUZURbhL_xJovdM6eY)

---

## System Setup

Physical setup of the LE-Arm robotic system connected to Arduino for custom control.

![LE-Arm Setup](images/le-arm-programming.png)

*LE-Arm robotic system connected to Arduino during testing and calibration*

---


## Additional Learning & Coursework

Alongside this project, I completed a structured set of hands-on exercises and experiments covering Arduino programming, robotics control, and system behavior.

This included:
- basic to intermediate Arduino programming  
- servo motor control and calibration  
- multi-joint movement experiments  
- debugging and hardware troubleshooting  
- iterative testing of robotic behavior  

For reference, I have organized my coursework, notes, and experimental recordings here:

[View full coursework and experiments](https://sofiauniversity-my.sharepoint.com/:f:/g/personal/santosh_bogati_sofia_edu/IgAF_oZXf4HhR7f3WGFfTg0mAcNXg8zfneXSlw9UcmuOXyo)
## Notes

This implementation focuses on control logic and movement sequencing.  
Achieving stable real-world pouring behavior depends on precise calibration, load handling, and hardware constraints.


---

## Technologies Used

- Arduino  
- Servo motors  
- C/C++ (Arduino environment)  
