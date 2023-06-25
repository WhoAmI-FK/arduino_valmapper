const int POTPIN = A2;
double minValue = 0.1;
double maxValue = 100.0;
double stepValue = 0.1;
double currentValue = 5.0;
int maxPotVal = -1e4;
int minPotVal = 1e4;

double updateCurrentValue(double minVal, double maxVal, double stepVal, double currentVal, int potentiometerVal) {
  // Calculate the proportion based on the potentiometer value
  Serial.println("POTVAL:");
  Serial.println(potentiometerVal);
  double proportion = static_cast < double > (potentiometerVal - minPotVal) / (maxPotVal - minPotVal);

  // Calculate the range of values based on minVal and maxVal
  double valueRange = maxVal - minVal;

  // Calculate the change based on the proportion of the value range
  double change = valueRange * proportion;

  // Calculate the new value based on the change
  double newValue = minVal + change;

  // Round the new value to the nearest multiple of stepVal
  double roundedValue = floor(newValue / stepVal) * stepVal;

  // Ensure the rounded value stays within the range
  currentVal = min(maxVal, max(minVal, roundedValue));

  return currentVal;
}

void setup() {
  Serial.begin(9600);
}

void loop() {

  int potentiometerVal = analogRead(A2);

  if (maxPotVal < potentiometerVal) {
    maxPotVal = potentiometerVal;
  }

  if (minPotVal > potentiometerVal) {
    minPotVal = potentiometerVal;
  }
  // Call the function to adjust currentValue based on potentiometer changes
  if (maxPotVal != (-1e9) && minPotVal != (1e9)) {
    currentValue = updateCurrentValue(minValue, maxValue, stepValue, currentValue, potentiometerVal);
  }
  // Print the updated currentValue for debugging
  Serial.println(currentValue, 2);

  delay(100); // Delay for stability, adjust as needed
}