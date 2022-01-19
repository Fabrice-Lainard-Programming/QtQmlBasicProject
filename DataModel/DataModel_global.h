#ifndef DATAMODEL_GLOBAL_H
#define DATAMODEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATAMODEL_LIBRARY)
#  define DATAMODEL_EXPORT Q_DECL_EXPORT
#else
#  define DATAMODEL_EXPORT Q_DECL_IMPORT
#endif

#endif // DATAMODEL_GLOBAL_H
