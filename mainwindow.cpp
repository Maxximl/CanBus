#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canObject = new canIO;


    statusBarLbl = new QLabel;
    ui->statusBar->addPermanentWidget(statusBarLbl);
    ui->sendButon->setEnabled(false);
   QObject::connect(ui->actionConnect,SIGNAL(triggered()),this, SLOT(connects()));
   QObject::connect(ui->sendButon, SIGNAL(clicked()),this, SLOT(sends()));
   QObject::connect(ui->actionDisconnect, SIGNAL(triggered()),this,SLOT(disconnectDevice()));
   QObject::connect(ui->actionClear, SIGNAL(triggered()), this, SLOT(clearConsole()));
   QObject::connect(ui->actionInformation, SIGNAL(triggered()),this, SLOT(information()));
   QObject::connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(showSettings()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete canObject;
    delete device;
}

void MainWindow::connects()
{
    statusBarLbl->setText(canObject->createDev());
    device = canObject->getDevice();
    ui->sendButon->setEnabled(true);
    QObject::connect(device, SIGNAL(framesReceived()), this, SLOT(processRecievedFrames()));
}

 void MainWindow::sends()
{       bool ok;
     const quint32 id = ui->idLineEdit->text().toUInt(&ok, 16);

     QByteArray frm = ui->dataLineEdit->text().toUtf8();

    ui->sentMessagePlain->appendPlainText(canObject->sendFrame(id, frm));
}

 void MainWindow::processRecievedFrames()
 {    if (ui->getFramesCheckBox->isChecked()){
        QCanBusFrame frame;


       if(device->framesAvailable()){

            frame = device->readFrame();
            ui->getMessagePlain->appendPlainText(frame.toString());
        }
     }
 }
void MainWindow::disconnectDevice()
{
    statusBarLbl->setText(canObject->disconnectDevice());
    ui->sendButon->setEnabled(false);

}

void MainWindow::clearConsole()
{
    ui->getMessagePlain->clear();
    ui->sentMessagePlain->clear();
}

void MainWindow::information()
{
    QList<QCanBusDeviceInfo> dev;
    dev = canObject->info();
    int count = 0;
    for (QCanBusDeviceInfo devices : dev)
    {
        count++;

    QString name = devices.name();
    QString isVirtual = devices.isVirtual() ? "virtual" : "not virtual";
    ui->sentMessagePlain->appendPlainText(QString("Device #%1: %2 --- %3").arg(QString::number(count)).arg(name).arg(isVirtual));
    }
}


void MainWindow::showSettings()
{
    canObject->showSettingDialog();
}
