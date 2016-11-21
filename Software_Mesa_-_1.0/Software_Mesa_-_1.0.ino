#include "SoftwareSerial.h"
#include "Servo.h"
#include "ctype.h"
  SoftwareSerial bluetooth(2, 3); //RX, TX
  Servo servoY;
  Servo servoX;
  int servoVar;
  void setup() {
    servoY.attach(12);  
    servoX.attach(11);
    //Serial.begin(9600);
    bluetooth.begin(115200);
    //bluetooth.setTimeout(35);
  } 
  int move_X;
  int move_Y;
      
  void deserializarCoordenadas()
  {
    int i = 0;
    int iPosX = -1;
    bool achouX = false;
    String possivelX;
    String possivelY;
    String message;
    while(bluetooth.available()) 
    {
      char chr = (char)bluetooth.read();  
      message += chr;
    }
    String str = message;
    //Serial.println(message);
    for(char& charIN : str) {


      if(!achouX)
      {
        if(i == 0 && charIN != '<'){return;}
        if(i == 1 && charIN != 'X'){return;}
        if(i == 2 && charIN != ':'){return;}
        if(i == 3 && charIN == '-')
        {
            possivelX += charIN;
        }
        if(i == 3 && isDigit(charIN))
        {
            possivelX += charIN;
        }
        if(i == 4 || i == 5 || i == 6 )
        {
          if(isDigit(charIN)){possivelX += charIN;}
        }
        if(charIN == '>')
        {
          //Serial.println("Achou X:" + possivelX);  
          move_X = possivelX.toInt();
          achouX = true;
          
        }
      }  
      
      if(achouX)
      {
        
     
        if(iPosX == 0 && charIN != '<'){return;}
        if(iPosX == 1 && charIN != 'Y'){return;}
        if(iPosX == 2 && charIN != ':'){return;}
        if(iPosX == 3 && charIN == '-')
        {
          
            possivelY += charIN;
        }
        if(iPosX == 3 && isDigit(charIN))
        {
            possivelY += charIN;
        }
        if(iPosX == 4 || iPosX == 5 || iPosX == 6 )
        {
          if(isDigit(charIN)){possivelY += charIN;}
        }
        if(charIN == '>' && iPosX > 0)
        {
          //Serial.println("Achou Y:" + possivelY);  
          move_Y = possivelY.toInt();
          
        }

        iPosX++;
      }
      i++;
    }      
  }
  int antigaServoVarY;
  int antigaServoVarX;
  void loop() 
  {
      if (bluetooth.available())  
      {  
        deserializarCoordenadas();
      }
      int servoVarY = map(move_Y, -100, 100, 0, 200);
      int servoVarX = map(move_X, -100, 100, 0, 200);
      if(antigaServoVarY != servoVarY)
      {
        servoY.write(servoVarY);
        delay(15);
        //Serial.println("diff");
        antigaServoVarY = servoVarY;
      }

      
      if(antigaServoVarX != servoVarX)
      {
        servoX.write(servoVarX);
        delay(15);
        antigaServoVarX = servoVarX;
      }

  }

