#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 8
#define VIBRATION_PIN 11
#define BUZZER_PIN 9
#define HALL_SENSOR_PIN 10

#define RED_LED_PIN 7 
#define GREEN_LED_PIN 6   
#define YELLOW_LED_PIN 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

volatile int vibrationCount = 0;
int currentState = LOW;

unsigned long lastHallHighMillis = 0;
unsigned long lastVibHighMillis = 0;
unsigned long previousMillis = 0;
const unsigned long interval = 25;

void setup() {
  sensors.begin();
  sensors.setResolution(12);
  Serial.begin(9600);

  pinMode(VIBRATION_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(HALL_SENSOR_PIN, INPUT);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);

    if (temperature > 40) {
      digitalWrite(BUZZER_PIN, HIGH);
      digitalWrite(RED_LED_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(RED_LED_PIN, LOW);
    }
    
    currentState = digitalRead(VIBRATION_PIN);

    if (currentState == HIGH) {
      vibrationCount++;
      lastVibHighMillis = currentMillis;
      digitalWrite(GREEN_LED_PIN, HIGH); 
    } else if (currentMillis - lastVibHighMillis > 2000) {
      vibrationCount = 0;
      digitalWrite(GREEN_LED_PIN, LOW); 
    }
    
    int hallReading = digitalRead(HALL_SENSOR_PIN);
    int rpm = 0;

    if (hallReading == HIGH) {
      lastHallHighMillis = currentMillis;
    }
    
    if (currentMillis - lastHallHighMillis < 2000) {
      rpm++;
      digitalWrite(YELLOW_LED_PIN, HIGH); 
    } else {
      rpm = 0;
      digitalWrite(YELLOW_LED_PIN, LOW); 
    }

   Serial.print(temperature);  Serial.print(",");
   Serial.print(vibrationCount);  Serial.print(",");
   Serial.print(rpm); 

    lcd.setCursor(0, 0);
    lcd.print("Temp: "); lcd.print(temperature, 1); lcd.print(" C    ");

    lcd.setCursor(0, 1);
    lcd.print("Vib:"); lcd.print(vibrationCount); lcd.print(" RPM:"); lcd.print(rpm);
    lcd.print("   ");
  }
}
