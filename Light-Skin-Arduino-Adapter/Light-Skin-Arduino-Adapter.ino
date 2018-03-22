#define LED_OFF HIGH
#define LED_ON LOW

const int LEDs[] = {
  1, 2, 3
};
const int Sensors[] = {
  A0, A1, A2
};


// Samples to be measured for each sensor measurement
const int SAMPLES = 50;




const int LEDs_num = sizeof(LEDs) / sizeof(int);
const int Sensors_num = sizeof(Sensors) / sizeof(int);




void setup() {

  for(int i = 0; i < LEDs_num; i++){
    pinMode(LEDs[i], OUTPUT);
    digitalWrite(LEDs[i], LED_OFF);
  }
  for(int i = 0; i < Sensors_num; i++){
    pinMode(Sensors[i], INPUT);
  }
  
  Serial.begin(115200);
}




float allValues[LEDs_num][Sensors_num];
int lastLED = LEDs[0];
long sum;
float value;
int l, s, i; // Inner loop variables; so they don't need to be reallocated every time

void loop() {

  // Take a "snapshot": measure all the LED / Sensor combinations
  
  for(l = 0; l < LEDs_num; l++){
    int led = LEDs[l];

    // switch to new LED
    digitalWrite(lastLED, LED_OFF);
    digitalWrite(led, LED_ON);
    
    // Measure all sensors
    for(s = 0; s < Sensors_num; s++){
      int sensor = Sensors[s];
      // Read sensor once to switch ADC circuit to this pin (discard result)
      analogRead(sensor);

      sum = 0;
      for(i = 0; i < SAMPLES; i++){
        sum += analogRead(sensor);
      }
      value = sum / SAMPLES;

      allValues[l][s] = value;
    }
    
    lastLED = led;
  }
  digitalWrite(lastLED, LED_OFF);

  // Print the measurements to Serial
  Serial.print("Snapshot: ");
  Serial.print(LEDs_num);
  Serial.print(',');
  Serial.print(Sensors_num);
  Serial.println();
  for(l = 0; l < LEDs_num; l++){
    for(s = 0; s < Sensors_num; s++){
      Serial.print(allValues[l][s]);
      Serial.print(',');
    }
    Serial.println();
  }

  // Wait for the next snapshot to be taken
  delay(100);
}
