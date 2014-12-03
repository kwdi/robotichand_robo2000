/*RoboticHand v1*/
#include <Encoder.h>
// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder U1(20, 30); //UpRight
Encoder U2(21, 31); //UPLeft
Encoder D1(32, 33); //DownRight
Encoder D2(34, 35); //DownLeft

//Hbridges

// U1 #Firstbranch Right
int ENA=4;//pwm
int IN1=22;
int IN2=23;

// U2 #Secondbrach Left
int ENB=5;//pwm
int IN3=24;
int IN4=25;

// D1 Right
int ENC=6;//pwm
int IN5=26;
int IN6=27;

// D2 Left
int END=7;//pwm
int IN7=28;
int IN8=29;

//Buttons
int But1=40; //main
int But2=39; //middle
int But3=28; //grip


//variables
byte byteRead;
int u=0;
int j=0;
int k=0;
int pwmspeed=0; 
//

//Initialisation
void setup() {
  Serial.begin(115200);
  Serial.println("Test begin:");

 pinMode(ENA,OUTPUT); //Pwm U1
 pinMode(ENB,OUTPUT); //Pwm U2
 pinMode(ENC,OUTPUT); //Pwm D1
 pinMode(END,OUTPUT); //Pwm D1
 pinMode(IN1,OUTPUT); //U1
 pinMode(IN2,OUTPUT); //U1
 pinMode(IN3,OUTPUT); //U2
 pinMode(IN4,OUTPUT); //U2
 pinMode(IN5,OUTPUT); //D1
 pinMode(IN6,OUTPUT); //D1
 pinMode(IN7,OUTPUT); //D2
 pinMode(IN8,OUTPUT); //D2
 pinMode(But1,INPUT); //main
 pinMode(But2,INPUT); //middle
 pinMode(But2,INPUT); //grip
 
 //Setting All Enable To Low
 digitalWrite(ENA,LOW);
 digitalWrite(ENB,LOW);
 digitalWrite(ENC,LOW);
 digitalWrite(END,LOW);
}

long positionLeft  = -999;
long positionRight = -999;

void loop() {
  /*j=20000;
  k=1; 
  MoveD1D2(j,k);
  delay(3000);*/

  /*  check if data has been sent from the computer: */
  //if (Serial.available()) {
    Serial.println("waiting first num");
    // read the most recent byte 
    byteRead = Serial.read();
    u=byteRead-48;
    Serial.write(byteRead);
    //ECHO the value that was read, back to the serial port. 
   /* Serial.println("waiting second num");
    Serial.write(byteRead);
    
    byteRead = Serial.read();
    Serial.println("waiting third num");
    Serial.write(byteRead);
    j=byteRead-48;
    byteRead = Serial.read();
    Serial.write(byteRead);
    k=byteRead-48;*/
  //}  

  Serial.println("secondif");
  if(u==1)
  {
      MoveU1(200,1);
      Serial.println("moving U1down");
  } 
  else if(u==2)
  {
      MoveU1(200,2);
      Serial.println("moving U1up"); 
  }
  else if(u==3)
  {
      MoveU2(200,1);
      Serial.println("moving U2down"); 
  }
  else if(u==4)
  {
      MoveU2(200,2);
      Serial.println("moving U2up");
  }
  else if (u==5)
  {
      MoveD1D2(200,1);
      Serial.println("moving D1D2down");
  }
  else if (u==6)
  {
      MoveD1D2(200,2);
      Serial.println("moving D1D2up"); 
  } 



  /*long newLeft, newRight;
  newLeft = RLeft.read();
  newRight = RRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    RLeft.write(0);
    RRight.write(0);
  }*/
}

void MoveU1(int x, int y){ //x=steps,y=witchwaytoturn(1=right=down,2=left=up)
  Serial.println("mpika");
  if(y==1)
  {
    Serial.println("11111111");
    digitalWrite(IN1,HIGH);  //high-down/low-up
    digitalWrite(IN2,LOW);  //low-down/high-up

    int pos = U1.read();
    int finalpos=pos+x;

      while(pos<=finalpos)
      {
        pos = U1.read();

          if((finalpos-pos)>100)
          {
            analogWrite(ENA,200);
            pos = U1.read();
          }
          else
          {
            analogWrite(ENA,170);
            pos = U1.read();
          }    
      }
  }
  else if (y==2)
  {
    Serial.println("222222222222");
    digitalWrite(IN1,LOW);  //high-down/low-up
    digitalWrite(IN2,HIGH);  //low-down/high-up

    int pos = U1.read();
    int finalpos=pos-x;

    while(pos>=finalpos && digitalRead(But1)==LOW)
    {
      pos = U1.read();

        if((pos-finalpos)>100)
        {
          analogWrite(ENA,200);
          pos = U1.read();
        }
        else
        {
          analogWrite(ENA,170);
          pos = U1.read();
        }    
    }
  }
  else 
  {
    return;
  }

  analogWrite(ENA,0);
  if(digitalRead(But1)==HIGH)
  {
    U1.write(0);
  }
  return;
}

