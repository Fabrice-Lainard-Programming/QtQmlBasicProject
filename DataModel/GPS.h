// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#pragma once


#include "Sensor.h"
#include "WGS84Coordinates.h"
#include <QObject>


namespace DICE
{


/**
 * @brief The GPS class is a specific sensor
 */
class DATAMODEL_EXPORT GPS : public Sensor
{
    Q_OBJECT
public:

    Q_PROPERTY(WGS84Coordinates location READ getLocation WRITE setLocation NOTIFY locationChanged)

signals:
    void locationChanged(const WGS84Coordinates& location);

public:

    /**
     * @brief create add a specific Sensor as a shared object
     * @param name name of the sensor
     * @param signalStrength signal strenght
     * @param state initial state of this sensor
     * @return a shared object
     */
    static QExplicitlySharedDataPointer<GPS> create(const QString& name,SignalStrength signalStrength, SensorState state)
    {
        return QExplicitlySharedDataPointer<GPS>(new GPS(name,signalStrength,state));
    }


    /**
     * @brief getLocation gets the location of the boat
     * @return the boat coordinates in WGS84 system
     */
    const WGS84Coordinates& getLocation() const;
    /**
     * @brief setLocation sets the boat location
     * @param the boat coordinates in WGS84 system
     */
    void setLocation(const WGS84Coordinates& coord);


protected:
    explicit GPS(const QString& name,SignalStrength signalStrength, SensorState state);
     Q_DISABLE_COPY(GPS)

private:
    WGS84Coordinates _wgs84Coordinates;


};

} // namespace


