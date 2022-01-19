// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include "Anenometer.h"
#include "Compass.h"
#include "GPS.h"
#include "Gyro.h"
#include "SensorModel.h"
#include "MonitorSensorSource.h"

// -------------------------------------------------------------------------

using namespace DICE;

// -------------------------------------------------------------------------


int main(int argc, char *argv[])
{
    // init Qt app
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QGuiApplication app(argc, argv);
    app.setOrganizationDomain("FLProgramming");
    app.setApplicationName("App");
    app.setApplicationVersion("1.0.0");


    qRegisterMetaType<WGS84Coordinates>();

    // build sensor model
    QExplicitlySharedDataPointer<SensorModel> model = SensorModel::create();
    model->addSensor(GPS::create(QObject::tr("Front gps"),0,SensorState::Error));
    model->addSensor(GPS::create(QObject::tr("Rear gps"),0,SensorState::Error));
    model->addSensor(GPS::create(QObject::tr("Starboard gps"),0,SensorState::Error));
    model->addSensor(GPS::create(QObject::tr("Port gps"),0,SensorState::Error));

    model->addSensor(Compass::create(QObject::tr("Compass #1"),0,SensorState::Error));
    model->addSensor(Compass::create(QObject::tr("Compass #2"),0,SensorState::Error));
    model->addSensor(Compass::create(QObject::tr("Compass #3"),0,SensorState::Error));
    model->addSensor(Compass::create(QObject::tr("Compass #4"),0,SensorState::Error));

    model->addSensor(Anenometer::create(QObject::tr("Primary anenometer"),0,SensorState::Error));
    model->addSensor(Anenometer::create(QObject::tr("Secondary anenometer"),0,SensorState::Error));

    model->addSensor(Gyro::create(QObject::tr("Main gyro"),0,SensorState::Error));
    model->addSensor(Gyro::create(QObject::tr("Backup gyro"),0,SensorState::Error));


    // Multithread Data Monitoring
    QExplicitlySharedDataPointer<MonitorSensorSource> monitorSource = MonitorSensorSource::create(model);
    monitorSource->start(); // start thread


    // create qml view
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    // associate qml model to qml item
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [&](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
        {
            QCoreApplication::exit(-1);
            return;
        }
        obj->setProperty("sensorModel", QVariant::fromValue(model.data()));
    }, Qt::QueuedConnection);

    // load qml file
    engine.load(url);

     // cleanup
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [monitorSource] ()
    {
        monitorSource->stop();
    });


    return app.exec();
}
