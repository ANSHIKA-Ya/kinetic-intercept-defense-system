\# Methodology



\## 1. Problem Formulation



The anti-missile interception problem is formulated as a one-dimensional physical model.



An incoming rolling ball represents the target, while a second ball represents the interceptor.



The objective is to release the interceptor at the correct time so that it collides with the target at a predetermined position on the track.



\## 2. Target Detection



The incoming ball passes through two consecutive optical sensors.



The Arduino records the time at which the ball crosses the first and second sensing points.



The distance between the sensing points is known.



\## 3. Velocity Estimation



The velocity of the target is estimated from the measured time interval:



v = d / Δt



where:



\- v = estimated target velocity

\- d = distance between the two sensors

\- Δt = measured time between sensor events



The implementation uses microsecond-resolution timing through the Arduino `micros()` function.



\## 4. Interception Timing



Once the target velocity has been estimated, the controller determines the required delay before actuating the servo.



The servo releases the interceptor such that the interceptor and target reach the predetermined interception region at approximately the same time.



\## 5. Direction Detection



The sensor arrangement also allows the system to distinguish motion in different directions.



The implementation contains separate measurement states for the two sensor pairs and both directions of motion.



\## 6. Actuation



The servo is normally held in a position that prevents the interceptor from entering the track.



After the calculated delay, the servo is moved to release the interceptor.



After the interception sequence, the servo returns to its initial position.



\## 7. Physical Model



The prototype uses a rolling ball rather than a sliding object. Therefore, the physical model can include both translational and rotational kinetic energy.



For a rolling object:



K\_total = (1/2)mv² + (1/2)Iω²



where:



\- m = mass of the ball

\- v = translational velocity

\- I = moment of inertia

\- ω = angular velocity



For rolling without slipping:



ω = v/r



The current prototype is calibrated for a specific ball type, with its physical parameters treated as known values.



\## 8. Real-World Analogy



The prototype represents the fundamental detection, estimation, prediction, and interception sequence found at a high level in defensive interception systems.



In the prototype:



Optical sensors → Target detection and velocity measurement



Arduino Due → Processing and interception timing



Servo → Interceptor release mechanism



Interceptor ball → Defensive interceptor



Target ball → Incoming threat



In a real anti-missile system, radar and other tracking sensors provide substantially more information, including target position, velocity, trajectory and other tracking parameters. The prototype simplifies these functions to a one-dimensional sensing and interception problem.

