#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QSet>

#include <set>

#include "coin.h"

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
    Ui::MainWindow *ui_;
    std::set<Coin> coins_;
    QString basedir_;
    void readCoinsFromFile();
    void viewCoins();
    void getCoinArguments(QStringList &arguments);
    QString printTextError(QProcess::ProcessError errorCode);
    void debugPrintCoins();
    void debugPrintLaunch(QString& program, QStringList& arguments);
    void debugTryToCreateProcess();

private slots:
    void on_LaunchPushButton_clicked();
    void onSetCurrentCoin(const int index);
    void onError(QProcess::ProcessError errorCode);
};

#endif // MAINWINDOW_H

