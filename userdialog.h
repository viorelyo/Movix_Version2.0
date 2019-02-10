#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "Controller.h"
#include <QListWidgetItem>

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = 0);
    ~UserDialog();

    void setCtrl(Controller& c);
    Controller& getCtrl() {
        return this->ctrl;
    }

    void setExtraInfo(std::string usrNm, WatchList& newWtchList, bool newCstm, int posUsr){
        userName = usrNm;
        newWatchList = newWtchList;
        newCustomer = newCstm;
        posUser = posUsr;
    }

    std::string getUserName() {
        return this->userName;
    }

    WatchList& getNewWatchList() {
        return this->newWatchList;
    }

    bool getNewCustomer(){
        return this->newCustomer;
    }

    int getPosUser(){
        return this->posUser;
    }

    void initGenreItems();

    void logedIn();


private slots:
    void on_exitBtn_clicked();

    void on_showBtn_clicked();

    void on_watchedBtn_clicked();


    void on_openCSV_Btn_clicked();

    void on_openHTML_Btn_clicked();

    void on_yesRadio_clicked();

    void on_genreComboBox_currentTextChanged(const QString &arg1);

    void on_fileTypeCombo_currentTextChanged(const QString &arg1);

    void on_addBtn_clicked();

    void on_viewBtn_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::UserDialog *ui;
    Controller ctrl;
    std::string userName;
    WatchList newWatchList;
    bool newCustomer = false;
    int posUser;
};

#endif // USERDIALOG_H
