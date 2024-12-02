Overview: This project monitors temperature, vibration, and RPM (rotation per minute) using various sensors. If the temperature exceeds a threshold, a buzzer and red LED are activated. Vibration is counted, and the vibration level is displayed with a green LED. The RPM is detected using a Hall effect sensor, and a yellow LED indicates the RPM readings. The data is displayed on an LCD screen and sent via Serial to monitor these parameters.
Code Breakdown:

1. Lines 1-5: Define Libraries

    Libraries for one-wire communication (OneWire.h), Dallas Temperature sensors (DallasTemperature.h), I2C communication (Wire.h), and LCD control (LiquidCrystal_I2C.h) are included.

2. Lines 7-11: Pin Definitions

    Define pins for the temperature sensor, vibration sensor, buzzer, Hall sensor, and LEDs (red, green, and yellow).

3. Lines 13-17: Initialize Objects and Variables

    Create instances for the OneWire, DallasTemperature, and LiquidCrystal_I2C objects. Define variables for vibration count, RPM, and sensor states.

4. Lines 19-25: Time Tracking Variables

    Define time variables to control sensor readings and debounce actions (for vibration and Hall sensor).

5. Lines 27-35: Setup Function

    Initialize sensors, serial communication, pin modes, and LCD display settings.

6. Lines 37-75: Main Loop

    Sensor Readings:
        Every 25 milliseconds, the temperature is read and displayed.
        If the temperature exceeds 40°C, the buzzer is activated, and the red LED lights up.
        Vibration is detected using a vibration sensor. When vibration is detected, the green LED is activated, and the vibration count is incremented. If no vibration is detected for 2 seconds, the count resets.
        The Hall sensor detects RPM by counting the number of pulses within a 2-second window. The yellow LED lights up when the RPM is being counted.

    Data Display:
        The temperature, vibration count, and RPM are printed on the LCD screen. The data is also sent to the Serial monitor for remote monitoring.

