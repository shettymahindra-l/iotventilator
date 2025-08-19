#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD setup (change address 0x27 to your LCD’s I2C address if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo setup
Servo ventServo;
int servoPin = 9;

// Push button pins
const int startButton = 2;
const int modeButton  = 3;

// LED pins
const int greenLED = 6;
const int redLED   = 7;

// Potentiometer pin for BPM control
const int potPin = A0;

// Safety sensor (simulated with analog input)
const int currentSensorPin = A1;

// Variables
bool ventilatorOn = false;
int mode = 0; // 0 = Adult, 1 = Child
int BPM = 12; // default

// Servo positions (adjust based on mechanics)
int inhalePos = 0;
int exhalePos = 90;

void setup() {
  Serial.begin(9600);
  
  // LCD init
  lcd.init();
  lcd.backlight();
  
  // Servo init
  ventServo.attach(servoPin);
  ventServo.write(exhalePos);
  
  // Button/LED setup
  pinMode(startButton, INPUT_PULLUP);
  pinMode(modeButton, INPUT_PULLUP);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  lcd.setCursor(0,0);
  lcd.print("IoT Ventilator");
  lcd.setCursor(0,1);
  lcd.print("Press Start Btn");
}

void loop() {
  // Read buttons
  if (digitalRead(startButton) == LOW) {
    ventilatorOn = !ventilatorOn; // toggle start/stop
    delay(300); // debounce
  }
  
  if (digitalRead(modeButton) == LOW) {
    mode = !mode; // toggle between Adult/Child
    delay(300);
  }

  // Read BPM from potentiometer (range: 10 - 30)
  BPM = map(analogRead(potPin), 0, 1023, 10, 30);

  // Display mode and BPM
  lcd.setCursor(0,0);
  lcd.print(mode == 0 ? "Mode: Adult   " : "Mode: Child   ");
  lcd.setCursor(0,1);
  lcd.print("BPM: ");
  lcd.print(BPM);
  lcd.print("        ");

  if (ventilatorOn) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);

    runBreathingCycle(BPM);
    
    // Safety check (simulate overcurrent)
    int currentValue = analogRead(currentSensorPin);
    if (currentValue > 800) {  // threshold for alarm
      triggerAlarm();
    }
  } else {
    digitalWrite(greenLED, LOW);
    ventServo.write(exhalePos); // default position
  }
}

void runBreathingCycle(int bpm) {
  int cycleTime = 60000 / bpm; // time per breath in ms
  int inhaleTime = cycleTime * 0.4; // 40% inhale
  int exhaleTime = cycleTime * 0.6; // 60% exhale

  // Inhale
  lcd.setCursor(12,1);
  lcd.print("Inh ");
  ventServo.write(inhalePos);
  Serial.println("Inhale");
  delay(inhaleTime);

  // Exhale
  lcd.setCursor(12,1);
  lcd.print("Exh ");
  ventServo.write(exhalePos);
  Serial.println("Exhale");
  delay(exhaleTime);
}

void triggerAlarm() {
  ventilatorOn = false;
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("!! ALARM TRIGGER");
  lcd.setCursor(0,1);
  lcd.print("Check Sensors");
  
  Serial.println("ALARM: Safety triggered!");
  delay(2000);
}
