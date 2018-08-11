#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "canio.h"
#include <QMainWindow>
#include <QtWidgets>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
   canIO * canObject = nullptr;
   QLabel * statusBarLbl = nullptr;
   QCanBusDevice * device = nullptr;

public slots:
   void connects();
   void sends();
   void processRecievedFrames();
   void disconnectDevice();
   void clearConsole();
   void information();
   void showSettings();



};

#endif // MAINWINDOW_H
