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

MonitorSensorSource::MonitorSensorSource(QExplicitlySharedDataPointer<SensorModel> model)
    : _model(model)
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
    int updtIndex = rand()%(_model->rowCount());
    // simulation of data acquisition from server side
    // The example here is not generic as it is rarely the case in real life
    QExplicitlySharedDataPointer<Sensor> sensor = _model->getSensors().at(updtIndex);

    if(sensor->getType().compare("Anenometer") == 0)
    {
        QExplicitlySharedDataPointer<UpdateAnenometer> updtBlck = QExplicitlySharedDataPointer<UpdateAnenometer>(new UpdateAnenometer());
        updtBlck->_sensorIndex = updtIndex;
        updtBlck->_signalStrength = rand()%(100 + 1);
        updtBlck->_state = static_cast<SensorState>(rand()%(3 + 1));
        updtBlck->_dt = QDateTime::currentDateTime();
        updtBlck->_windGust = rand()%(50 + 1);
        updtBlck->_windDirection = rand()%(360 + 1);
        _queue.append(updtBlck);
    }
    if(sensor->getType().compare("GPS") == 0)
    {
        QExplicitlySharedDataPointer<UpdateGps> updtBlck = QExplicitlySharedDataPointer<UpdateGps>(new UpdateGps());
        updtBlck->_sensorIndex = updtIndex;
        updtBlck->_signalStrength = rand()%(100 + 1);
        updtBlck->_state = static_cast<SensorState>(rand()%(3));
        updtBlck->_dt = QDateTime::currentDateTime();
        updtBlck->_wgs84Coordinates._longitude = rand()%(180 + 1);
        updtBlck->_wgs84Coordinates._latitude = rand()%(180 + 1);
        updtBlck->_wgs84Coordinates._altitude = rand()%(3);
        _queue.append(updtBlck);
    }
    else
        if(sensor->getType().compare("Gyro") == 0)
        {
            QExplicitlySharedDataPointer<UpdateGyro> updtBlck = QExplicitlySharedDataPointer<UpdateGyro>(new UpdateGyro());
            updtBlck->_sensorIndex = updtIndex;
            updtBlck->_signalStrength = rand()%(100 + 1);
            updtBlck->_state = static_cast<SensorState>(rand()%(3));
            updtBlck->_dt = QDateTime::currentDateTime();
            updtBlck->_angle = rand()%(10 + 1);
            _queue.append(updtBlck);
        }
        else
            if(sensor->getType().compare("Compass") == 0)
            {
                QExplicitlySharedDataPointer<UpdateCompass> updtBlck = QExplicitlySharedDataPointer<UpdateCompass>(new UpdateCompass());
                updtBlck->_sensorIndex = updtIndex;
                updtBlck->_signalStrength = rand()%(100 + 1);
                updtBlck->_state = static_cast<SensorState>(rand()%(3));
                updtBlck->_dt = QDateTime::currentDateTime();
                updtBlck->_boatDirection = rand()%(10 + 1);
                _queue.append(updtBlck);
            }
            else
            {
                QExplicitlySharedDataPointer<UpdateBlock> updtBlck = QExplicitlySharedDataPointer<UpdateBlock>(new UpdateBlock());
                updtBlck->_sensorIndex = updtIndex;
                updtBlck->_signalStrength = rand()%(100 + 1);
                updtBlck->_state = static_cast<SensorState>(rand()%(3 + 1));
                updtBlck->_dt = QDateTime::currentDateTime();
                _queue.append(updtBlck);
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
