// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#pragma once

#include "DataModel_global.h"
#include "Sensor.h"
#include <QAbstractListModel>
#include <QSharedData>
#include <QExplicitlySharedDataPointer>

namespace DICE
{

/**
 * @brief The SensorModel class standard interface for model that represent sensors
 */
class DATAMODEL_EXPORT SensorModel : public QAbstractListModel, public QSharedData
{
    Q_OBJECT
public:
    enum SensorRoles {
        NameRole = Qt::UserRole + 1,
        SignalStrengthRole,
        StateRole,
        StateColorRole,
        TypeRole,
        IsNewSectionRole,
        ObjectRole
    };

    /**
     * @brief create add a shared sensor model
     * @return a shared object
     */
    static QExplicitlySharedDataPointer<SensorModel> create()
    {
        return QExplicitlySharedDataPointer<SensorModel>(new SensorModel());
    }

    void addSensor(QExplicitlySharedDataPointer<Sensor> sensor);
    QExplicitlySharedDataPointer<Sensor> beginUpdate(int index);
    void endUpdate(int index);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant get(int row) const;
    QList<QExplicitlySharedDataPointer<Sensor> >& getSensors();

protected:
    explicit SensorModel();
    Q_DISABLE_COPY(SensorModel)
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<QExplicitlySharedDataPointer<Sensor>> _sensors;
};

} // namespace
