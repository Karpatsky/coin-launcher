#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "coinsxmldocument.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    connect(ui_->coinNamesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSetCurrentCoin(int)));

    readCoinsFromFile();
    viewCoins();

    debugPrintCoins();
}

MainWindow::~MainWindow()
{
    delete ui_;
}
void MainWindow::readCoinsFromFile()
{
    CoinsXmlDocument options(this);
    options.setFile("coinsoptions.xml");
    options.readFromXml(coins_, basedir_);
}

void MainWindow::viewCoins()
{
    for(const auto &c:coins_)
        ui_->coinNamesComboBox->addItem(c.name.c_str());
}
void MainWindow::getCoinArguments(QStringList& arguments)
{
    arguments<<ui_->pathToDataDirLabel->text();

    if(ui_->rescanCheckBox->isChecked())
        arguments<<ui_->rescanCheckBox->text();
    if(ui_->salvageCheckBox->isChecked())
        arguments<<ui_->salvageCheckBox->text();
    if(ui_->daemonChekBox->isChecked())
        arguments<<ui_->daemonChekBox->text();

    QString manual;
    manual = ui_->manualLineEdit->text();
    manual = manual.trimmed();

    arguments<<manual.split(' ');
}
void MainWindow::onError(QProcess::ProcessError errorCode)
{
    QString message;
    message = tr("ERROR %1:\n%2").arg((int)errorCode).arg(printTextError(errorCode));
    QMessageBox::warning(this, tr("Message"), message);
}
///slots
void MainWindow::onSetCurrentCoin(const int index)
{
    int i=0;
    for(std::set<Coin>::const_iterator c = coins_.cbegin(); c != coins_.cend(); ++c, ++i)
    {
        if(i==index)
        {
            ui_->pathToBinLabel->setText(basedir_ + c->binpath.c_str());
            ui_->pathToDataDirLabel->setText(QString("-datadir=%1%2").arg(basedir_).arg(c->datadirpath.c_str()));
        }
    }
}

void MainWindow::on_LaunchPushButton_clicked()
{
    QString program = ui_->pathToBinLabel->text();
    QStringList arguments;
    getCoinArguments(arguments);

    QProcess *myProcess = new QProcess();
    connect(myProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onError(QProcess::ProcessError)));
    myProcess->start(program, arguments);

    debugPrintLaunch(program, arguments);
}

QString MainWindow::printTextError(QProcess::ProcessError errorCode)
{
    switch (errorCode)
    {
    case QProcess::FailedToStart:
        return "QProcess::FailedToStart";
    case QProcess::Crashed:
        return "QProcess::Crashed";
    case QProcess::Timedout:
        return "QProcess::Timedout";
    case QProcess::WriteError:
        return "QProcess::WriteError";
    case QProcess::ReadError:
        return "QProcess::ReadError";
    case QProcess::UnknownError:
        return "QProcess::UnknownError";
    default:
        return "";
    }
}

///debug
void MainWindow::debugPrintCoins()
{
    qDebug()<<"coins_.size() ="<<coins_.size();
    for(const auto &c: coins_)
    {
        qDebug();
        qDebug()<< c.name.c_str();
        qDebug()<< c.binpath.c_str();
        qDebug()<< c.datadirpath.c_str();
    }
}
void MainWindow::debugPrintLaunch(QString& program, QStringList& arguments)
{
    qDebug();
    qDebug()<<"program = "<<program;
    qDebug()<<"arguments = "<<arguments.join(' ');
}

void MainWindow::debugTryToCreateProcess()
{
    QString program = "notepad";
    QStringList arguments;

    QProcess *myProcess = new QProcess();
    connect(myProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onError(QProcess::ProcessError)));
    myProcess->start(program, arguments);
}

