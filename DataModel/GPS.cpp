// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------



#include "GPS.h"

using namespace DICE;

// -------------------------------------------------------------------------

GPS::GPS(const QString& name,SignalStrength signalStrength, SensorState state)
    : Sensor(name,signalStrength,state)
{
}

// -------------------------------------------------------------------------

const WGS84Coordinates& GPS::getLocation() const
{
    return _wgs84Coordinates;
}

void GPS::setLocation(const WGS84Coordinates& coord)
{
    _wgs84Coordinates = coord;
    emit locationChanged(_wgs84Coordinates);
}
