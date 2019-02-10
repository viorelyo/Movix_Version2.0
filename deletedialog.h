#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>
#include "Controller.h"

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = 0);
    ~DeleteDialog();
    void setAddCtrl(Controller& c);
    Controller& getCtrl() {
        return ctrl;
    }

private slots:
    void on_addBtn_clicked();

    void on_cancelBtn_clicked();

    void on_titleEdit_textChanged(const QString &arg1);

    void on_yearEdit_textChanged(const QString &arg1);

private:
    Ui::DeleteDialog *ui;
    Controller ctrl;
};

#endif // DELETEDIALOG_H
