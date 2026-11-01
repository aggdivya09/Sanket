# Sanket
### Intelligent Railway Worker Safety & Early Warning System

**SANKET** is a proposed railway worker safety system designed to provide timely warnings about approaching trains to railway track maintainers. It aims to address communication challenges in difficult railway environments through wireless communication, relay-assisted connectivity, intelligent warning logic, and wearable alerts.

The project focuses on exploring an additional layer of safety for railway maintenance workers, particularly in areas with sharp curves, hilly terrain, restricted visibility, and potential communication dead zones.

> **Tagline:** Detect the Approach. Deliver the Warning. Support the Response.

---

## 📌 Problem Statement

Railway track maintainers often work in environments where heavy machinery, environmental noise, restricted visibility, and difficult terrain can make it challenging to recognise an approaching train in time.

Wireless communication can also become unreliable in locations where hills, tunnels, sharp curves, or other obstacles interfere with radio signals.

These challenges highlight the need to explore additional warning mechanisms that can provide relevant information to workers near maintenance zones.

## 💡 Our Proposed Solution

SANKET proposes an integrated system combining train-location information, wireless communication, relay-assisted message forwarding, local warning logic, and wearable alerts.

The system is designed around four primary components:

### 1. 🚆 Train Box
- Obtains train-location information using GPS.
- Transmits relevant data wirelessly.
- Provides the train-side information used by the proposed warning system.

### 2. 📡 Relay Box
- Intended for suitable locations where direct wireless communication may be unreliable.
- Receives and retransmits messages to help extend communication coverage.
- Aims to reduce communication gaps in challenging terrain.

**Note:** Relay placement and communication reliability must be evaluated under real operating conditions. LoRa is also affected by terrain and radio obstructions.

### 3. 🛡️ Safety Box
- A portable unit positioned near the designated railway maintenance work zone.
- Receives relevant information from the communication network.
- Supports local warning decisions based on configured safety conditions.

### 4. ⌚ Wearable Safety Bracelet
- Provides audible warnings to workers.
- Can be designed to deliver progressively urgent alerts.
- Aims to help workers recognise potential danger and respond promptly.

---

## ⚙️ System Workflow

The proposed workflow is:

1. The Train Box obtains the train's GPS location.
2. Relevant information is transmitted through LoRa communication.
3. A Relay Box may forward the message where suitable relay-assisted communication is required.
4. The Safety Box evaluates the received information against the configured warning conditions.
5. The wearable bracelet activates when the warning criteria are met.
6. The system monitors message freshness and communication status to identify potential communication failures.

**Important:** Missing or outdated messages must never be interpreted as confirmation that the railway track is clear.

### System Architecture

```text
        TRAIN BOX
      (GPS + Data)
            |
            v
    LoRa Communication
            |
            v
        RELAY BOX
   (When required)
            |
            v
    LoRa Communication
            |
            v
        SAFETY BOX
  (Work-zone warning logic)
            |
            v
    WEARABLE BRACELET
      (Worker alerts)
            |
            v
  Worker responds to warning
  and moves to designated
        safe area
```

This diagram represents the proposed architecture. Actual message routing and relay placement will depend on the final implementation.

---

## 🔬 Accelerometer-Based Vibration Analysis

SANKET also explores the potential use of an accelerometer for identifying train-related vibrations.

An accelerometer measures acceleration along three axes: X, Y, and Z. These measurements can be analysed to study vibration patterns over time.

The proposed processing pipeline includes:

1. Collecting accelerometer readings.
2. Preprocessing the XYZ signals.
3. Applying Fast Fourier Transform (FFT) for frequency-domain analysis.
4. Investigating digital filters to reduce unwanted signal components.
5. Analysing vibration patterns from trains and other sources.
6. Evaluating whether vibration information can contribute to train-related event detection.

### Why is signal processing necessary?

Road vehicles, footsteps, and railway maintenance machinery can also produce vibrations. Their frequency patterns may overlap with train-related vibrations.

Therefore, FFT and filtering alone cannot guarantee reliable train identification. Real-world data collection, pattern analysis, and controlled validation are necessary.

The accelerometer is considered a potential supplementary detection method rather than a standalone guarantee of early warning.

---

## 📡 Communication Challenges

LoRa is a low-power, long-range wireless communication technology. However, its performance depends on factors such as terrain, antenna placement, obstructions, interference, and deployment conditions.

