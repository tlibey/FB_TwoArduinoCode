
double timeIn_ms = 120000; //5 minutes = 300000
double timeOut_ms = 120000;

int RFinPin = 9;
int printingState=0;
int oldState =LOW;
unsigned long  oldTime = 0;
unsigned long  currentTime = 0;
int count = 0;
unsigned long oldTimecue = 0;
int feederPin = 8;
int lightPin = 13;
unsigned long successCounter = 0;
int lowThresh = 700;
int highThresh = 1300;

int toneOutPin = 7;

double lastChange = 0;
double lastPulse = 0;
double firstPulse = 0;
boolean toneOn = false;
int rewardCounter = 0;
String rs = "r: ";
String tis = "timein: ";
String serPrint = ""; 


char serChar = 0;

void setup()
{
 pinMode(RFinPin, INPUT); 
 pinMode(feederPin,OUTPUT);
 pinMode(lightPin,OUTPUT);
 pinMode(toneOutPin,OUTPUT);
 Serial.begin(9600);
}


void loop()
{
   if(Serial.available() > 0)
 {
 serChar = Serial.read();
 
 }
 if (serChar=='A')
{
   pulse(feederPin,1);
   pulse(lightPin,1000);
   serChar = 0;
} 
 
  
 int currentState = digitalRead(RFinPin);
 if(currentState != oldState)
 {
   oldState = currentState;
   currentTime = micros();
   unsigned long  timecue = currentTime-oldTime;
//964/1020
   
   if(timecue >= lowThresh&& timecue <= highThresh && oldTimecue >=lowThresh && oldTimecue <= highThresh)
   {  
        //Serial.println(timecue);

     count = count++;
     if(count >= 5)
     { 
      count = 0;
      receivedEvent();
    }
     
   }
   else
   {
    count = 0; 
    if(millis()>lastPulse+300)
    {
    digitalWrite(feederPin,LOW);
    digitalWrite(lightPin,LOW);
    digitalWrite(toneOutPin,LOW);
    }
   }
   oldTimecue = timecue;
   oldTime = currentTime;
 }
}

void receivedEvent(){
  
 
      digitalWrite(toneOutPin,HIGH);
      digitalWrite(lightPin,HIGH);
      rewardCounter++;
     if(millis() > lastPulse + 2*timeOut_ms/3){
      serPrint = tis + millis();
      }
      else{
          serPrint = rs + rewardCounter + " t: " + millis();
      }
        lastPulse = millis();

        Serial.println(serPrint);

      digitalWrite(feederPin,HIGH);
      delay(100);
      digitalWrite(toneOutPin,LOW);
      
        }
  

void pulse(int pin, int _delay)
{
 digitalWrite(pin,HIGH);
delay(_delay);
digitalWrite(pin,LOW);
delay(_delay);
}


  

