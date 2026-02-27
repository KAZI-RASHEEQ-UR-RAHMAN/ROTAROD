# Author: Kazi Rasheeq -Ur- Rahman Niloy
# Department: Electrical & Electronic Engineering (MAK-18)
# University: Bangladesh Army International University of Science & Technology (BAIUST)

# Low-Cost Automated Rotarod Apparatus

## 🧪 Smart Rotarod System

A low-cost, microcontroller-based automated Rotarod apparatus built using:

- NEMA17 Stepper Motor  
- Dual Arduino Nano  
- Microstep Motor Driver  
- Custom Auto Time Cut-Off System  
- Push Button Interface  
- Buck Converter Power System  

This system is designed for motor coordination and balance testing in rodents, commonly used in neuroscience and biomedical experiments.

---

## 🎯 Project Objectives

- Develop a cost-effective alternative to commercial rotarod systems  
- Implement precise speed control using microstepping  
- Automatically detect fall events and stop timer  
- Provide user-friendly control using push buttons  
- Ensure stable power regulation using buck converter  

---

## ⚙️ Hardware Components

| Component | Purpose |
|------------|----------|
| NEMA17 Stepper Motor | Drives the rotating rod |
| Microstep Motor Driver (Black Type) | Controls motor precision |
| Arduino Nano (2 Units) | Motor control + Timer system |
| Push Buttons (5x) | Speed control, Start/Stop, Mode |
| Buck Converter | Voltage regulation |
| Metal/Plastic Roller | Rotating platform |
| Contact Plates (Self-made) | Fall detection system |
| Meterboard Plastic Sheet | Frame & structure |

---

## 🔌 System Architecture

### 🔹 Arduino 1
- Controls stepper motor speed  
- Handles microstepping  
- Reads push button inputs  

### 🔹 Arduino 2
- Manages timer  
- Detects fall using plate-contact system  
- Stops timer automatically when rodent falls  

---

## 🧠 Key Features

- ✔ Adjustable speed  
- ✔ Microstep precision control  
- ✔ Automatic fall detection  
- ✔ Real-time timer  
- ✔ Low-cost design  
- ✔ Modular architecture  
- ✔ Safe voltage regulation  

---

## 🛠 Working Principle

1. Motor rotates rod using NEMA17.  
2. Speed controlled via microstep driver.  
3. Timer starts when experiment begins.  
4. When rodent falls:
   - Two contact plates touch  
   - Signal sent to Arduino  
   - Timer automatically stops  
5. Data can be displayed or logged.  

---

## 📊 Applications

- Neuroscience research  
- Parkinson’s disease motor studies  
- Drug testing experiments  
- Motor coordination analysis  
- Biomedical lab experiments  

---

## 🔧 Future Improvements

- LCD display integration  
- Wireless data logging  
- Adjustable acceleration profile  
- SD card storage  
- GUI-based PC monitoring  

