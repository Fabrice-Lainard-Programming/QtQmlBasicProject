// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------



#include "Anenometer.h"

using namespace DICE;

// -------------------------------------------------------------------------

Anenometer::Anenometer(const QString& name,SignalStrength signalStrength, SensorState state)
    : Sensor(name,signalStrength,state)
{
}

// -------------------------------------------------------------------------

float Anenometer::getWindDirection() const
{
    return _windDirection;
}

void Anenometer::setWindDirection(float dir)
{
    _windDirection = dir;
    emit windDirectionChanged(_windDirection);
}

// -------------------------------------------------------------------------

float Anenometer::getWindGust() const
{
    return _windGust;
}

void Anenometer::setWinGust(float gust)
{
    _windGust = gust;
    emit windGustChanged(_windGust);
}

