#include <Servo.h>





Servo myservo;                

int angle1 = 0;  

int angle2 = 90;                    



int sensor_1_pin1 = A0;                          

int sensor_1_pin2 = A2;                          

int sensor_2_pin1 = A4;                          

int sensor_2_pin2 = A6;  



int S1_counts,S2_counts,S3_counts,S4_counts;

bool S1,S2,S3,S4;

bool S1_old,S2_old,S3_old,S4_old;

bool S1_rising, S2_rising,S3_rising,S4_rising;



int S1_timer,S3_timer;

long t1,t2,t3,t4,t5;

int state_1,state_2,state_3,state_4;

long S1_start_time,S1_end_time,S3_start_time,S3_end_time;

long S2_start_time,S2_end_time,S4_start_time,S4_end_time;

int S1_pulse_width,S2_pulse_width;

double Velocity1,Velocity2,Velocity3,Velocity4;

bool trigger1,trigger2,trigger3,trigger4,trigger5;

bool done=false;

long dt=0;

                       





void setup() {

  pinMode(13, OUTPUT);

  myservo.attach(2);        // attaches the servo on pin 2 to the servo object

  Serial.begin(115200);                                  

  analogReadResolution(12);

 

       for (int pos = 0; pos <= 155; pos += 1)

       {

       myservo.write(pos);              

       delay(10);                      

       }

       

  delay(1000);

  Serial.println("start");

  state_1 =0;

  state_2 =0;

  state_3 =0;

  state_4 =0;

  t3=millis();

}

char mode = 0;



void loop() {

    t1=micros();

   

    S1_counts = analogRead(sensor_1_pin1); if(S1_counts < 1400){S1=true;}else{S1=false;}

    delayMicroseconds(50);

    S2_counts = analogRead(sensor_1_pin2);if(S2_counts < 1400){S2=true;}else{S2=false;}

    delayMicroseconds(50);

    S3_counts = analogRead(sensor_2_pin1);if(S3_counts < 1400){S3=true;}else{S3=false;}

    delayMicroseconds(50);

    S4_counts = analogRead(sensor_2_pin2);if(S4_counts < 1400){S4=true;}else{S4=false;}



    if(S1==true && S1_old == false){S1_rising = true;}else{S1_rising = false;} S1_old=S1;

    if(S2==true && S2_old == false){S2_rising = true;}else{S2_rising = false;} S2_old=S2;

    if(S3==true && S3_old == false){S3_rising = true;}else{S3_rising = false;} S3_old=S3;

    if(S4==true && S4_old == false){S4_rising = true;}else{S4_rising = false;} S4_old=S4;



    //--measure +ve velocity sensor1

    if(state_1==0 && S1_rising ==true){S1_start_time=micros();state_1=1;}

    if(state_1==1 && S2_rising ==true){S1_end_time = micros();Velocity1 = 50000.0/(S1_end_time-S1_start_time);state_1=0; trigger1=true;trigger5=true;}

    if(state_1==1 && (micros()-S1_start_time) > 500000){state_1=0;}



    //--measure +ve velocity sensor2

    if(state_2==0 && S3_rising ==true){S3_start_time=micros();state_2=1;}

    if(state_2==1 && S4_rising ==true){S3_end_time = micros();Velocity2 = 50000.0/(S3_end_time-S3_start_time);state_2=0;trigger2=true;}

    if(state_2==1 && (micros()-S3_start_time) > 500000){state_2=0;}

   

    //---measure -ve velocity sensor1

    if(state_3==0 && S2_rising ==true){S2_start_time=micros();state_3=1;}

    if(state_3==1 && S1_rising ==true){S2_end_time = micros();Velocity3 = 50000.0/(S2_end_time-S2_start_time);state_3=0; trigger3=true;}

    if(state_3==1 && (micros()-S2_start_time) > 500000){state_3=0;}



   //---measure -ve velocity sensor2

    if(state_4==0 && S4_rising ==true){S4_start_time=micros();state_4=1;}

    if(state_4==1 && S3_rising ==true){S4_end_time = micros();Velocity4 = 50000.0/(S4_end_time-S4_start_time);state_4=0;trigger4=true;}

    if(state_4==1 && (micros()-S4_start_time) > 500000){state_4=0;}



 if(mode==1)

 {    

    if(trigger5==true)//----caculate the time delay and activate servo to allow the ball to fall for colision

    {  

       dt=400.0/Velocity1;

       if(dt>480){dt=dt-480;}else{dt=0;}

       delay(dt);

       for (int pos = 155; pos > 130; pos -= 1) {

       myservo.write(pos);              

       delay(1);                      

       }

       delay(800);

       for (int pos = 130; pos <= 155; pos += 1) {

       myservo.write(pos);              

       delay(1);                      

       }

      trigger5=false;

    }

    }



  t2=micros();

//  Serial.print(S1);

//  Serial.print("  ");

//  Serial.print(S2);

//  Serial.print("  ");

//  Serial.print(S3);

//  Serial.print("  ");

//  Serial.print(S4);

//  Serial.print("  ");

//  Serial.print(Velocity1,3);

//  Serial.print("  ");

//  Serial.print(Velocity2,3);

//  Serial.print("  ");

//  Serial.print(t2-t1);

//  //Serial.print(50.0/(t2-t1),3);

//  Serial.println();



//if(millis()-t3> 5000 && done==false){

//  t4=micros();

//   myservo.write(150);

//   done=true;

//}

//if(trigger2==true){t5=micros();Serial.print(t5-t4);Serial.print(" = t");}





//if(trigger1==true){Serial.print(t2-t1);Serial.print(" V1-->"); Serial.println(Velocity1,3);trigger1=false; }

//if(trigger2==true){Serial.print(t2-t1);Serial.print(" V2-->"); Serial.println(Velocity2,3);trigger2=false; }

//if(trigger3==true){Serial.print(t2-t1);Serial.print(" V1-->"); Serial.println(-Velocity3,3);trigger3=false;}

//if(trigger4==true){Serial.print(t2-t1);Serial.print(" V2-->"); Serial.println(-Velocity4,3);trigger4=false;}



if(Serial.available() >0){

  char ch = Serial.read();

  if(ch == 'A'){ mode = 0;}

  if(ch == 'B'){ mode = 1;}

  if(ch == '1'){if(trigger1==true){Serial.println(Velocity1,3);trigger1=false;Serial.print(",1E"); }else {Serial.print("0,0E");}}

  if(ch == '2'){if(trigger2==true){Serial.println(-Velocity2,3);trigger2=false;Serial.print(",1E"); }else {Serial.print("0,0E");}}

  if(ch == '3'){if(trigger3==true){Serial.println(-Velocity3,3);trigger3=false;Serial.print(",1E"); }else {Serial.print("0,0E");}}

  if(ch == '4'){if(trigger4==true){Serial.println(Velocity4,3);trigger4=false;Serial.print(",1E"); }else {Serial.print("0,0E");}}

}



//  delay(1);      

}

