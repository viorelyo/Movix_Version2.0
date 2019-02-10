#include "deletedialog.h"
#include "ui_deletedialog.h"
#include "Validation.h"
#include <QMessageBox>


DeleteDialog::DeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::setAddCtrl(Controller& c){
    this->ctrl = c;
}

void DeleteDialog::on_addBtn_clicked()
{
    QString title = ui->titleEdit->text();
    QString year  = ui->yearEdit->text();

    if (ui->titleEdit->text().isEmpty() || ui->yearEdit->text().isEmpty() || Validation::validateYear(year.toStdString()) == -1 || Validation::validateYear(year.toStdString()) == -2)
        QMessageBox::warning(this, "DELETE", "Can't delete any film!");

    else if (ctrl.deleteFilmFromRepo(title.toStdString(), Validation::validateYear(year.toStdString())) == -1)
        QMessageBox::warning(this, "DELETE", title + " " + year + " doesn't exist!");


    this->close();
}

void DeleteDialog::on_cancelBtn_clicked()
{
    this->close();
}

void DeleteDialog::on_titleEdit_textChanged(const QString &arg1)
{
    ui->label_4->setStyleSheet("color: green;");
    ui->label_7->setStyleSheet("color: red;");

    if(ui->titleEdit->text().isEmpty()) {
        ui->label_7->setVisible(true);
        ui->label_4->setVisible(false);
    }
    else {
        ui->label_4->setVisible(true);
        ui->label_7->setVisible(false);
    }
}

void DeleteDialog::on_yearEdit_textChanged(const QString &arg1)
{
    ui->label_6->setStyleSheet("color: green;");
    ui->label_9->setStyleSheet("color: red;");

    if(ui->yearEdit->text().isEmpty() || Validation::validateYear(ui->yearEdit->text().toStdString()) == -1 || Validation::validateYear(ui->yearEdit->text().toStdString()) == -2) {
        ui->label_9->setVisible(true);
        ui->label_6->setVisible(false);
    }
    else {
        ui->label_6->setVisible(true);
        ui->label_9->setVisible(false);
    }
}
