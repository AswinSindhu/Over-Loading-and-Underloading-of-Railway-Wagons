#include <HX711.h>

#define LOADCELL_DOUT_PIN 33
#define LOADCELL_SCK_PIN 32

HX711 scale;

#define LED1_PIN 19
#define LED2_PIN 18
#define LED3_PIN 5
#define BUZZER_PIN 4
#define BUTTON_PIN 25

bool stopReadings = false; // Start readings by default

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistor

  Serial.begin(115200); // Initialize serial communication for debugging
  Serial.println("Scale starting...");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();  // Calibrate the scale if needed
}

void loop() {
  float weight = scale.get_units(10);  // Read the weight from the load cell
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" kg");

  // Check if the button is pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Button is pressed, plot the weight
    Serial.println(weight);
  }

  // Control the LEDs based on the weight
  if (weight > 10000) {
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
    Serial.print(weight - 10000);
    Serial.println(" KG must be reduced");

    // Activate the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    tone(BUZZER_PIN, 262, 1000); // Plays 262Hz tone for 0.250 seconds
    

  } else if (weight < 5000) {
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, LOW);
    Serial.print(5000 - weight);
    Serial.println(" KG can be added");
  } else {
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
  }

  delay(10);
}
