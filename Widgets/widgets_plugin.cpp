// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#include "widgets_plugin.h"
#include <qqml.h>

void WidgetsPlugin::registerTypes(const char *uri)
{
        qmlRegisterModule(uri, 1, 0);
}

