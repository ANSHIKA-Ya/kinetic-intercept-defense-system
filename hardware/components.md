\# Hardware Components



\## Main Controller



\### Arduino Due

The Arduino Due is used as the central controller of the prototype. It receives signals from the optical sensors, measures timing between sensor events, calculates the target velocity, and controls the servo mechanism.



\## Sensors



\### Optical Sensor System

The prototype uses four analog sensor inputs arranged as two consecutive sensor pairs.



The current implementation uses:



| Sensor | Arduino Pin |

|---|---|

| Sensor 1 - Channel 1 | A0 |

| Sensor 1 - Channel 2 | A2 |

| Sensor 2 - Channel 1 | A4 |

| Sensor 2 - Channel 2 | A6 |



The sensor pairs are used to detect the passage of the rolling target and determine its velocity from the measured time interval.



\## Actuator



\### Servo Motor

The servo motor acts as the interception mechanism. The Arduino calculates the required delay based on the measured velocity and then actuates the servo to release the interceptor at the appropriate time.



Servo control pin:



\- Arduino Due Pin 2



\## Mechanical Track



\### U-shaped Track

A wooden U-shaped track provides a controlled one-dimensional path for the rolling target and interceptor.



The track simplifies the real-world interception problem into a one-dimensional model.



\## Projectiles



Two rolling balls are used:



\- Target ball — represents the incoming threat.

\- Interceptor ball — represents the defensive interceptor.



The current mathematical model is calibrated for the specific ball characteristics used during the experiment.



\## Supporting Components



\- Connecting wires

\- Wooden structure

\- Mechanical supports

\- Power supply

\- Servo mounting mechanis

