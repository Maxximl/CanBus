#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QDebug>
#include <string>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    defaultSettings();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

//SettingDialog::settings SettingDialog::getSettings()
//{
//        settings setting;
//        qDebug() << setting.bitRate[0];
//        return setting;
//}

SettingDialog::Settings SettingDialog::getSettings()
{
    Settings set;

    return set;
}

void SettingDialog::defaultSettings()
{
    QStringList plugins;
    plugins << "socketcan" << "tinycan";
    ui->canPluginComboBox->addItems(plugins);
    ui->canPluginComboBox->setCurrentText("default");
    QString currentPlugin;
    currentPlugin = ui->canPluginComboBox->currentText();




    QString errorMessage;
    availableDevices = QCanBus::instance()->availableDevices(QString(currentPlugin), &errorMessage);
    for ( QCanBusDeviceInfo dev : availableDevices)
    {
        ui->canInterfaceComboBox->addItem(dev.name());
    }

}
