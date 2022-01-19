// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#pragma once

#include "DataModel_global.h"
#include <QObject>

struct DATAMODEL_EXPORT WGS84Coordinates
{
private:
    Q_GADGET
    Q_PROPERTY(double longitude MEMBER _longitude)
    Q_PROPERTY(double latitude MEMBER _latitude)
    Q_PROPERTY(double altitude MEMBER _altitude)
 public:
    double _longitude = 0;
    double _latitude = 0;
    double _altitude = 0;

};


Q_DECLARE_METATYPE(WGS84Coordinates)

