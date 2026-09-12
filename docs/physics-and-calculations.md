# Physics and Calculations

## 1. Problem Formulation

The physical prototype models the interception problem as a **one-dimensional rolling-object system**.

The target moves along a constrained U-shaped track, while an interceptor is released by a servo-controlled mechanism.

The objective is to determine an appropriate interceptor release time from the measured motion of the target.

---

## 2. Rolling Motion

The target is a rolling ball rather than a purely translating object.

Therefore, its kinetic energy consists of two components:

- Translational kinetic energy
- Rotational kinetic energy

The total kinetic energy is:

\[
K = K_{trans} + K_{rot}
\]

or

\[
K = \frac{1}{2}mv^2 + \frac{1}{2}I\omega^2
\]

where:

- \(m\) = mass of the ball
- \(v\) = translational velocity
- \(I\) = moment of inertia
- \(\omega\) = angular velocity

---

## 3. Rolling Without Slipping

For ideal rolling without slipping:

\[
\omega = \frac{v}{r}
\]

where \(r\) is the radius of the ball.

Substituting this into the kinetic-energy equation:

\[
K =
\frac{1}{2}mv^2
+
\frac{1}{2}I
\left(\frac{v}{r}\right)^2
\]

This demonstrates why the rotational component cannot be ignored when analysing a rolling object.

---

## 4. Velocity Measurement

The target velocity is obtained from the time required for the target to travel between two sensing points.

For a known sensing distance \(d\):

\[
v = \frac{d}{\Delta t}
\]

where:

- \(d\) = distance between sensing points
- \(\Delta t\) = measured travel time

The Arduino Due records the sensor-transition times using the `micros()` function.

The current firmware converts the measured time interval into a calibrated velocity value.

---

## 5. Sensor Timing

The firmware detects transitions on the optical sensors.

For example, for one measurement path:

```text
Sensor 1 transition
        │
        ▼
Record start time
        │
        ▼
Sensor 2 transition
        │
        ▼
Record end time
        │
        ▼
Δt = end time − start time
        │
        ▼
Calculate velocity

The implementation uses:

S1_start_time = micros();

followed by:

S1_end_time = micros();

The measured interval is then used to determine the target velocity.

6. Directional Velocity Measurement

The firmware contains four measurement paths:

S1 → S2
S3 → S4
S2 → S1
S4 → S3

These paths allow the system to distinguish motion in different directions along the track.

The corresponding firmware variables are:

Velocity1
Velocity2
Velocity3
Velocity4

The velocity calculation uses the measured difference between the corresponding sensor timestamps.

7. Interception Timing

Once the target velocity has been measured, the firmware calculates an actuation delay.

In the active interception mode, the current implementation uses:

$$ dt = \frac{400}{Velocity1} $$

The firmware then applies a timing correction:

if(dt > 480)
{
    dt = dt - 480;
}
else
{
    dt = 0;
}

The resulting delay is used before servo actuation.

8. Servo Actuation

After the calculated delay, the servo moves the interceptor release mechanism.

The current firmware commands the servo through the Arduino Servo library.

The release sequence is approximately:

Wait calculated delay
        │
        ▼
Move servo from 155° to 130°
        │
        ▼
Hold for approximately 800 ms
        │
        ▼
Return servo from 130° to 155°

The purpose of this mechanism is to release the interceptor at the calculated time.

9. Calibration

The firmware contains calibrated constants that connect the measured sensor timing to the velocity and actuation calculations.

For example, the current velocity calculation contains:

Velocity1 = 50000.0 /
            (S1_end_time - S1_start_time);

The value 50000.0 is therefore part of the current experimental calibration.

Its physical interpretation depends on the units and calibration procedure used during construction of the prototype.

This value should be treated as an experimentally determined system constant unless the physical calibration procedure is explicitly documented.

10. Theoretical Model vs Firmware

An important distinction is made between the physical model and the current embedded implementation.

Theoretical model

The theoretical analysis considers:

$$ K = \frac{1}{2}mv^2 + \frac{1}{2}I\omega^2 $$

and:

$$ \omega = \frac{v}{r} $$

This describes the physics of the rolling target.

Current firmware

The current firmware primarily performs:

Sensor detection
       ↓
Timestamp measurement
       ↓
Travel-time calculation
       ↓
Calibrated velocity estimation
       ↓
Interception-delay calculation
       ↓
Servo actuation

The current Arduino code does not explicitly calculate mass, moment of inertia, angular velocity, or rotational kinetic energy.

These quantities belong to the theoretical physical model used to understand the rolling system.

11. Assumptions

The prototype operates under several simplifying assumptions:

Target motion is constrained to one dimension.
The target follows the physical track.
The target is approximately rolling without slipping.
The target ball is treated as a known physical object.
Sensor positions are fixed.
The experimental calibration remains valid during operation.
Servo response is sufficiently repeatable for the intended experiment.
Mechanical losses and friction are not fully modelled.
12. Sources of Error

Potential sources of error include:

Sensor Timing

Sensor response time and threshold selection can introduce timing uncertainty.

Mechanical Friction

Rolling resistance and track imperfections can alter the target velocity.

Track Geometry

Small changes in track alignment or surface geometry can affect the motion.

Servo Response

The servo requires finite time to move between commanded positions.

Calibration Error

The velocity and timing calculations depend on experimentally calibrated constants.

Release Variation

Small differences in the initial release condition can affect the target trajectory.

13. Experimental Validation

The mathematical and timing model should ultimately be validated using repeated experimental trials.

Useful measurements include:

$$ Error_{position} = x_{measured} - x_{target} $$

and:

$$ Error_{timing} = t_{actual} - t_{predicted} $$

Repeated trials can then be used to determine:

Mean interception-position error
Maximum interception-position error
Timing error
Repeatability
Sensor-to-actuation latency

These measurements will be documented in:

results/experimental-results.md
14. Summary

The prototype combines:

Rolling-body physics
        +
Optical sensing
        +
Microsecond timing
        +
Velocity estimation
        +
Interception timing
        +
Servo actuation

The resulting system provides a physical demonstration of how measured target motion can be used to determine an appropriate interception action in a controlled one-dimensional environment.