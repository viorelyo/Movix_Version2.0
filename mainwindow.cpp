#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "dialogadmin.h"
#include "userdialog.h"
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setController(Controller& c)
{
    this->ctrl = c;
}

void MainWindow::on_admin_clicked()
{
    ui->adminPass->setVisible(true);
    ui->adminPass->setEchoMode(QLineEdit::Password);
    ui->adminPass->clear();
    ui->usernameEdit->clear();
    ui->loginBtn->setVisible(true);
}

void MainWindow::on_loginBtn_clicked()
{
    QString pass = ui->adminPass->text();

    if (pass == "1111") {
        this->hide();

        DialogAdmin adminWindow;
        adminWindow.setAdminCtrl(this->ctrl);
        adminWindow.showContent();
        adminWindow.setModal(true);
        adminWindow.exec();

        this->ctrl = adminWindow.getCtrl();
        this->show();
        ui->adminPass->setVisible(false);
        ui->loginBtn->setVisible(false);
    }
    else {
        QMessageBox::warning(this, "Authorization", "The password is incorrect!");
    }
}

void MainWindow::on_user_clicked()
{
    ui->loginBtn->setVisible(false);
    ui->adminPass->setVisible(false);
    ui->adminPass->clear();


    if (ui->usernameEdit->text().isEmpty())
        QMessageBox::warning(this, "Login", "Enter your username!");
    else {
        this->hide();

        userName = ui->usernameEdit->text().toStdString();
        this->posUser = ctrl.getRepo().findUser(this->userName);


        User newUser;
        if (posUser == -1) {
            newUser.userName = this->userName;
            this->newCustomer = true;
        }
        else
            this->newCustomer = false;

        //show users window
        QFile f(":qdarkstyle/style.qss");
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);

        UserDialog userWindow;
        userWindow.setStyleSheet(ts.readAll());
        userWindow.setModal(true);
        userWindow.setCtrl(this->ctrl);
        userWindow.initGenreItems();
        userWindow.setExtraInfo(userName,newWatchList,newCustomer,posUser);
        userWindow.logedIn();
        userWindow.exec();

        this->newWatchList = userWindow.getNewWatchList();

        if (newCustomer) {
            newUser.watchList = this->newWatchList;
            ctrl.addNewUserToRepo(newUser);

            ctrl.setListForFileRepo(newUser.watchList.getFilms());
            if (newUser.watchList.getFilms().size() != 0)       //check if user has changed his watchlist
                ctrl.saveFile();
        }
        this->ctrl = userWindow.getCtrl();
        ui->usernameEdit->clear();
        this->show();
    }

}
