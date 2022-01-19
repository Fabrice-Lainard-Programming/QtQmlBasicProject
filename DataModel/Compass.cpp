// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------



#include "Compass.h"

using namespace DICE;

// -------------------------------------------------------------------------

Compass::Compass(const QString& name,SignalStrength signalStrength, SensorState state)
    : Sensor(name,signalStrength,state)
{
}

// -------------------------------------------------------------------------

float Compass::getBoatDirection() const
{
    return _boatDirection;
}

void Compass::setBoatDirection(float dir)
{
    _boatDirection = dir;
    emit boatDirectionChanged(_boatDirection);
}
