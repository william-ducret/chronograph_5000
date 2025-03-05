Abstract
---
This simple code creates a time measurement device (chronograph). It is aimed to measure the time duration between two displacement of an object.
The object must pass in front of a sensor to starts the timer, and the timer will stops when the object pass back in front of the sensor.


Features
---
- Waits for an object to be placed in front of the IR sensor (used as proximity sensor)
- Starts a timer when the object moves (away from the sensor)
- Stops the timer when the object pass back in front of the sensor
- Displays the the measured time when
- A button allows to reset the timer and to repeat a measurement
- SOON : A switch allows to switch between two modes : single lap or "x" lap (to be changed in the code) to compute the average time
- The LED can displays custom information, such as the selected mode, the status of the timer or simply to shows that the device is on


Hardware
---
- Arduino Micro
- IR sensor (TCRT5000)
- LED
- Button
- Switch
