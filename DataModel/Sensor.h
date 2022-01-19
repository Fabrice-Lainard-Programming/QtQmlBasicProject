// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#pragma once

#include "DataModel_global.h"
#include <QObject>
#include <QSharedData>
#include <QExplicitlySharedDataPointer>
#include <QString>
#include <QDateTime>

namespace DICE
{

typedef int SignalStrength;

/**
 * @brief The SensorState enum list device status
 */
enum SensorState
{
    Nominal,
    Warning,
    Error,
};


/**
 * @brief Sensor is a base class of all sensors
 * @note this class should be derived
 */
class DATAMODEL_EXPORT Sensor : public QObject,public QSharedData
{
    Q_OBJECT

public:

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(SignalStrength signalStrength READ getSignalStrength WRITE setSignalStrength NOTIFY signalStrengthChanged)
    Q_PROPERTY(SensorState state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString type READ getType)
    Q_PROPERTY(QDateTime dt READ getUpdateTime NOTIFY dateChanged)

signals:
    void nameChanged(const QString& name);
    void signalStrengthChanged(SignalStrength signalStrength);
    void stateChanged(SensorState state);
    void dateChanged(const QDateTime& dt);

public:

    /**
     * @brief name gets the name of the sensor
     * @return a name
     */
    QString getName() const;
    /**
     * @brief setName sets the name of the sensor
     * @param name the new name
     */
    void setName(const QString& name);
    /**
     * @brief signalStrength retrieve the signal strength of this sensor
     * @return signal strength in percent [0,100]
     */
    SignalStrength getSignalStrength() const;
    /**
     * @brief setSignalStrength change the signal strength of the sensor
     * @param strength the new signal strength in percent [0,100]
     */
    void setSignalStrength(SignalStrength strength);
    /**
     * @brief state gets the state of the sensor
     * @return
     */
    SensorState getState() const;
    /**
     * @brief setState sets the state of the sensor
     * @param state the new state
     */
    void setState(SensorState state);

    /**
     * @brief getType gets the type of the sensor base on its classname
     * @return the type
     */
    QString getType () const;

    /**
     * @brief getUpdateTime
     * @return
     */
    QDateTime getUpdateTime() const;

    /**
     * @brief setUpdateTime
     * @param updateTime
     */
    void setUpdateTime(const QDateTime &updateTime);

protected:
    /**
     * @brief Sensor Ctor
     * @param parent parent object
     */
    explicit Sensor(const QString& name,SignalStrength signalStrength, SensorState state);
    Q_DISABLE_COPY(Sensor)

protected:
    QString _name;
    int _signalStrength;
    SensorState _state = SensorState::Error;
    QDateTime _updateTime;

};

} // namespace


