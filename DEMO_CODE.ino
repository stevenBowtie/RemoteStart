#include <SoftwareSerial.h>
 
SoftwareSerial GPRS(7, 8);
String message;    //incoming messages string
void setup()
{
  GPRS.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);             // the Serial port of Arduino baud rate.
}
 
void loop()
{
  if (GPRS.available())              // if date is comming from softwareserial port ==> data is comming from gprs shield
  {   
      int timestamp = millis();        //timestamp of processor initialization
      int dataAmount = GPRS.available();    
      
      while(millis() - timestamp < 500)          // reading data into char array 
      {
        if(GPRS.available() > dataAmount) {
          dataAmount = GPRS.available();
          timestamp = millis();
        }
      }
      
      message = "";
      for (int i = 0; i < GPRS.available(); i++) {
        message += String(GPRS.read());
      }
   }
   
   if(message.indexOf('+CMTI: "SM",') != -1) {
       String initCode = "+CMTI: \"SM\",";
       
       int loc = message.indexOf(message.indexOf(initCode) + initCode.length());
       int ends = message.indexOf("\r");
       
       String num_almost = message.substring(loc, ends);
       int num = num_almost.toInt();
       
   }
}
