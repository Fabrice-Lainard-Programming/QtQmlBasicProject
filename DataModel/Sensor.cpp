// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#include "Sensor.h"

using namespace DICE;

// -------------------------------------------------------------------------

Sensor::Sensor(const QString& name,SignalStrength signalStrength, SensorState state)
 : _name(name),_signalStrength(signalStrength),_state(state)
{
}


// -------------------------------------------------------------------------

QString Sensor::getName() const
{
    return _name;
}

void Sensor::setName(const QString& name)
{
    _name = name;
    emit nameChanged(_name);
}

// -------------------------------------------------------------------------

SignalStrength Sensor::getSignalStrength() const
{
    return _signalStrength;
}

void Sensor::setSignalStrength(SignalStrength strength)
{
    _signalStrength = strength;
    emit signalStrengthChanged(_signalStrength);
}

// -------------------------------------------------------------------------

SensorState Sensor::getState() const
{
    return _state;
}

void Sensor::setState(SensorState state)
{
    _state = state;
    emit stateChanged(_state);
}

// -------------------------------------------------------------------------

QString Sensor::getType () const
{
    QString type= metaObject()->className();
    return type.remove("DICE::");
}

// -------------------------------------------------------------------------

QDateTime Sensor::getUpdateTime() const
{
    return _updateTime;
}

void Sensor::setUpdateTime(const QDateTime &updateTime)
{
    _updateTime = updateTime;
    emit dateChanged(_updateTime);
}
