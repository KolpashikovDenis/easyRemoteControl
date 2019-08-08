#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <time.h>
#include <stdlib.h>

#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_send->setFocus();
//    QRect r = QApplication::desktop()->screenGeometry();
//    QString resolution = QString::number(r.width())+"x"+QString::number(r.height());
    QString s = qApp->applicationDirPath();

    fullIdName = s + "/id";

    // TODO: прочитать файл с ID
    if( !isIDPresent() )
    {
        idString = generateID(lenID);
        saveID();
    }
    ui->statusBar->showMessage(idString);
    // TODO: создать сокет, коннект на сервер, отправить инжормацию, получить информацию о сервере

}

MainWindow::~MainWindow()
{

    delete ui;
}

QString MainWindow::generateID(int len)
{
    QString res;
    srand(::time(0));
    int a = alphabet.length();
    for( int i = 0; i< len; i++)
    {
        res.append(alphabet[rand()%a]);
    }

    return res;
}

bool MainWindow::isIDPresent()
{
    QFileInfo info(fullIdName);
    qint64 fileSize;
    if(info.exists())
    {
        fileSize = info.size();
        if( fileSize == 0 )
        {
            return false;
        }
    }

    QFile *idFile = new QFile(fullIdName);
    if(idFile->exists())
    {
        idFile->open(QIODevice::ReadOnly);
        idString = QString(idFile->readLine());
    }

    if(idString.isEmpty())
    {
        return false;
    }

    return true;
}

void MainWindow::saveID()
{
    QFile file(fullIdName);
    file.open(QIODevice::WriteOnly);
    file.write(idString.toUtf8(), idString.length());
    file.close();
}
