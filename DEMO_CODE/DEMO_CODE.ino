#include <SoftwareSerial.h>
/*
AT+CMGDA="DEL ALL" - Clear ALL messages. Inbox is full at 30.
AT+CMGL="ALL"      - Lists all messages.
AT+CMGR=<n>        - Reads message number <n>
ATD+phonenumber,i; - Call phonenumber
ATA                - Answer incoming call
ATH                - Hang up

*/
SoftwareSerial GPRS(7, 8);
String message;    //incoming messages string
char temp;
int timestamp;
int dataAmount;

void setup()
{
  GPRS.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);             // the Serial port of Arduino baud rate.
  delay(3000);                    // because... you know
  GPRS.write("AT+CMGF=1\r\n");
}
 
void loop()
{
  if (Serial.available()){
    while(Serial.available()){
    GPRS.write(Serial.read());
    }
  }
  if (GPRS.available())              // if date is comming from softwareserial port ==> data is comming from gprs shield
  {   
      timestamp = millis();        //timestamp of processor initialization
      dataAmount = GPRS.available();    
      while(GPRS.available())          // reading data into char array 
      {
        temp=GPRS.read();
        if(temp!=-1){
          message += String(char(temp));
        }
      }
      Serial.println(message); //for debug
   }
   
   //Check for incoming message
   if(message.indexOf("+CMTI: \"SM\",") != -1) {
     Serial.println("Number Found");
       String initCode = "+CMTI: \"SM\",";
       
       int loc = message.indexOf(initCode)+initCode.length();
       int ends = message.indexOf("\\r");
       Serial.print(loc);
       Serial.print(",");
       Serial.println(ends);
       
       String num_almost = message.substring(loc);
       int num = num_almost.toInt();
       
       Serial.println(num);
       read_message(num);
   }
   
   //Check for message to parse
   if(message.indexOf("+CMGR:") != -1) {
     Serial.println("Message read");
   }
  message="";
}

void read_message(int message_number){
  GPRS.print("AT+CMGR="); 
  GPRS.print(message_number);
  GPRS.print("\r\n");
  //delay(1000);
  while(GPRS.available()){
    Serial.print(char(GPRS.read()));
  }
}

int start(){
  //Try to start
  
  return 0;
}
