const int pin1 = 2; // First pin connected to the Pico
const int pin2 = 3; // Second pin connected to the Pico
const int pin3 = 4; // Third pin connected to the Pico
const int ledPin = 13; // Pin where the LED is connected

int lastState1 = LOW; // Variable to store the last state of pin1
int lastState2 = LOW; // Variable to store the last state of pin2
int lastState3 = LOW; // Variable to store the last state of pin3

void setup() {
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // Initialize serial communication for the Bluetooth module
}

void loop() {
  int state1 = digitalRead(pin1);
  int state2 = digitalRead(pin2);
  int state3 = digitalRead(pin3);

  // Check if any of the states have changed
  if (state1 != lastState1 || state2 != lastState2 || state3 != lastState3) {
    // Determine the combination of pin states
    if (state1 == LOW && state2 == LOW && state3 == HIGH) {
      Serial.println("Final Prediction: CIRCLE");
      digitalWrite(ledPin, HIGH); // Turn the LED on
      //Serial.println("LED is ON"); // Send data over Bluetooth
      delay(1000); // Wait for 1 second
      digitalWrite(ledPin, LOW); // Turn the LED off
      //Serial.println("LED is OFF"); // Send data over Bluetooth
    } else if (state1 == LOW && state2 == HIGH && state3 == LOW) {
      Serial.println("Final Prediction: IDLE");
      digitalWrite(ledPin, HIGH); // Turn the LED on
      //Serial.println("LED is ON"); // Send data over Bluetooth
      delay(1000); // Wait for 1 second
      digitalWrite(ledPin, LOW); // Turn the LED off
      //Serial.println("LED is OFF"); // Send data over Bluetooth
    } else if (state1 == HIGH && state2 == HIGH && state3 == LOW) {
      Serial.println("Final Prediction: LEFT-RIGHT");
      digitalWrite(ledPin, HIGH); // Turn the LED on
      //Serial.println("LED is ON"); // Send data over Bluetooth
      delay(1000); // Wait for 1 second
      digitalWrite(ledPin, LOW); // Turn the LED off
      //Serial.println("LED is OFF"); // Send data over Bluetooth
    } else if (state1 == HIGH && state2 == HIGH && state3 == HIGH) {
      Serial.println("Final Prediction: UP-DOWN");
      digitalWrite(ledPin, HIGH); // Turn the LED on
      //Serial.println("LED is ON"); // Send data over Bluetooth
      delay(1000); // Wait for 1 second
      digitalWrite(ledPin, LOW); // Turn the LED off
      //Serial.println("LED is OFF"); // Send data over Bluetooth
    } else {
      Serial.println("No valid combination detected");
    }

    // Update the last states
    lastState1 = state1;
    lastState2 = state2;
    lastState3 = state3;
  }

  delay(100); // Add a short delay to avoid spamming the Bluetooth module
}
