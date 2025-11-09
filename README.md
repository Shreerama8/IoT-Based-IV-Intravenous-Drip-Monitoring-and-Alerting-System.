# IoT-Based-IV(Intravenous)-Drip-Monitoring-and-Alerting-System. 
### 🩺 Improving Patient Safety and Nursing Efficiency with IoT  

---

## 📘 Project Overview  
This project presents an **IoT-enabled intravenous (IV) drip monitoring and alerting system** that automates the process of IV fluid level detection in hospitals.  
It continuously measures the IV bottle weight using a **load cell and HX711 amplifier**, processes the data with an **ESP32 microcontroller**, and sends **real-time updates** to the **Blynk IoT Cloud** for remote monitoring.

When the IV level falls below a safe threshold (e.g., **25%**), the system:  
- Activates a **buzzer** and displays a warning on the **LCD**.  
- Moves a **servo motor** as a visual indicator.  
- Sends a **push notification** to the **Blynk mobile app** for timely refill alerts.  

This enhances **patient safety**, reduces **manual monitoring**, and prevents air or reverse flow in IV lines.

---

## ⚙️ Hardware Components  
| Component | Function |
|------------|-----------|
| **ESP32** | Main controller with Wi-Fi connectivity |
| **HX711 + Load Cell** | Measures IV bottle weight |
| **16×2 I²C LCD Display** | Displays real-time weight and volume |
| **Servo Motor** | Acts as flow indicator / alert arm |
| **Buzzer** | Audio alarm when IV is low |
| **Li-ion Batteries (7.4 V)** | Portable power source |
| **LM2596 Buck Converter** | Regulates voltage to 5 V |

---

## 🧠 Working Principle  
1. The **load cell** senses the IV bottle weight.  
2. The **HX711 module** converts the analog signal to digital.  
3. The **ESP32** calculates remaining volume and level percentage.  
4. Data is displayed on the **LCD** and uploaded to **Blynk Cloud**.  
5. If level < 25%, the system triggers **buzzer**, **servo**, and **Blynk alert**.  
6. When refilled, it automatically resets and resumes monitoring.

---

## 🌐 IoT & Cloud Integration  
- **Platform:** [Blynk IoT Cloud](https://blynk.cloud)  
- **Virtual Pins:**  
  - `V0` → IV bottle weight (grams)  
  - `V1` → IV level percentage  
- **Event Name:** `iv_alert` → sends push notification to the mobile app  

---

## 🧩 Circuit Connections  

| Module | ESP32 Pin |
|---------|------------|
| HX711 DOUT | GPIO 19 |
| HX711 SCK | GPIO 18 |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |
| Servo Signal | GPIO 14 |
| Buzzer | GPIO 23 |
| Power | 5 V / 3.3 V as required |

---

## 🪧 Block Diagram  
*(Add your block diagram image here)*  
![Block Diagram](images/block_diagram.png)

---

## 🖥️ System Workflow  
*(Add your circuit diagram here)*  
![Circuit Diagram](images/circuit_diagram.png)

---

## 📱 Blynk Mobile Dashboard  
*(Add screenshot of your Blynk dashboard here)*  
![Blynk Dashboard](images/blynk_dashboard.png)

---

## 🔋 Power Design  
- **Input:** Dual 18650 Li-ion cells (7.4 V nominal)  
- **Regulation:** LM2596 DC-DC Buck Converter → 5 V  
- **Servo:** Powered from dedicated 5 V rail (≥ 2 A)  
- **Common Ground:** All modules share same GND reference  

---

## 🚨 Key Features  
- 📶 **IoT Connectivity:** Real-time data via Blynk Cloud  
- ⚖️ **Accurate Monitoring:** Displays weight (g) & volume (mL)  
- 📱 **Instant Notifications:** Push alert when level < 25%  
- 🔊 **Local Alerts:** Buzzer + LCD warnings  
- ⚙️ **Smart Logic:** Auto-reset after refill  
- 🔋 **Portable Design:** Battery-powered, low cost, and efficient  

---

## 🚀 Future Enhancements  
- Integration of **drip-rate sensor** for flow measurement  
- **Central dashboard** for multi-bed hospital monitoring  
- **AI-based prediction** of IV depletion time  
- Battery level monitoring & low-power optimization  

---

## 🏁 Conclusion  
This IoT-based IV monitoring system automates a critical hospital process by ensuring timely IV replacement, enhancing patient safety, and reducing manual workload.  
By combining **embedded systems** with **IoT cloud connectivity**, it demonstrates how **technology can modernize healthcare** through real-time automation and intelligent alerting.

---

## 📚 Author  
**Developed by:** Shreerama T D  
**Platform:** Arduino IDE | ESP32 | Blynk IoT  
**Repository:** [IoT-Based-IV-Intravenous-Drip-Monitoring-and-Alerting-System](https://github.com/Shreerama8/IoT-Based-IV-Intravenous-Drip-Monitoring-and-Alerting-System)

---

## 🏷️ Tags  
`#IoT` `#ESP32` `#SmartHealthcare` `#BlynkIoT` `#EmbeddedSystems` `#Innovation` `#BiomedicalEngineering` `#Automation` `#IoTProjects`

