#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "Controller.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();
    void setAddCtrl(Controller& c);
    Controller& getCtrl() {
        return ctrl;
    }

private slots:
    void on_addBtn_clicked();

    void on_cancelBtn_clicked();

    void on_titleEdit_textChanged(const QString &arg1);

    void on_genreEdit_textChanged(const QString &arg1);

    void on_yearEdit_textChanged(const QString &arg1);

private:
    Ui::AddDialog *ui;
    Controller ctrl;
};

#endif // ADDDIALOG_H
