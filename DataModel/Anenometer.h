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
 * @brief The Anenometer class is a specific sensor
 */
class Anenometer : public Sensor
{
    Q_OBJECT
public:

    Q_PROPERTY(float windDirection READ getWindDirection WRITE setWindDirection NOTIFY windDirectionChanged)
    Q_PROPERTY(float windGust READ getWindGust WRITE setWinGust NOTIFY windGustChanged)


signals:
    void windDirectionChanged(float windDirection);
    void windGustChanged(float windGust);

public:

    /**
     * @brief create add a specific Sensor as a shared object
     * @param name name of the sensor
     * @param signalStrength signal strenght
     * @param state initial state of this sensor
     * @return a shared object
     */
    static QExplicitlySharedDataPointer<Anenometer> create(const QString& name,SignalStrength signalStrength, SensorState state)
    {
        return QExplicitlySharedDataPointer<Anenometer>(new Anenometer(name,signalStrength,state));
    }



    /**
     * @brief getWindDirection gets the wind direction
     * @return the wind direction in degrees
     */
    float getWindDirection() const;
    /**
     * @brief setWindDirection sets the wind direction
     * @param dir the wind direction in degrees
     */
    void setWindDirection(float dir);
    /**
     * @brief getWindGust gets wind gust in m/s
     * @return wind gust in m/s
     */
    float getWindGust() const;
    /**
     * @brief setWinGust sets wind gust in m/s
     * @param wind gust in m/s
     */
    void setWinGust(float gust);


protected:
    explicit Anenometer(const QString& name,SignalStrength signalStrength, SensorState state);
     Q_DISABLE_COPY(Anenometer)

private:
    float _windDirection = 0;
    float _windGust = 0;

};

} // namespace


