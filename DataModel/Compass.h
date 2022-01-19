// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#pragma once


#include "Sensor.h"
#include <QObject>


namespace DICE
{

/**
 * @brief The Compass class is a specific sensor
 */
class DATAMODEL_EXPORT Compass : public Sensor
{
    Q_OBJECT
public:

    Q_PROPERTY(float boatDirection READ getBoatDirection WRITE setBoatDirection NOTIFY boatDirectionChanged)



signals:
    void boatDirectionChanged(float boatDirection);


public:

    /**
     * @brief create add a specific Sensor as a shared object
     * @param name name of the sensor
     * @param signalStrength signal strenght
     * @param state initial state of this sensor
     * @return a shared object
     */
    static QExplicitlySharedDataPointer<Compass> create(const QString& name,SignalStrength signalStrength, SensorState state)
    {
        return QExplicitlySharedDataPointer<Compass>(new Compass(name,signalStrength,state));
    }


    /**
     * @brief getBoatDirection gets the boat direction
     * @return the boat direction in degrees
     */
    float getBoatDirection() const;
    /**
     * @brief setBoatDirection sets the boat direction
     * @param dir the boat direction in degrees
     */
    void setBoatDirection(float dir);

protected:
    explicit Compass(const QString& name,SignalStrength signalStrength, SensorState state);
     Q_DISABLE_COPY(Compass)


private:
    float _boatDirection = 0;


};

} // namespace


