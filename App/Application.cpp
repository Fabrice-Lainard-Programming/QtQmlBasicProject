// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#include "Application.h"
#include "Anenometer.h"
#include "Compass.h"
#include "GPS.h"
#include "Gyro.h"
#include "SensorModel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>


// -------------------------------------------------------------------------

using namespace DICE;

// -------------------------------------------------------------------------



Application::Application(int &argc, char **argv,QExplicitlySharedDataPointer<MonitorCallBack> mockServer)
    : QGuiApplication(argc,argv),_monitorCallBack(mockServer)
{
    setOrganizationDomain("FLProgramming");
    setApplicationName("App");
    setApplicationVersion("1.0.0");
    qRegisterMetaType<WGS84Coordinates>();
    initModel();

}

// -------------------------------------------------------------------------


void Application::initModel()
{
    // build sensor model
    _model = SensorModel::create();
    _model->addSensor(GPS::create(QObject::tr("Front gps"),0,SensorState::Error));
    _model->addSensor(GPS::create(QObject::tr("Rear gps"),0,SensorState::Error));
    _model->addSensor(GPS::create(QObject::tr("Starboard gps"),0,SensorState::Error));
    _model->addSensor(GPS::create(QObject::tr("Port gps"),0,SensorState::Error));

    _model->addSensor(Compass::create(QObject::tr("Compass #1"),0,SensorState::Error));
    _model->addSensor(Compass::create(QObject::tr("Compass #2"),0,SensorState::Error));
    _model->addSensor(Compass::create(QObject::tr("Compass #3"),0,SensorState::Error));
    _model->addSensor(Compass::create(QObject::tr("Compass #4"),0,SensorState::Error));

    _model->addSensor(Anenometer::create(QObject::tr("Primary anenometer"),0,SensorState::Error));
    _model->addSensor(Anenometer::create(QObject::tr("Secondary anenometer"),0,SensorState::Error));

    _model->addSensor(Gyro::create(QObject::tr("Main gyro"),0,SensorState::Error));
    _model->addSensor(Gyro::create(QObject::tr("Backup gyro"),0,SensorState::Error));

    _monitorSource = MonitorSensorSource::create(_model,_monitorCallBack);
}


// -------------------------------------------------------------------------


int Application::run()
{
    // create qml view
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    // associate qml model to qml item
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     this, [&](QObject *obj, const QUrl &objUrl) {
        if (obj && url == objUrl)
        {
          obj->setProperty("sensorModel", QVariant::fromValue(_model.data()));
        }}, Qt::QueuedConnection);

    // load qml file
    engine.load(url);

    // cleanup
    QObject::connect(this, &QCoreApplication::aboutToQuit, [this] ()
    {
        _monitorSource->stop();
    });

    // start monitor thread
    _monitorSource->start();

    return exec();
}


