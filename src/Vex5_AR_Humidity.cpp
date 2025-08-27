#include "Vex5.h"
#include "string.h"
// #include "Vex5_Distance.h"

extern uint8_t ver;

int8_t Vex5_AR_Humidity::begin(VEX5_PORT_t port, Vex5_t* shield)
{
  this->shield = shield;
  int8_t result = -1;
  if((port > VEX5_PORT_NO) && (port <= VEX5_PORT_12))
  {
    uint8_t data[256];
    if(ver == 5) {                        //Process port numbers for version 5
      if(port <= VEX5_PORT_3) {
        id = 1;
        this->port = port;
      } else if (port > VEX5_PORT_9) {
        id = 1;
        this->port = port - 6;
      } else {
        id = 0;
        this->port = port - 3;
      }
    } else {                              //Process port numbers for version 0
  	  if(port > VEX5_PORT_6)
  	  {
  	    id = 1;
  	    this->port  = port - 6;
  	  }
  	  else
  	  {
        id = 0;
        this->port = port;
  	  }
    }
  	data[0] = this->port - 1;
    // data[1] = 0xff;
    // data[2] = 0xff;
    // data[3] = 0x14; //id
    // data[4] = 2;   //packet size inst + packet + checksum
    // data[5] = 0x01; //inst
    // data[6] = data[3] + data[4] + data[5]; //Checksum = ~( ID + Length + Instruction + Parameter1 + … Parameter N )
    shield->sendData((VEX5_DEVICE_ID_t)id, VEX5_CMD_AR_HUMIDITY_GET_VAL, data, 1);
  	while(shield->sendData((VEX5_DEVICE_ID_t)id, VEX5_CMD_AR_HUMIDITY_BEGIN, data, 1))
      delay(50);
    int8_t len = shield->receiveData(data);
    if(len > 0)
    {
      result = 0;
  	}
  }
  return result;
}

uint16_t Vex5_AR_Humidity::getValue()
{
  int8_t result = -1;
  if (port)
  {
    uint8_t data[256];
    // data[0] = port - 1;
    // data[1] = 0xff;
    // data[2] = 0xff;
    // data[3] = 0x14; //id
    // data[4] = 3;   //packet size inst + packet + checksum
    // data[5] = 0x02; //inst
    // data[6] = 32; //adress
    // data[7] = data[3] + data[4] + data[5] + data[6]; //Checksum = ~( ID + Length + Instruction + Parameter1 + … Parameter N )
    shield->sendData((VEX5_DEVICE_ID_t)id, VEX5_CMD_AR_HUMIDITY_GET_VAL, data, 1);
    int8_t len = shield->receiveData(data);
    if(len > 0)
    {
      result = 0;
      result = data[2];
      result |= ((int16_t)data[3]) << 8;
    }
  }
  return result;
}

