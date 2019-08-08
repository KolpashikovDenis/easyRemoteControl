#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    int lenID = 24;
    QString fullIdName;
    QString idString;
    QString alphabet = "qwertyuioplkjhgfdsazxcvbnmMNBVCXZASDFGHJKLPOIUYTREWQ1234567890";

    Ui::MainWindow *ui;
    QString generateID(int len);
    bool isIDPresent();
    void saveID();    
};

#endif // MAINWINDOW_H
