// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#include "MockServer.h"
#include "Anenometer.h"
#include "Compass.h"
#include "GPS.h"
#include "Gyro.h"
#include "SensorModel.h"
#include <QQueue>




// -------------------------------------------------------------------------

using namespace DICE;

// -------------------------------------------------------------------------


MockServer::MockServer()
{
}

// -------------------------------------------------------------------------

void MockServer::readData(QExplicitlySharedDataPointer<SensorModel>& model,
              QQueue<QExplicitlySharedDataPointer<UpdateBlock>>& queue)
{
    int updtIndex = rand()%(model->rowCount());
    // simulation of data acquisition from server side
    // The example here is not generic as it is rarely the case in real life
    QExplicitlySharedDataPointer<Sensor> sensor = model->getSensors().at(updtIndex);

    if(sensor->getType().compare("Anenometer") == 0)
    {
        QExplicitlySharedDataPointer<UpdateAnenometer> updtBlck = QExplicitlySharedDataPointer<UpdateAnenometer>(new UpdateAnenometer());
        updtBlck->_sensorIndex = updtIndex;
        updtBlck->_signalStrength = rand()%(100 + 1);
        updtBlck->_state = static_cast<SensorState>(rand()%(3 + 1));
        updtBlck->_dt = QDateTime::currentDateTime();
        updtBlck->_windGust = rand()%(50 + 1);
        updtBlck->_windDirection = rand()%(360 + 1);
        queue.append(updtBlck);
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
        queue.append(updtBlck);
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
            queue.append(updtBlck);
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
                queue.append(updtBlck);
            }
            else
            {
                QExplicitlySharedDataPointer<UpdateBlock> updtBlck = QExplicitlySharedDataPointer<UpdateBlock>(new UpdateBlock());
                updtBlck->_sensorIndex = updtIndex;
                updtBlck->_signalStrength = rand()%(100 + 1);
                updtBlck->_state = static_cast<SensorState>(rand()%(3 + 1));
                updtBlck->_dt = QDateTime::currentDateTime();
                queue.append(updtBlck);
            }
}


