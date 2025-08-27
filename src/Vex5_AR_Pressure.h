#ifndef VEX5_AR_PRESSURE_H_
#define VEX5_AR_PRESSURE_H_
#include <Arduino.h>
#include "Vex5.h"

class Vex5_AR_Pressure : public Vex5_InternalProtocol
{
private:
  Vex5_t* shield;
  int port;
  int id;
public:
  Vex5_AR_Pressure() : port(0){};
  int8_t begin(VEX5_PORT_t port, Vex5_t *shield = &Vex5);
  uint16_t getValue();
};

#endif