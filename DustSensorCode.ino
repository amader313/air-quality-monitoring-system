int pin = 23;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 1000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(23,INPUT);
  starttime = millis();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;

  if ((millis()-starttime) > sampletime_ms) {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio, 3)-3.8*pow(ratio, 2)+520*ratio+0.62;
    
    lowpulseoccupancy = 0;
    starttime = millis();
    }

    Serial.println(concentration);
    delay(100);
}
