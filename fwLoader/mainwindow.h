#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtSerialPort/QSerialPort"
#include "qserialport.h"
#include <QSerialPortInfo>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

struct s_flags {
    uint8_t serialPort;
};
enum s_flag{
    s_connect = 0,
    s_disconnect
};

struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };
void openSerialPort();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btsselect_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_btnSerial_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    QSerialPort *m_serial = nullptr;
    Settings p;
    s_flags s_flg;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
