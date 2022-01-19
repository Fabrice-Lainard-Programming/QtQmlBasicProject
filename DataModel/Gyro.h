// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#pragma once


#include "Sensor.h"




namespace DICE
{


/**
 * @brief The Gyro class is a specific sensor
 */
class DATAMODEL_EXPORT Gyro :  public Sensor
{
 Q_OBJECT
public:

    Q_PROPERTY(float angle READ getAngle WRITE setAngle NOTIFY angleChanged)


signals:
    void angleChanged(float angle);

public:

    /**
     * @brief create add a specific Sensor as a shared object
     * @param name name of the sensor
     * @param signalStrength signal strenght
     * @param state initial state of this sensor
     * @return a shared object
     */
    static QExplicitlySharedDataPointer<Gyro> create(const QString& name,SignalStrength signalStrength, SensorState state)
    {
        return QExplicitlySharedDataPointer<Gyro>(new Gyro(name,signalStrength,state));
    }

    /**
     * @brief getAngle gets angle
     * @return angle in degrees
     */
    float getAngle() const;
    /**
     * @brief setAngle sets angle
     * @param angle in degrees
     */
    void setAngle(float angle);

protected:
    explicit Gyro(const QString& name,SignalStrength signalStrength, SensorState state);
     Q_DISABLE_COPY(Gyro)

private:
    float _angle = 0;

};

} // namespace


