#include <Wire.h>
#include <MQUnifiedsensor.h>

// pins
const int mq7pin = 34;
const int mq135pin = 35;
int dustpin = 23;

//const value
const int ADC_Max_Value = 4095; // esp32

//calibration for mq 7 carbon monoxide
const float A_mq7 = 5.00; //start with smaller values later adjust 
const float B_mq7 = -0.5;

// calibration mq135 methane 
const float A_mq135 = 10.0; //adjust down
const float B_mq135 = -0.3; 

// Dust sensor variables
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 1000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup() {
  Serial.begin(115200);
  pinMode(dustpin,INPUT);
  starttime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  duration = pulseIn(dustpin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;

  if ((millis()-starttime) > sampletime_ms) {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio, 3)-3.8*pow(ratio, 2)+520*ratio+0.62;
    
    lowpulseoccupancy = 0;
    starttime = millis();
    }

  Serial.println(concentration);
   
  // MQ7 (CO Sensor
  int mq7_raw = analogRead(mq7pin);
  float mq7_ppm = A_mq7 * pow((float(mq7_raw) / ADC_Max_Value), B_mq7);

  // MQ135 (Air Quality Sensor
  int mq135_raw = analogRead(mq135pin);
  float mq135_ppm = A_mq135 * pow((float(mq135_raw) / ADC_Max_Value), B_mq135); 
    
  // CO PPM | Air Quality PPM
  Serial.print(mq7_ppm); // CO concentration in ppm
  Serial.print(" ");
  Serial.print(mq135_ppm); // Air quality concentration in ppm
  delay(100);
  }

//  // CO PPM | Air Quality PPM
 // Serial.print(mq7_ppm); // CO concentration in ppm
//Serial.print(" ");
//  Serial.print(mq135_ppm); // Air quality concentration in ppm
//  Serial.print(" ");
//  Serial.println(concentration);
