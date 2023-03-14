#include <wiringPi.h>
#include <iostream>

using namespace std;

// Define GPIO pins
const int trigPin = 23;
const int echoPin = 24;

int main() {
  // Initialize wiringPi library
  if (wiringPiSetup() == -1) {
    cout << "Error: wiringPi setup failed." << endl;
    return 1;
  }

  // Configure GPIO pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Loop to read sensor data
  while (true) {
    // Send trigger pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Wait for echo signal
    while (digitalRead(echoPin) == LOW);
    unsigned long startTime = micros();

    while (digitalRead(echoPin) == HIGH);
    unsigned long travelTime = micros() - startTime;

    // Calculate distance in centimeters
    float distance = travelTime / 58.0;

    // Output distance to console
    cout << "Distance: " << distance << " cm" << endl;

    // Add delay before next reading
    delay(500);
  }

  return 0;
}
