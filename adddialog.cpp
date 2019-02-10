#include "adddialog.h"
#include "ui_adddialog.h"
#include "Validation.h"
#include <QMessageBox>


AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::setAddCtrl(Controller& c){
    this->ctrl = c;
}

void AddDialog::on_addBtn_clicked()
{
    QString title = ui->titleEdit->text();
    QString genre = ui->genreEdit->text();
    QString year  = ui->yearEdit->text();

    if (ui->titleEdit->text().isEmpty() || ui->genreEdit->text().isEmpty() || ui->yearEdit->text().isEmpty() || Validation::validateYear(year.toStdString()) == -1 || Validation::validateYear(year.toStdString()) == -2)
        QMessageBox::warning(this, "ADD", "Can't add any film!");

    else if (ctrl.addFilmToRepo(title.toStdString(), genre.toStdString(), Validation::validateYear(year.toStdString())) == -1)
        QMessageBox::warning(this, "ADD", title + " " + year + " exists!");


    this->close();
}

void AddDialog::on_cancelBtn_clicked()
{
    this->close();
}

void AddDialog::on_titleEdit_textChanged(const QString &arg1)
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

void AddDialog::on_genreEdit_textChanged(const QString &arg1)
{
     ui->label_5->setStyleSheet("color: green;");
     ui->label_8->setStyleSheet("color: red;");

     if(ui->genreEdit->text().isEmpty()) {
         ui->label_8->setVisible(true);
         ui->label_5->setVisible(false);
     }
     else {
         ui->label_5->setVisible(true);
         ui->label_8->setVisible(false);
     }
}

void AddDialog::on_yearEdit_textChanged(const QString &arg1)
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
