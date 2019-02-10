#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include "Controller.h"

namespace Ui {
class UpdateDialog;
}

class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDialog(QWidget *parent = 0);
    ~UpdateDialog();

    void setUpdateCtrl(Controller& c);
    Controller& getCtrl() {
        return ctrl;
    }

private slots:
    void on_cancelBtn_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_titleEdit_textChanged(const QString &arg1);

    void on_yearEdit_textChanged(const QString &arg1);

    void on_customEdit_textChanged(const QString &arg1);

    void on_addBtn_clicked();

private:
    Ui::UpdateDialog *ui;
    Controller ctrl;
};

#endif // UPDATEDIALOG_H
