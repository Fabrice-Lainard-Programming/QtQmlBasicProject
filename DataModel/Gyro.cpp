// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------



#include "Gyro.h"

using namespace DICE;

// -------------------------------------------------------------------------

Gyro::Gyro(const QString& name,SignalStrength signalStrength, SensorState state)
    : Sensor(name,signalStrength,state)
{
}


// -------------------------------------------------------------------------

float Gyro::getAngle() const
{
    return _angle;
}

void Gyro::setAngle(float angle)
{
    _angle = angle;
  emit angleChanged(_angle);
}

