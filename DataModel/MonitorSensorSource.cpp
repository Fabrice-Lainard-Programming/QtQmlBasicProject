// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#include "MonitorSensorSource.h"
#include "Anenometer.h"
#include "GPS.h"
#include "Gyro.h"
#include "Compass.h"
#include <QDebug>
#include <QDateTime>

using namespace DICE;

// -------------------------------------------------------------------------

MonitorSensorSource::MonitorSensorSource(QExplicitlySharedDataPointer<SensorModel> model,QExplicitlySharedDataPointer<MonitorCallBack> callback)
    : _model(model),_callback(callback)
{
    initUITimer();
}

// -------------------------------------------------------------------------

void MonitorSensorSource::run()
{
    UpdateBlock updtBlck;
    while(!_exit)
    {
        readData();
        QThread::msleep(500);
    }
}

// -------------------------------------------------------------------------

void MonitorSensorSource::stop()
{
    _exit=true;
    _UIThreadTimer->stop();
    while(isRunning())
    {
        QThread::msleep(500);
    }
    _UIThreadTimer->deleteLater();
}

// -------------------------------------------------------------------------

void MonitorSensorSource::readData()
{
    QMutexLocker lock(&_mutex);
    if(_callback)
    {
        _callback->readData(_model,_queue);
    }
}

// -------------------------------------------------------------------------

void MonitorSensorSource::updateUI()
{
    QMutexLocker lock(&_mutex);
    // Update UI
    // The example here is not generic as it is rarely the case in real life
    while (!_queue.isEmpty())
    {
        QExplicitlySharedDataPointer<UpdateBlock> updtBlck = _queue.dequeue();
        QExplicitlySharedDataPointer<Sensor> sensor = _model->beginUpdate(updtBlck->_sensorIndex);
        sensor->setSignalStrength(updtBlck->_signalStrength);
        sensor->setState(updtBlck->_state);
        sensor->setUpdateTime(updtBlck->_dt);

        // update anenometer if needed
        if(sensor->getType().compare("Anenometer") == 0)
        {
            UpdateAnenometer* ua = static_cast<UpdateAnenometer*>(updtBlck.data());
            Anenometer* anenometer = static_cast<Anenometer*>(sensor.data());
            anenometer->setWinGust(ua->_windGust);
            anenometer->setWindDirection(ua->_windDirection);
        }
        else
            // update gps if needed
            if(sensor->getType().compare("GPS") == 0)
            {
                UpdateGps* ua = static_cast<UpdateGps*>(updtBlck.data());
                GPS* gps = static_cast<GPS*>(sensor.data());
                gps->setLocation(ua->_wgs84Coordinates);
            }
            else
                // update Gyro if needed
                if(sensor->getType().compare("Gyro") == 0)
                {
                    UpdateGyro* ua = static_cast<UpdateGyro*>(updtBlck.data());
                    Gyro* gyro = static_cast<Gyro*>(sensor.data());
                    gyro->setAngle(ua->_angle);
                }
                else
                    // update Compass if needed
                    if(sensor->getType().compare("Compass") == 0)
                    {
                        UpdateCompass* ua = static_cast<UpdateCompass*>(updtBlck.data());
                        Compass* compass = static_cast<Compass*>(sensor.data());
                        compass->setBoatDirection(ua->_boatDirection);
                    }
        _model->endUpdate(updtBlck->_sensorIndex);
    }
}


// -------------------------------------------------------------------------

void MonitorSensorSource::initUITimer()
{
    _UIThreadTimer = new QTimer(this);
    connect(_UIThreadTimer, &QTimer::timeout, [this]()
    {
        updateUI();
    });
    _UIThreadTimer->start(1500);
}
