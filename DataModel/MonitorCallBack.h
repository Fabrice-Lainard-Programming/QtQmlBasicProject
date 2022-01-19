// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#pragma once

#include "DataModel_global.h"
#include "SensorModel.h"
#include "WGS84Coordinates.h"


namespace DICE
{


/**
 * @brief The UpdateBlock struct
 */
struct UpdateBlock : public QSharedData
{
    int _sensorIndex = 0;
    int _signalStrength = 0;
    SensorState _state = SensorState::Error;
    QDateTime _dt;
};


/**
 * @brief The UpdateAnenometer struct
 */
struct UpdateAnenometer : public UpdateBlock
{
    float _windDirection = 0;
    float _windGust = 0;
};



/**
 * @brief The UpdateGyro struct
 */
struct UpdateGyro : public UpdateBlock
{
     float _angle = 0;
};


/**
 * @brief The UpdateGps struct
 */
struct UpdateGps : public UpdateBlock
{
    WGS84Coordinates _wgs84Coordinates;
};


/**
 * @brief The UpdateGps struct
 */
struct UpdateCompass : public UpdateBlock
{
    float _boatDirection = 0;
};


/**
 * @brief The MonitorCallBack class
 */
class MonitorCallBack : public QSharedData
{
public:
    /**
     * @brief readData read data from server side and add it to the queue
     * @param model data model containing sensors
     * @param queue a queue to push data updates
     */
    virtual void readData(QExplicitlySharedDataPointer<SensorModel>& model,
                  QQueue<QExplicitlySharedDataPointer<UpdateBlock>>& queue) = 0;

};

} // namespace
