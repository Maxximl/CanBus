#include "canio.h"
#include <QDebug>
canIO::canIO()
{

   settingObject = new SettingDialog;

}
canIO::~canIO()
{
    delete device;
}

QString canIO::createDev()
{   QString errorMess;
    if(!QCanBus::instance()->plugins().contains(QStringLiteral("socketcan"))) //изменить с учетом настроек
        return "Error socket";

       device = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("vcan0"));
//       if (!errorMessage.isEmpty())
//           return errorMessage;
        if(!device->connectDevice())
           return "Could not to connect";
        return "Success";


}

QString canIO::sendFrame(int id, QByteArray frm)
{
    QCanBusFrame frame;


    frame.setFrameId(id);
    QByteArray payload(frm);
    frame.setPayload(payload);
    device->writeFrame(frame);
    return (QString::number(frame.frameId(),16).toUpper() + " " + QString::fromUtf8(frame.payload()));
}

QCanBusFrame canIO::readFrame()
{
    return device->readFrame();
}

QList<QCanBusDeviceInfo> canIO::info()
{   QString errorString;
    devices = QCanBus::instance()->availableDevices(QStringLiteral("socketcan"), &errorString);
    if (!errorString.isEmpty())
        qDebug() << errorString;
    return devices;
}

QCanBusDevice * canIO::getDevice()
{
    return device;
}

QString canIO::disconnectDevice()
{   if(!device)
        return "Устройство не подключено";
   if ( device->disconnect())
       return "Устройство успешно отключено";
   else "Не удалось отключить устройство";
}

void canIO::showSettingDialog()
{
    settingObject->show();
}
