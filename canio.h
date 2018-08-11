#ifndef CANIO_H
#define CANIO_H
#include "settingdialog.h"
#include <iostream>
#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusDeviceInfo>
#include <QCanBusFrame>
using namespace std;
class canIO : public QObject
{
public:
    canIO();
    ~canIO();
    QString createDev();
    QString sendFrame(int id, QByteArray frm);
    QCanBusFrame readFrame();
    QList<QCanBusDeviceInfo> info();
    QCanBusDevice *getDevice();
    QString disconnectDevice();
    void showSettingDialog();
private:
    QCanBusDevice * device = nullptr;
    QList<QCanBusDeviceInfo> devices;
    SettingDialog * settingObject;
};

#endif // CANIO_H
