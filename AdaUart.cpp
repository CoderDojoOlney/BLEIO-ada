#include "AdaUart.h"

//
// An error helper. Prints and terminates
void error(const __FlashStringHelper*err) 
{
  Serial.println(err);
  while (1);
}

AdaUart::AdaUart()
  : ble(8, 7, 6)
{
  
}


//
// Initialise the BLE connection in Data mode
void AdaUart::initBle(String name)
{
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(true) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  
  Serial.println( F("OK!") );

  Serial.println(F("Performing a factory reset: "));
  if ( ! ble.factoryReset() )
    error(F("Couldn't factory reset"));

  ble.verbose(false); 

  String cmd = "AT+GAPDEVNAME=" + name;
  ble.sendCommandCheckOK(cmd.c_str());
  ble.sendCommandCheckOK("ATZ");
  ble.echo(false);
  ble.sendCommandCheckOK("AT+HWModeLED=MODE");

  int cnt = 0;
  Serial.println(F("Waiting for connection to continue..."));
  while (! ble.isConnected()) 
  {
      Serial.print(".");
      if (++cnt > 80) 
      {
        cnt = 0; 
        Serial.println();
      }
      
      delay(500);
  }

  Serial.println();

  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("Ready!"));
}


//
// Check if the client is connected
bool AdaUart::isConnected()
{
  ble.print("+++\n");
  bool isConn = ble.isConnected();
  ble.print("+++\n");
  return isConn;
}

void AdaUart::sendString(const String& data)
{
  ble.println(data.c_str());  
}

String AdaUart::getString()
{
  String ret = "";
  while (ble.available()) 
  {
    char c =  ble.read();
    ret.concat(c);
  }

  return ret;
}

uint8_t AdaUart::hasString()
{
  return ble.available();
}


    


