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
#include "MonitorCallBack.h"
#include <QThread>
#include <QQueue>
#include <QMutexLocker>
#include <QTimer>
#include <QDateTime>

namespace DICE
{

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
    static QExplicitlySharedDataPointer<MonitorSensorSource> create(QExplicitlySharedDataPointer<SensorModel> model,
                                                                    QExplicitlySharedDataPointer<MonitorCallBack> callback)
    {
        return QExplicitlySharedDataPointer<MonitorSensorSource>(new MonitorSensorSource(model,callback));
    }

    /**
     * @brief stop monitoring
     */
    void stop();


protected:
    explicit MonitorSensorSource(QExplicitlySharedDataPointer<SensorModel> model,
                                 QExplicitlySharedDataPointer<MonitorCallBack> callback);
    Q_DISABLE_COPY(MonitorSensorSource)
    void run() override;
    void readData();
    void updateUI();
    void initUITimer();

private:
    QExplicitlySharedDataPointer<SensorModel> _model;
    QExplicitlySharedDataPointer<MonitorCallBack> _callback;
    QThread _workerThread;
    bool _exit = false;
    QMutex _mutex;
    QQueue<QExplicitlySharedDataPointer<UpdateBlock>> _queue;
    QTimer *_UIThreadTimer = nullptr;
};


} // namespace
