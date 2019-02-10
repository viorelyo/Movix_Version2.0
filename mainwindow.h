#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Controller.h"
#include "Validation.h"
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

    void setController(Controller& c);

private slots:
    void on_admin_clicked();

    void on_loginBtn_clicked();

    void on_user_clicked();

private:
    Ui::MainWindow *ui;
    std::string userName;
    bool newCustomer = false;
    int posUser;
    WatchList newWatchList;
    Controller ctrl;
};

#endif // MAINWINDOW_H
