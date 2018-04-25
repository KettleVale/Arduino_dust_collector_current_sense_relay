/*
Measuring AC Current Using ACS712 and switching Relay accordingly

This code is from Henry's Bench and modified for this application by Kettle Vale

http://henrysbench.capnfatz.com/henrys-bench/arduino-current-measurements/acs712-arduino-ac-current-tutorial/#The_ACS712_Arduino_AC_Current_Tutorial_Sketch

Arduino_dust_collector_current_sense_relay

*/
const int sensorIn = A0;
int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module
double ampThreshold = 1.00;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
const int dustCollectionPin = 7;
int DCspindown = 1000;

void setup(){ 
 Serial.begin(9600);
 pinMode (dustCollectionPin, OUTPUT);
 digitalWrite(dustCollectionPin, LOW);
 pinMode (sensorIn, INPUT);
}

void loop(){
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS");
if (AmpsRMS>ampThreshold){
  digitalWrite(dustCollectionPin, LOW);
}else{
  delay (DCspindown);
  digitalWrite(dustCollectionPin, HIGH);
}
}
float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 500) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }

