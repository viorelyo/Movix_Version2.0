#include "updatedialog.h"
#include "ui_updatedialog.h"
#include "Validation.h"
#include <QMessageBox>


UpdateDialog::UpdateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

void UpdateDialog::setUpdateCtrl(Controller& c){
    this->ctrl = c;
}

void UpdateDialog::on_cancelBtn_clicked()
{
    this->close();
}

void UpdateDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (ui->comboBox->currentText() == "New Title" || ui->comboBox->currentText() == "New Genre" || ui->comboBox->currentText() == "New Year") {
        ui->customLabel->setText(ui->comboBox->currentText());
        ui->customLabel->setVisible(true);
        ui->customEdit->setVisible(true);
    }
    else {
        ui->customLabel->setVisible(false);
        ui->customEdit->setVisible(false);
    }
}

void UpdateDialog::on_titleEdit_textChanged(const QString &arg1)
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

void UpdateDialog::on_yearEdit_textChanged(const QString &arg1)
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

void UpdateDialog::on_customEdit_textChanged(const QString &arg1)
{
    if (ui->comboBox->currentText() == "New Title") {
        ui->label_5->setStyleSheet("color: green;");
        ui->label_8->setStyleSheet("color: red;");

        if(ui->customEdit->text().isEmpty()) {
            ui->label_8->setVisible(true);
            ui->label_5->setVisible(false);
        }
        else {
            ui->label_5->setVisible(true);
            ui->label_8->setVisible(false);
       }
    }
    else if (ui->comboBox->currentText() == "New Genre") {
         ui->label_5->setStyleSheet("color: green;");
         ui->label_8->setStyleSheet("color: red;");

         if(ui->customEdit->text().isEmpty()) {
             ui->label_8->setVisible(true);
             ui->label_5->setVisible(false);
         }
         else {
             ui->label_5->setVisible(true);
             ui->label_8->setVisible(false);
         }
    }
    else if (ui->comboBox->currentText() == "New Year") {
        ui->label_5->setStyleSheet("color: green;");
        ui->label_8->setStyleSheet("color: red;");

        if(ui->customEdit->text().isEmpty() || Validation::validateYear(ui->customEdit->text().toStdString()) == -1 || Validation::validateYear(ui->customEdit->text().toStdString()) == -2) {
            ui->label_8->setVisible(true);
            ui->label_5->setVisible(false);
        }
        else {
            ui->label_5->setVisible(true);
            ui->label_8->setVisible(false);
        }
    }
}


void UpdateDialog::on_addBtn_clicked()
{
    QString title = ui->titleEdit->text();
    QString year  = ui->yearEdit->text();

    if (ui->titleEdit->text().isEmpty() || ui->customEdit->text().isEmpty() || ui->yearEdit->text().isEmpty() || Validation::validateYear(year.toStdString()) == -1 || Validation::validateYear(year.toStdString()) == -2)
        QMessageBox::warning(this, "UPDATE", "Can't update any film!");
    else {
        int exists = ctrl.getRepo().findFilm(ctrl.getRepo().findByID(title.toStdString(), Validation::validateYear(year.toStdString())));
        if (exists == -1)
            QMessageBox::warning(this, "UPDATE", "The film wasn't found!");
        else {
            if (ui->comboBox->currentText() == "New Title") {
                QString newTitle = ui->customEdit->text();
                ctrl.updateFilmFromRepo(exists, newTitle.toStdString());
            }
            else if (ui->comboBox->currentText() == "New Genre") {
                QString newGenre = ui->customEdit->text();
                ctrl.updateFilmFromRepo(exists, "", newGenre.toStdString());
            }
            else if (ui->comboBox->currentText() == "New Year") {
                QString newYear  = ui->customEdit->text();
                ctrl.updateFilmFromRepo(exists, "", "", Validation::validateYear(newYear.toStdString()));
            }
        }
    }
    this->close();
}







