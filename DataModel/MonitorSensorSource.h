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
#include <QSharedData>
#include <QExplicitlySharedDataPointer>
#include <QThread>
#include <QQueue>
#include <QMutexLocker>
#include <QTimer>
#include <QDateTime>

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
 * @brief The MonitorSensorSource class monitors data coming from the acquisition
 * layer and changes the display accordingly
 * @note Works in multithreads
 */
class DATAMODEL_EXPORT MonitorSensorSource : public QThread,public QSharedData
{
    Q_OBJECT
public:
    /**
     * @brief create add a shared monitor
     * @return a shared object
     */
    static QExplicitlySharedDataPointer<MonitorSensorSource> create(QExplicitlySharedDataPointer<SensorModel> model)
    {
        return QExplicitlySharedDataPointer<MonitorSensorSource>(new MonitorSensorSource(model));
    }

    /**
     * @brief stop
     */
    void stop();


protected:
    explicit MonitorSensorSource(QExplicitlySharedDataPointer<SensorModel> model);
    Q_DISABLE_COPY(MonitorSensorSource)
    void run() override;
    void readData();
    void updateUI();
    void initUITimer();

private:
    QExplicitlySharedDataPointer<SensorModel> _model;
    QThread _workerThread;
    bool _exit = false;
    QMutex _mutex;
    QQueue<QExplicitlySharedDataPointer<UpdateBlock>> _queue;
    QTimer *_UIThreadTimer = nullptr;
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


} // namespace
