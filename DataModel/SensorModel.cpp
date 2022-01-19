// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

#include "SensorModel.h"

using namespace DICE;

// -------------------------------------------------------------------------


SensorModel::SensorModel()
    : QAbstractListModel()
{

}

// -------------------------------------------------------------------------

void SensorModel::addSensor(QExplicitlySharedDataPointer<Sensor> sensor)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _sensors << sensor;
    endInsertRows();
}

// -------------------------------------------------------------------------

QExplicitlySharedDataPointer<Sensor> SensorModel::beginUpdate(int index)
{
    return _sensors.at(index);
}

// -------------------------------------------------------------------------


void SensorModel::endUpdate(int idx)
{
  emit dataChanged(index(idx,0), index(idx,0));
}


// -------------------------------------------------------------------------

int SensorModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return _sensors.count();
}

// -------------------------------------------------------------------------

QVariant SensorModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= _sensors.count())
        return QVariant();
    QExplicitlySharedDataPointer<Sensor> sensor = _sensors[index.row()];
    if (role == NameRole)
        return sensor->getName();
    else if (role == SignalStrengthRole)
        return sensor->getSignalStrength();
    else if (role == StateRole)
        return sensor->getState();
    else if (role == StateColorRole)
    {
        switch(sensor->getState())
        {
        case Nominal : return "Green";
        case Warning : return "Yellow";
        default:
        case Error : return "Red";
        }
    }

    else if (role == TypeRole)
        return sensor->getType();
    else if (role == IsNewSectionRole)
    {
        if (index.row()-1 < 0)
            return QVariant::fromValue(0);
        QExplicitlySharedDataPointer<Sensor> lastSensor = _sensors[index.row()-1];
        int v = lastSensor->getType().compare(sensor->getType()) == 0 ? 0 : 1;
        return v;
    }
    else if (role == ObjectRole)
        return QVariant::fromValue(sensor.data());
    return QVariant();
}

// -------------------------------------------------row------------------------

QHash<int, QByteArray> SensorModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[SignalStrengthRole] = "signalStrength";
    roles[StateRole] = "state";
    roles[StateColorRole] = "statecolor";
    roles[TypeRole] = "type";
    roles[IsNewSectionRole] = "isNewSection";
    roles[ObjectRole] = "object";
    return roles;
}


// -------------------------------------------------------------------------

QList<QExplicitlySharedDataPointer<Sensor> >& SensorModel::getSensors()
{
    return _sensors;
}

// -------------------------------------------------------------------------

QVariant SensorModel::get(int row) const
{
    const QModelIndex idx = index(row,0);
    if( !idx.isValid() )
        return QVariant();
    QVariant data = idx.data();
    return data;
}
