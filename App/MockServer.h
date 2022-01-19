// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#pragma once

#include "MonitorCallBack.h"

namespace DICE
{

/**
 * @brief The MockServer class
 */
class MockServer : public MonitorCallBack
{
public:
    MockServer();

    /**
     * @brief readData read data from server side and add it to the queue
     * @param model data model containing sensors
     * @param queue a queue to push data updates
     */
    void readData(QExplicitlySharedDataPointer<SensorModel>& model,
                  QQueue<QExplicitlySharedDataPointer<UpdateBlock>>& queue) override;

};

} // namespace
