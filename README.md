# Photoresistor-Based Line-Following Robot

An Arduino-controlled robot that follows a black line using two photoresistors, built for an Intro to Electrical/Computer Engineering course. The robot successfully completed all three test tracks, including curves and sharp turns, stopping correctly at the finish line.

Full write-up with circuit derivation and testing notes is included in [`IECE111_Project_2_Report.pdf`](./IECE111_Project_2_Report.pdf).

## Circuit

![Circuit schematic](./images/circuit_schematic.png)

Each photoresistor (PRL, PRR) is wired into a voltage divider with a 10kΩ resistor, connected to an Arduino analog input. Each motor is switched by a digital output pin driving the gate of an NMOS transistor:
- **Dark surface →** high photoresistor resistance → low voltage read on the analog pin → digital pin outputs LOW → transistor gate stays open → motor off
- **Bright surface →** low photoresistor resistance → high voltage read on the analog pin → digital pin outputs HIGH → transistor gate closes → motor on

Photoresistor resistance is calculated in code from the measured voltage using the voltage divider equation, then compared against a threshold to decide bright vs. dark.

## How it works

- **Both sensors see bright (off the line):** both motors on → robot drives straight
- **Left sensor sees dark (on the line):** left motor off, right motor on → robot turns left back toward center
- **Right sensor sees dark (on the line):** right motor off, left motor on → robot turns right back toward center
- **Both sensors see dark (finish line):** both motors off → robot stops

Motors are pulsed on for a short fixed duration (50ms) rather than left on continuously, then the loop waits 300ms before reading the sensors again — this keeps corrections small and gives clean sensor readings between moves.

## Debugging & tuning

Getting from a working circuit to a robot that reliably finished all three tracks took several rounds of real hardware debugging:

- **Wiring:** Initial photoresistor and motor circuits gave incorrect readings/no motor response — traced to incorrect wiring on both the photoresistor voltage dividers and the motor/transistor connections, and to specific digital/analog pin assignments not matching the code.
- **Threshold tuning:** The initial resistance cutoff was too close to the line's actual reading, so the robot would drive past the line before reacting. Lowering the threshold tightened the response without making it falsely trigger on shadows.
- **Sensor spacing:** With sensors placed too far apart and a slight motor strength imbalance, the robot would drift to one side and steer around the finish line instead of stopping on it. Moving the two photoresistors closer together fixed this.
- **Move size:** On the track with sharp turns, the robot occasionally overshot the line entirely. Shortening the motor pulse from 80ms to 50ms reduced how far the robot moved per correction, keeping it from overshooting narrow sections of tape.

## Testing

Tested incrementally: first confirmed each photoresistor gave correct bright/dark readings independently, then confirmed each motor responded correctly to its corresponding sensor, then ran the full robot on three tracks of increasing difficulty (straight line, curved line, sharp turns) — tuning threshold, sensor spacing, and pulse duration between runs until all three tracks completed successfully.

## Files

- `line_follower.ino` — Arduino sketch controlling both motors based on photoresistor readings
- `IECE111_Project_2_Report.pdf` — full report with circuit derivation, pseudocode, and testing notes

## Tools

- **Hardware:** Arduino, 2x photoresistors, 2x NMOS transistors, 2x DC motors, 10kΩ resistors
- **Language:** Arduino (C/C++)

---
*Course project for Intro to Electrical/Computer Engineering, University at Albany.*
