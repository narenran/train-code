
const int trigPin = 2;
const int echoPin = 3;

const int IR_SEN = 5;

const int RLY = 4;


char ir_flag, ultra_flag = 0, flag2 = 0;

long duration;
float distance;

void setup() 
{
 Serial.begin(9600);
 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT); 

 pinMode(IR_SEN, INPUT); 

 pinMode(RLY, OUTPUT); digitalWrite(RLY, HIGH);
}

void loop() 
{
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 
 duration = pulseIn(echoPin, HIGH);
 distance = 0.034*(duration/2);

 if(distance > 99)distance = 99;

 //////
 
 if(digitalRead(IR_SEN) ==  LOW){ delay(10); if(digitalRead(IR_SEN) ==  LOW){ delay(10); if(digitalRead(IR_SEN) ==  LOW){ ir_flag = 0; } } }
 if(digitalRead(IR_SEN) == HIGH){ delay(10); if(digitalRead(IR_SEN) == HIGH){ delay(10); if(digitalRead(IR_SEN) == HIGH){ ir_flag = 1; } } }

 //////
 
 Serial.write(ir_flag+48); Serial.print(" "); Serial.println(distance);
 

      if(distance <= 20)ultra_flag = 1;
 else if(distance >= 25)ultra_flag = 0;
 
 
 if( (ultra_flag == 0) && (ir_flag == 1) )  //both normal
 {
  digitalWrite(RLY, HIGH);  //OFF  
 
  flag2 = 0;
 }
 else 
 {
  if( (ultra_flag == 0) && (ir_flag == 0) )  //ir abnormal 
  {
   if(flag2 == 0)
   {
    digitalWrite(RLY,  LOW);  //ON  
     
    delay(5000);  

    digitalWrite(RLY, HIGH);  //OFF  
   
    flag2 = 1;
   }
  }
  else if( (ultra_flag == 1) && (ir_flag == 1) )  //ultra abnormal 
  {
   digitalWrite(RLY,  LOW);  //ON  
  }
 }

 delay(100);  
}
