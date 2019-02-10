#ifndef DIALOGADMIN_H
#define DIALOGADMIN_H

#include "Controller.h"
#include "Validation.h"
#include <QDialog>

namespace Ui {
class DialogAdmin;
}

class DialogAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAdmin(QWidget *parent = 0);
    ~DialogAdmin();

    Controller& getCtrl() {
        return this->ctrl;
    }

    void setAdminCtrl(Controller& c);
    void showContent();
private slots:
    void on_pushButton_clicked();

    void on_addBtn_clicked();

    void on_deleteBtn_clicked();

    void on_updateBtn_clicked();

private:
    Ui::DialogAdmin *ui;
    Controller ctrl;
};

#endif // DIALOGADMIN_H
