#include <SoftwareSerial.h>
 
SoftwareSerial GPRS(7, 8);
String message;    //incoming messages string
char temp;
void setup()
{
  GPRS.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);             // the Serial port of Arduino baud rate.
  delay(3000);                    // because... you know
  GPRS.write("AT+CMGF=1");
}
 
void loop()
{
  if (GPRS.available())              // if date is comming from softwareserial port ==> data is comming from gprs shield
  {   
    Serial.println("Data Received");
    Serial.println(GPRS.available());
      int timestamp = millis();        //timestamp of processor initialization
      int dataAmount = GPRS.available();    
      while(millis() - timestamp < 1000)          // reading data into char array 
      {
        temp=GPRS.read();
        if(temp!=-1){
          message += String(char(temp));
        }
      }
     
      /*for (int i = 0; i < GPRS.available(); i++) {
        message += String(char(GPRS.read()));
      }*/
//      Serial.println("Bebug");
      Serial.println(message); //for debug
   }
   
   if(message.indexOf('+CMTI: "SM",') != -1) {
     Serial.println("Number Found");
       String initCode = "+CMTI: \"SM\",";
       
       int loc = message.indexOf(message.indexOf(initCode) + initCode.length());
       int ends = message.indexOf("\r");
       
       String num_almost = message.substring(loc, ends);
       int num = num_almost.toInt();
       
       Serial.println(char(num));
   }
  message="";
}