SANKET proposes to investigate the following approaches:

- **Relay-assisted communication:** Forwarding messages through suitably positioned intermediate nodes.
- **Communication monitoring:** Checking whether valid and recent messages are being received.
- **Fault alerts:** Providing a distinct warning when reliable communication cannot be confirmed.
- **Environmental protection:** Evaluating enclosure design and antenna connections for outdoor conditions.
- **Performance testing:** Measuring message delivery, communication range, and latency in representative environments.

These approaches require testing. The system does not assume that wireless connectivity will always be available.

---

## ✨ Key Features

- GPS-based train-location information.
- LoRa-based wireless communication.
- Proposed relay-assisted communication for challenging terrain.
- Portable work-zone Safety Box.
- Wearable audible warning mechanism.
- Proposed progressive alert levels.
- Communication-failure awareness.
- Accelerometer-based vibration analysis as a potential supplementary detection method.
- Modular architecture that can be evaluated and improved independently.

---

## 🆚 How Is SANKET Different?

SANKET is not based on the claim that LoRa or accelerometers are individually new technologies.

Its proposed contribution is the integration of:

- Relay-assisted communication.
- Work-zone-focused warning logic.
- Progressive wearable alerts.
- Communication-failure monitoring.
- Potential supplementary vibration analysis.

The project aims to investigate whether this integrated approach can address selected limitations encountered in railway maintenance environments.

Any comparison with existing systems must be supported by technical documentation and controlled testing.

---

## 🛠️ Proposed Technologies

| Component | Technology | Purpose |
|---|---|---|
| Train Box | GPS and microcontroller | Obtain and transmit train-location information |
| Wireless communication | LoRa | Transmit messages between system components |
| Relay Box | LoRa and microcontroller | Forward messages where required |
| Safety Box | Microcontroller and communication module | Evaluate received information and support warning decisions |
| Vibration analysis | Three-axis accelerometer | Collect vibration data for signal analysis |
| Signal processing | FFT and digital filtering | Analyse vibration characteristics |
| Wearable unit | Audible alert mechanism | Notify the worker of warning conditions |

The final hardware, software stack, and communication protocol will depend on prototype development and testing.

---

## 🎯 Project Objectives

1. Explore an additional warning mechanism for railway maintenance workers.
2. Investigate relay-assisted communication in challenging terrain.
3. Develop a work-zone-focused warning process.
4. Explore progressive wearable alerts.
5. Investigate accelerometer-based vibration analysis.
6. Monitor communication failures and outdated messages.
7. Evaluate the prototype through controlled experiments and performance testing.

---

## 🚧 Current Status

**Project stage:** Proposed design / prototype development.

The project concept includes the Train Box, Relay Box, Safety Box, wearable bracelet, and potential accelerometer-based vibration analysis.

Implementation status should be updated as individual components are developed and tested.

Planned validation areas include:

- Wireless communication reliability.
- Message delivery and latency.
- Relay-assisted coverage.
- Alert timing and accuracy.
- Vibration detection performance.
- Battery life and outdoor operation.
- Fail-safe behaviour during communication loss.

No operational safety performance is claimed until supported by appropriate test results.

---

## 🔮 Future Scope

- Develop and test a working hardware prototype.
- Evaluate wireless communication in different terrain conditions.
- Collect accelerometer data from trains and non-train vibration sources.
- Develop and validate vibration classification methods.
- Improve warning logic using train direction, speed, track geometry, and work-zone information.
- Evaluate battery performance and weather resistance.
- Conduct controlled trials with appropriate railway-authority involvement.
- Investigate emergency reporting capabilities, subject to implementation and safety validation.

---

## ⚠️ Safety Disclaimer

SANKET is a proposed research and development project. It is not a certified railway safety system.

It must not replace established railway protection procedures, authorised lookout arrangements, signalling systems, or other mandated safety measures.

Operational use would require extensive testing, formal safety engineering, and the necessary railway-authority approvals.

---

## 👥 Team SANKET — The Platypus

**Team Name:** The Platypus

**Project Name:** SANKET

**Project Title:** Intelligent Railway Worker Safety & Early Warning System

### Team Members

1. **Saurabh Rawat**
2. **Amit Padhan**
3. **Lavanya Joshi**
4. **Divya Agarwal**

---
