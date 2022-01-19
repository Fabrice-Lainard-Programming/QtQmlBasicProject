// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#include "Application.h"
#include "MockServer.h"

// -------------------------------------------------------------------------

using namespace DICE;

// -------------------------------------------------------------------------


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    auto mockServer = QExplicitlySharedDataPointer<MockServer>(new MockServer());
    Application app(argc,argv,mockServer);

    return app.run();
}
