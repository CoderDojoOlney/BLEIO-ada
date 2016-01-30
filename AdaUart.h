/*****************************************************************************/
// Robot remote control via Bluetooth LE
// Author: Anthony Abbot
// Date: 27 Dec 2015
// 
// This code has been developed for use by the Olney Coder Dojo club
//
// Class to better encapsulate the BLE UART protocol for receiving commands
// and sending back data
//
/*****************************************************************************/

#ifndef __AdaUart_h__
#define __AdaUart_h__

#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>

// text buffer for reading commands
#define BLEIO_BUFSIZE                    (20)

class AdaUart
{
  private:
    uint8_t recvbuffer[BLEIO_BUFSIZE + 1];
    char    sendbuffer[BLEIO_BUFSIZE + 1];
    Adafruit_BluefruitLE_SPI ble;
  
  public:
    AdaUart();
    void initBle(String name);
    bool isConnected();
    uint8_t hasString();
    String getString();
    void sendString(const String& data);
};

#endif // __AdaUart_h__
