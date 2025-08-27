#include <Vex5.h>

Vex5_AR_Humidity humidity_sensor;
Vex5_AR_Pressure pressure_sensor;
Vex5_Motor motor;

void setup() {
  Serial.begin(115200);
  Vex5.begin();
  humidity_sensor.begin(VEX5_PORT_4);
  motor.begin(VEX5_PORT_2);
  pressure_sensor.begin(VEX5_PORT_1);
  
}

void loop() {
  uint16_t val1 = 0;
  uint16_t val2 = 0;
  val1 = humidity_sensor.getValue();
  delay(10);
  val2 = pressure_sensor.getValue();
  Serial.println("humidity = " + String(val1) + "%");
  Serial.println("pressure = " + String(val2) + "mm");
  if (val1 > 50)
  {
    motor.setSpeed(200);
  }
  else
  {
     motor.setSpeed(-50);
  }
  delay(500);
}
