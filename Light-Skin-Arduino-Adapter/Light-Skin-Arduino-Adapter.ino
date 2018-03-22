

const int LEDs[] = {
  1,
  2,
  3
};
const int LEDs_num = sizeof(LEDs) / sizeof(int);

#define LED_OFF HIGH
#define LED_ON LOW

const int Sensors[] = {
  A0,
  A1,
  A2
};
const int Sensors_num = sizeof(Sensors) / sizeof(int);


const int SAMPLES = 50;



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




int lastLED = LEDs[0];
void loop() {
  
  for(int l = 0; l < LEDs_num; l++){
    int led = LEDs[l];

    // switch to new LED
    digitalWrite(lastLED, LED_OFF);
    digitalWrite(led, LED_ON);
    
    // Measure all sensors for each LED
    for(int s = 0; s < Sensors_num; s++){
      int sensor = Sensors[s];
      // Read sensor once to switch ADC circuit to this pin
      analogRead(sensor);

      long sum = 0;
      for(int i = 0; i < SAMPLES; i++){
        sum += analogRead(sensor);
      }
      float value = sum / SAMPLES;
    }
    
    lastLED = led;
  }
}
