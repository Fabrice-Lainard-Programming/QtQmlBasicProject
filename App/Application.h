// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#pragma once

#include <QGuiApplication>
#include "MonitorSensorSource.h"
#include "MockServer.h"

namespace DICE
{

class Application : public QGuiApplication
{
     Q_OBJECT
public:
    Application(int &argc, char **argv,QExplicitlySharedDataPointer<MonitorCallBack> mockServer);
    int run();
private:
    void initModel();
private:
    QExplicitlySharedDataPointer<SensorModel> _model;
    QExplicitlySharedDataPointer<MonitorSensorSource> _monitorSource;
    QExplicitlySharedDataPointer<MonitorCallBack> _monitorCallBack;
};

} // namespace
