// SpeedCheese.h
#ifndef SPEED_CHEESE_H
#define SPEED_CHEESE_H

#include <QTRSensors.h>

class SpeedCheese {
public:
    SpeedCheese(QTRSensors& qtr, float kp, float ki, float kd);
    void update();
    int getMotorSpeed(bool isLeftMotor);

private:
    QTRSensors& _qtr;
    float _kp, _ki, _kd;
    int _previousError;
    int _integral;
    int _leftMotorSpeed;
    int _rightMotorSpeed;

    void calculateMotorSpeeds(int error);
};

#endif
