#include "dialogadmin.h"
#include "ui_dialogadmin.h"
#include "mainwindow.h"
#include <QTextStream>
#include <QFontDatabase>
#include <QFont>
#include <adddialog.h>
#include <deletedialog.h>
#include <updatedialog.h>



DialogAdmin::DialogAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAdmin)
{
    ui->setupUi(this);
}

DialogAdmin::~DialogAdmin()
{
    delete ui;
}

void DialogAdmin::setAdminCtrl( Controller& c)
{
    this->ctrl = c;
}
void DialogAdmin::on_pushButton_clicked()
{
    this->close();
}

void DialogAdmin::showContent()
{
    QString s;
    QTextStream ss(&s);

    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    ui->textBrowser->setCurrentFont(fixedFont);

    std::vector<Film> allFilms = ctrl.getRepo().getFilms();
    for (unsigned i = 0; i < allFilms.size(); i++) {
        ss << left << qSetFieldWidth(20) << QString::fromStdString(allFilms[i].getTitle()) << qSetFieldWidth(0) << " ";
        ss << qSetFieldWidth(10) << QString::fromStdString(allFilms[i].getGenre()) << qSetFieldWidth(0) << " ";
        ss << qSetFieldWidth(7) << allFilms[i].getYear() << qSetFieldWidth(0) << " ";
        ss << qSetFieldWidth(8) << allFilms[i].getLikes();
        ss << qSetFieldWidth(0) << endl;
    }

    //  Add the content to the text widget
    s = ss.readAll();
    ui->textBrowser->setPlainText(s);
}

void DialogAdmin::on_addBtn_clicked()
{   
    AddDialog addWindow;
    addWindow.setAddCtrl(ctrl);
    addWindow.setModal(true);
    addWindow.exec();

    this->ctrl = addWindow.getCtrl();
    showContent();
}

void DialogAdmin::on_deleteBtn_clicked()
{
    DeleteDialog deleteWindow;
    deleteWindow.setAddCtrl(ctrl);
    deleteWindow.setModal(true);
    deleteWindow.exec();

    this->ctrl = deleteWindow.getCtrl();
    showContent();
}

void DialogAdmin::on_updateBtn_clicked()
{
    UpdateDialog updateWindow;
    updateWindow.setUpdateCtrl(ctrl);
    updateWindow.setModal(true);
    updateWindow.exec();

    this->ctrl = updateWindow.getCtrl();
    showContent();
}