void MoveU2(int x, int y){ //x=steps,y=witchwaytoturn(1=right=down,2=left=up)

  if(y==1)
  {
    digitalWrite(IN3,HIGH);  //high-down/low-up
    digitalWrite(IN4,LOW);  //low-down/high-up

    int pos = U2.read();
    int finalpos=pos-x;

    while(pos>=finalpos && digitalRead(But2)==LOW)
      {
        pos = U2.read();

          if((pos-finalpos)>100)
          {
            analogWrite(ENB,200);
            pos = U2.read();
          }
          else
          {
            analogWrite(ENB,170);
            pos = U2.read();
          }    
      }
  } 
  else if (y==2)
  {
    digitalWrite(IN3,LOW);  //high-down/low-up
    digitalWrite(IN4,HIGH);  //low-down/high-up

    int pos = U2.read();
    int finalpos=pos+x;

    while(pos<=finalpos)
      {
        pos = U2.read();

          if((finalpos-pos)>100)
          {
            analogWrite(ENB,200);
            pos = U2.read();
          }
          else
          {
            analogWrite(ENB,170);
            pos = U2.read();
          }    
      }
  }
  else 
  {
    return;
  }

  analogWrite(ENB,0);
  if(digitalRead(But2)==HIGH)
  {
    U2.write(0);
  }
  return;
}

void MoveD1D2(int x, int y){ //x=steps,y=witchwaytoturn(1=right=down,2=left=up)
  int pos1=0;
  int pos2=0;

  if(y==1)
  {
    digitalWrite(IN5,HIGH);  //high-down/low-up
    digitalWrite(IN6,LOW);  //low-down/high-up
    digitalWrite(IN7,HIGH);  //high-down/low-up
    digitalWrite(IN8,LOW);  //low-down/high-up

    int finalpos1=pos1+x;
    int finalpos2=pos2+x;

    while(pos1<=finalpos1 && pos2<=finalpos2)
      {
        pos1 = D1.read();
        pos2 = D2.read();

          if((finalpos1-pos1)>100 && (finalpos2-pos2)>100)
          {
            analogWrite(ENC,200);
            analogWrite(END,200);
            pos1 = D1.read();
            pos2 = D2.read();
          }
          else
          {
            analogWrite(ENC,170);
            analogWrite(END,170);
            pos1 = D1.read();
            pos2 = D2.read();
          }    
      }
  } 
  else if (y==2)
  {
    digitalWrite(IN5,LOW);  //high-down/low-up
    digitalWrite(IN6,HIGH);  //low-down/high-up
    digitalWrite(IN7,LOW);  //high-down/low-up
    digitalWrite(IN8,HIGH);  //low-down/high-up

    int finalpos1=pos1-x;
    int finalpos2=pos2-x;

    while(pos1>=finalpos1 && pos2>=finalpos2 && digitalRead(But3)==LOW)
      {
        pos1 = D1.read();
        pos2 = D2.read();

          if((pos1-finalpos1)>100 &&(pos2-finalpos2)>100)
          {
            analogWrite(ENC,200);
            analogWrite(END,200);
            pos1 = D1.read();
            pos2 = D2.read();
          }
          else
          {
            analogWrite(ENC,170);
            analogWrite(END,170);
            pos1 = D1.read();
            pos2 = D2.read();
          }    
      }
  }
  else 
  {
    return;
  }
  analogWrite(ENC,0);
  analogWrite(END,0);
  if(digitalRead(But3)==HIGH)
  {
    D1.write(0);
    D1.write(0);
  }
  return;
}

void SafeZone() {

  while(digitalRead(But1)!=HIGH && digitalRead(But2)!=HIGH && digitalRead(But2)!=HIGH)
  {
      // statement
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  analogWrite(ENC,0);
  analogWrite(END,0);

    if(digitalRead(But1)==LOW && digitalRead(But2)==LOW && digitalRead(But3)==LOW)
    {
      digitalWrite(IN1,LOW);  //high-down/low-up
      digitalWrite(IN2,HIGH);  //low-down/high-up
      analogWrite(ENA,200);

    } else if(digitalRead(But2)==LOW && digitalRead(But3)==LOW)
      {
        digitalWrite(IN1,HIGH);  //high-down/low-up
        digitalWrite(IN2,LOW);  //low-down/high-up
        analogWrite(ENB,200);

      }
      else if (digitalRead(But3)==LOW) 
      {
        digitalWrite(IN5,LOW);  //high-down/low-up
        digitalWrite(IN6,HIGH);  //low-down/high-up
        digitalWrite(IN7,LOW);  //high-down/low-up
        digitalWrite(IN8,HIGH);  //low-down/high-up
        analogWrite(ENC,200);
        analogWrite(END,200);
      }
      else if (digitalRead(But3)==HIGH)
      {
        MoveD1D2(250,1);
      }

  }
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  analogWrite(ENC,0);
  analogWrite(END,0);
}

