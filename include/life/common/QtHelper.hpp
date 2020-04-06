#ifndef QTHELPER_HPP
#define QTHELPER_HPP

#include <configure.h>


class QDataStream;


DV_LIFE_OPEN_NAMESPACE

enum class DeviceKey;
enum class MotorXKind;
enum class AxisXFeedback;

namespace qthelper {

void registerMetatypes();
void registerMetatypesStreamOperator();

}

DV_LIFE_CLOSE_NAMESPACE

// questi operatori sono chiamati in automatico quando si legge/scrive un valore
// nel file di configurazione usando QSettings

QDataStream& operator<<(QDataStream &out, const dv::life::DeviceKey& obj);
QDataStream& operator>>(QDataStream &in, dv::life::DeviceKey& obj);

QDataStream& operator<<(QDataStream &out, const dv::life::MotorXKind& val);
QDataStream& operator>>(QDataStream &in, dv::life::MotorXKind& obj);

QDataStream& operator<<(QDataStream &out, const dv::life::AxisXFeedback& obj);
QDataStream& operator>>(QDataStream &in, dv::life::AxisXFeedback& obj);


#endif // QTHELPER_HPP
