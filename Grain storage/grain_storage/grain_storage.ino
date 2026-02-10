/*
 SMART SAFETY & ENVIRONMENT MONITORING SYSTEM

 Components:
 - PIR Motion Sensor        → D2
 - Temperature Sensor (LM35)→ A2
 - Humidity (Potentiometer)→ A1
 - MQ2 Gas Sensor           → A0
 - LED (Gas Indicator)      → D6
 - Buzzer                  → D12
 - Built-in LED             → Motion Indicator
*/

//// -------- PIN DEFINITIONS --------
const int PIR_PIN = 2;
const int TEMP_PIN = A2;
const int HUMIDITY_PIN = A1;
const int GAS_PIN = A0;
const int LED_PIN = 6;
const int BUZZER_PIN = 12;

//// -------- VARIABLES --------
int pirState;
int gasValue;
int humidityValue;
int rawTempValue;

double voltage;
double tempC;
double tempF;

//// -------- SETUP --------
void setup() {
  Serial.begin(9600);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("System Initialized");
}

//// -------- LOOP --------
void loop() {

  // ===== PIR MOTION SENSOR =====
  pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Motion Detected");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("No Motion");
  }

  // ===== TEMPERATURE SENSOR =====
  rawTempValue = analogRead(TEMP_PIN);
  voltage = (rawTempValue / 1023.0) * 5000;   // millivolts
  tempC = (voltage - 500) * 0.1;
  tempF = (tempC * 1.8) + 32;

  Serial.print("Temperature: ");
  Serial.print(tempC, 1);
  Serial.print(" °C | ");
  Serial.print(tempF, 1);
  Serial.println(" °F");

  // ===== HUMIDITY SENSOR =====
  humidityValue = analogRead(HUMIDITY_PIN);
  int humidityPercent = map(humidityValue, 0, 1023, 10, 70);

  Serial.print("Humidity: ");
  Serial.print(humidityPercent);
  Serial.println(" %");

  // ===== GAS SENSOR =====
  gasValue = analogRead(GAS_PIN);
  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  int outputValue = map(gasValue, 80, 400, 0, 255);
  outputValue = constrain(outputValue, 0, 255);

  analogWrite(LED_PIN, outputValue);
  tone(BUZZER_PIN, outputValue, 100);

  Serial.println("--------------------------------");

  delay(1000);  // 1 second delay
}
