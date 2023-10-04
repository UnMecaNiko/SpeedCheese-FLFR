// librerias
#include <QTRSensors.h>
#include "SpeedCheese.h"

// llamar librerias
QTRSensors qtr;
SpeedCheese speedCheese(qtr, 0.9, 0.0001, 4);

// Seleccionar cantidad de sensores
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

void setup() {
  // ... (tu código de configuración anterior) ...

  // Asignación pines para los sensores según matriz
  qtr.setSensorPins((const uint8_t[]){ A5, A4, A3, A2, A1, A0 }, SensorCount);

  // ... (resto de tu código de configuración) ...
}

void loop() {
  speedCheese.update();  // Actualizar el controlador PID

  int m1Speed = speedCheese.getMotorSpeed(true);  // Obtener velocidad para el motor izquierdo
  int m2Speed = speedCheese.getMotorSpeed(false);  // Obtener velocidad para el motor derecho

  // ... (tu código para setear las velocidades en los motores) ...
}
