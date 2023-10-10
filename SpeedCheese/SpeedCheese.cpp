// SpeedCheese.cpp
#include "SpeedCheese.h"

SpeedCheese::SpeedCheese(QTRSensors& qtr, float kp, float ki, float kd) :
    _qtr(qtr), _kp(kp), _ki(ki), _kd(kd), _previousError(0), _integral(0) {}

void SpeedCheese::update() {
    uint16_t position = _qtr.readLineBlack();
    int error = position - 2500;
    
    _integral += error;
    int derivative = error - _previousError;
    
    int pidValue = _kp*error + _ki*_integral + _kd*derivative;
    
    calculateMotorSpeeds(pidValue);
    
    _previousError = error;
}

void SpeedCheese::calculateMotorSpeeds(int pidValue) {
    int baseSpeed = 512;  // Base speed at which motors will run
    int correction = pidValue / 25;  // Adjust this value to suit your robot's behavior
    
    _leftMotorSpeed = baseSpeed + correction;
    _rightMotorSpeed = baseSpeed - correction;
    
    // Ensure motor speeds are within valid range
    _leftMotorSpeed = constrain(_leftMotorSpeed, 0, 1023);
    _rightMotorSpeed = constrain(_rightMotorSpeed, 0, 1023);
}

int SpeedCheese::getMotorSpeed(bool isLeftMotor) {
    return isLeftMotor ? _leftMotorSpeed : _rightMotorSpeed;
}
