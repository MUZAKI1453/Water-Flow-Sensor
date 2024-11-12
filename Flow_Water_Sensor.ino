const int flowPin = 2;  // Pin 2 for interrupt input
volatile int flow_frequency = 0;  // Flow frequency counter
int flow_rate = 0;  // Flow rate in L/h
int volume = 0;  // Total volume in L
unsigned long cloopTime = 0; // Variable to hold loop time

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(flowPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(flowPin), flowISR, RISING); // Corrected this line
}

void loop() {
  // Every second, calculate and print flow rate and volume
  if (millis() >= (cloopTime + 1000)) {
    cloopTime = millis();
    if (flow_frequency != 0) {
      flow_rate = (flow_frequency / 7.5) * 60;
      Serial.print("Rate: ");
      Serial.print(flow_rate);
      Serial.print(" L/h, ");
      Serial.print("Vol: ");
      Serial.print(volume);
      Serial.println(" L");
      flow_frequency = 0;
    }
  }
}

void flowISR() {  // Corrected the function name to flowISR
  flow_frequency++;
}
