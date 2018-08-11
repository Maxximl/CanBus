#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H
#include <QCanBusDeviceInfo>
#include <QCanBus>
#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

      struct Settings
      {
          enum bitRate {btrt500000 = 500000};

      };
        Settings getSettings();

private:
    Ui::SettingDialog *ui;
    QList<QCanBusDeviceInfo> availableDevices;
    void defaultSettings();

};

#endif // SETTINGDIALOG_H
