QT -= gui

TEMPLATE = lib
DEFINES += DATAMODEL_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Anenometer.cpp \
    Compass.cpp \
    GPS.cpp \
    Gyro.cpp \
    MonitorSensorSource.cpp \
    Sensor.cpp \
    SensorModel.cpp

HEADERS += \
    Anenometer.h \
    Compass.h \
    DataModel_global.h \
    GPS.h \
    Gyro.h \
    MonitorCallBack.h \
    MonitorSensorSource.h \
    Sensor.h \
    SensorModel.h \
    WGS84Coordinates.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
