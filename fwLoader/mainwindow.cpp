#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QSplitter>
#include <QDebug>


QString fwData;
static QStringList binFileName;
int byteArray[5];

//QSerialPort serial1;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_serial(new QSerialPort(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lblnfo->setText(" STM32F429 fw loader V1.0");
    ui->tbFileName->setEnabled(false);
    s_flg.serialPort = s_disconnect;
    p.baudRate = 115200;
    p.dataBits = QSerialPort::Data8;
    p.parity = QSerialPort::NoParity;
    p.stopBits = QSerialPort::OneStop;
    p.flowControl = QSerialPort::NoFlowControl;

    foreach (const QSerialPortInfo &Port, QSerialPortInfo::availablePorts() )
    {
        ui->comboBox->addItem(Port.portName());
    }
    if(ui->comboBox->currentText()==""){
        ui->btnSerial->setText("Refresh");
        ui->listWidget->addItem("[O] serial port not found");
    }else{
        ui->btnSerial->setText("Connect");
    }
}

MainWindow::~MainWindow()
{
    if(s_flg.serialPort == s_connect){
        m_serial->close();
    }
    delete ui;
}


void MainWindow::on_btsselect_clicked()
{
    QFile file(QFileDialog::getOpenFileName(this, tr("Select Bin File"),"",tr(" (*.bin)")));
    if(file.fileName() != ""){
        file.open(QIODevice::ReadOnly);
        QByteArray blob = file.readAll();
        uint32_t line[4];
        uint64_t lineLength=0;
       for (int i =0;i<blob.length();i+=16) {
            line[0] = blob[i]   +(blob[i+1]<<8)+(blob[i+2]<<16)+(blob[i+3]<<24);
            line[1] = blob[i+4] +(blob[i+5]<<8)+(blob[i+6]<<16)+(blob[i+7]<<24);
            line[2] = blob[i+8] +(blob[i+9]<<8)+(blob[i+10]<<16)+(blob[i+11]<<24);
            line[3] = blob[i+12]+(blob[i+13]<<8)+(blob[i+14]<<16)+(blob[i+15]<<24);
            lineLength++;
        }
       ui->listWidget->addItem("[O] file location : "+file.fileName());
       ui->listWidget->addItem("[O] file size : "+QString::number(blob.length()));
     //   qDebug() << blob.toHex();
        binFileName = file.fileName().split(QLatin1Char('/'));
        ui->tbFileName->setText(binFileName[binFileName.length()-1]);
    }else{
        ui->tbFileName->setText("");
    }
}

void MainWindow::openSerialPort()
{
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        ui->listWidget->addItem("[O] "+p.name+" connected.");
        s_flg.serialPort = s_connect;
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

    }
}

void MainWindow::on_btnSerial_clicked()
{
    if(ui->btnSerial->text()=="Refresh"){
        foreach (const QSerialPortInfo &Port, QSerialPortInfo::availablePorts() )
        {
            ui->comboBox->addItem(Port.portName());
        }
        if(ui->comboBox->currentText()==""){
            ui->listWidget->addItem("[O] serial port not found");
        }else{
            ui->btnSerial->setText("Connect");
        }
    }else if(ui->btnSerial->text()=="Connect"){
        p.name = ui->comboBox->currentText();
        openSerialPort();
    }
}



void MainWindow::on_comboBox_activated(const QString &arg1)
{

}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(s_flg.serialPort == s_connect){
        m_serial->close();
        s_flg.serialPort = s_disconnect;
        ui->listWidget->addItem("[O] "+p.name+" disconnected.");
        ui->btnSerial->setText("Connect");
    }
}
