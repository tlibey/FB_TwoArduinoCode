int inputPin = 6;
int tonePin = 8;
int lightPin = 13;

double toneStarted = 0;

int rewardToneFreq = 788; //normal 988 //control = 788
int toneFreq = 425; //normal == 325 // control = 425
double toneDuration = 120000;
double rewardToneDuration = 300;
double rewardToneBuffer = 200;

double timeSinceTITO = 0;
double lastReward = 0;


boolean reset = true;
boolean toneOn = false;
boolean ableToStart = true;
boolean firstReward = false;

void setup(){
  //Serial.begin(9600);
 pinMode(inputPin,INPUT); 
 pinMode(lightPin,OUTPUT);
}

void loop(){
  int val = digitalRead(inputPin);
  //Serial.println(val);
  
  if(val && reset){
     reset = false; 
     if(!toneOn){
        tone(tonePin,toneFreq,toneDuration); 
        toneOn = true;
        toneStarted = millis();
        //Serial.println("started"); 
      }
      else{
        digitalWrite(lightPin,HIGH);
        rewardTone3();               
      } //end toneOn
   } //end reset 
   if(!val){
     reset = true;
     digitalWrite(lightPin,LOW);

   }
   if(millis()>toneStarted + toneDuration*3/2){
    toneOn = false; 
   }
  
  
  
}

void rewardTone3(){
  tone(tonePin,rewardToneFreq,rewardToneDuration);
  delay(rewardToneDuration + rewardToneBuffer);
   tone(tonePin,rewardToneFreq,rewardToneDuration);
  delay(rewardToneDuration + rewardToneBuffer);
   tone(tonePin,rewardToneFreq,rewardToneDuration);
  delay(rewardToneDuration + rewardToneBuffer);
   double toneElapsed = millis() - toneStarted;
        double toneRemaining = toneDuration - toneElapsed;
        if(toneRemaining > 0){
         tone(tonePin,toneFreq,toneRemaining); 
        }
}

