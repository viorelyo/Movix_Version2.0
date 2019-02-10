#include "userdialog.h"
#include "ui_userdialog.h"
#include <QMessageBox>
#include "Validation.h"
#include <QStringListModel>
#include <algorithm>


UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::setCtrl(Controller& c) {
    this->ctrl = c;
}

void UserDialog::initGenreItems() {
    std::vector<Film> allFilms = ctrl.getRepo().getFilms();
    std::vector<std::string> allGenres;
    for (auto f : allFilms) {
        if(std::find(allGenres.begin(), allGenres.end(), f.getGenre()) != allGenres.end()) {
            continue;
        }
        else {
            ui->genreComboBox->addItem(QString::fromStdString(f.getGenre()));
            allGenres.push_back(f.getGenre());
        }
    }
}

void UserDialog::on_exitBtn_clicked()
{
    this->close();
}

void UserDialog::on_showBtn_clicked()
{
    ui->listWidget->clearSelection();
    ui->genreComboBox->setCurrentText("Select Genre");
    ui->viewBtn->setVisible(false);
    ui->addBtn->setVisible(false);
    //Set top title
    ui->crtInfo->setText("Watchlist");

    //show content in list Widget
    WatchList temporaryWatchlist;
    ui->listWidget->clear();
    if (newCustomer) {
        temporaryWatchlist = this->newWatchList;			//if user is new modify the new watchlist
    }
    else {
        temporaryWatchlist = ctrl.getRepo().getUsers()[this->posUser].watchList;				//get the user's watchlist
    }

    if (temporaryWatchlist.getFilms().size() != 0) {
        std::vector<Film> allFilms = temporaryWatchlist.getFilms();
        for (auto f : allFilms) {
            ui->listWidget->addItem(QString::fromStdString(f.getTitle()) +
                        " | " + QString::fromStdString(f.getGenre()) + " | " + QString::number(f.getYear()));
        }
    }
    else
        QMessageBox::warning(this, "Watchlist", "Your Watchlist is empty!");
}

void UserDialog::on_watchedBtn_clicked()
{
    if (this->newCustomer == false) {
        //get position of film in List Widget
        int posOfWatched = ui->listWidget->selectionModel()->currentIndex().row();
        if (posOfWatched != -1) {

            //delete film from List Widget
            QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
            delete it;

            WatchList temporaryWatchlist = ctrl.getRepo().getUsers()[this->posUser].watchList;				//get the user's watchlist
            Film f = temporaryWatchlist.getFilms()[posOfWatched];

            //delete from watchlist of user
            ctrl.deleteFilmFromWatchlist(this->userName, f.getTitle(), f.getYear());
        }
        else
            QMessageBox::warning(this, "Watched", "No movie was selected!");
    }
    else {
        //get position of film in List Widget
        int posOfWatched = ui->listWidget->selectionModel()->currentIndex().row();
        if (posOfWatched != -1) {
            //delete film from List Widget
            QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
            delete it;
            //delete from watchlist of user
            this->newWatchList.deleteFilm(this->newWatchList.getFilms()[posOfWatched]);
        }
        else
            QMessageBox::warning(this, "Watched", "No movie was selected!");
    }

}


void UserDialog::on_openCSV_Btn_clicked()
{
    if (ui->fileTypeCombo->currentText() == "csv") {
        ctrl.selectFileType(this->userName, "csv");
        ctrl.selectFileType(this->userName, "html");
    }
    else {
        QMessageBox::warning(this, "Open", "Please, select a filetype!");
    }
}


void UserDialog::on_openHTML_Btn_clicked()
{
    if (ui->fileTypeCombo->currentText() == "html") {
        ctrl.selectFileType(this->userName, "html");
        ctrl.openFileInApp();
    }
    else {
        QMessageBox::warning(this, "Open", "Please, select a filetype!");
    }
}

void UserDialog::on_yesRadio_clicked()
{
    WatchList temporaryWatchlist;
    int posOfWatched = ui->listWidget->selectionModel()->currentIndex().row();

    if (newCustomer) {
        temporaryWatchlist = this->newWatchList;			//if user is new modify the new watchlist
    }
    else {
        temporaryWatchlist = ctrl.getRepo().getUsers()[this->posUser].watchList;				//get the user's watchlist
    }

    ctrl.incLikes(temporaryWatchlist.getFilms()[posOfWatched].getTitle(), temporaryWatchlist.getFilms()[posOfWatched].getYear());
}

void UserDialog::on_genreComboBox_currentTextChanged(const QString &arg1)
{
    ui->listWidget->clearSelection();
    ui->watchedBtn->setVisible(false);
    ui->label->setVisible(false);
    ui->yesRadio->setVisible(false);
    ui->NoRadio->setVisible(false);

    ui->listWidget->clear();
    //Set top title
    if (ui->genreComboBox->currentText() == "Select Genre")
        ui->crtInfo->setText("");
    else {
        ui->crtInfo->setText(ui->genreComboBox->currentText());

        std::string option = ui->genreComboBox->currentText().toStdString();
        if (option == "all")
            option = "";
        std::vector<Film> foundFilms = ctrl.getFilmsGenre(option);
        for (auto f : foundFilms) {
            ui->listWidget->addItem(QString::fromStdString(f.getTitle()) +
                        " | " + QString::fromStdString(f.getGenre()) + " | " + QString::number(f.getYear()));
        }
    }
}

void UserDialog::on_fileTypeCombo_currentTextChanged(const QString &arg1)
{
    if (ui->fileTypeCombo->currentText() != "Save Format")
        ctrl.selectFileType(this->userName, ui->fileTypeCombo->currentText().toStdString());
}

void UserDialog::on_addBtn_clicked()
{
    WatchList creatingWatchList = this->newWatchList;
    int posOfWatched = ui->listWidget->selectionModel()->currentIndex().row();
    if (posOfWatched != -1) {
        std::string option = ui->genreComboBox->currentText().toStdString();
        if (option == "all")
            option = "";
        std::vector<Film> foundFilms = ctrl.getFilmsGenre(option);

        if (this->newCustomer == false) {
            ctrl.addFilmToWatchlist(this->userName, foundFilms[posOfWatched]);      		//add the film to the watchlist of existing user
        }
        else {
            creatingWatchList.add(foundFilms[posOfWatched]);			//create new WatchList
        }

        if (newCustomer)
                this->newWatchList = creatingWatchList;
    }
    else {
        QMessageBox::warning(this, "Add", "No movie was selected!");
    }
}

void UserDialog::on_viewBtn_clicked()
{
    int posOfWatched = ui->listWidget->selectionModel()->currentIndex().row();

    std::string option = ui->genreComboBox->currentText().toStdString();
    if (option == "all")
        option = "";
    std::vector<Film> foundFilms = ctrl.getFilmsGenre(option);

    foundFilms[posOfWatched].play();
}


void UserDialog::logedIn() {
    ui->userLbl->setText("Loged In as: " + QString::fromStdString(this->userName));
}

void UserDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    {
        ui->yesRadio->setAutoExclusive(false);
        ui->yesRadio->setChecked(false);
        ui->NoRadio->setAutoExclusive(false);
        ui->NoRadio->setChecked(false);

        ui->yesRadio->setAutoExclusive(true);
        ui->NoRadio->setAutoExclusive(true);
    }

    {
        if (ui->crtInfo->text() == "Watchlist") {
            ui->watchedBtn->setVisible(true);
            ui->label->setVisible(true);
            ui->yesRadio->setVisible(true);
            ui->NoRadio->setVisible(true);
            ui->viewBtn->setVisible(false);
            ui->addBtn->setVisible(false);
            //should be changed
        }
        else {
            ui->viewBtn->setVisible(true);
            ui->addBtn->setVisible(true);
            ui->watchedBtn->setVisible(false);
            ui->label->setVisible(false);
            ui->yesRadio->setVisible(false);
            ui->NoRadio->setVisible(false);
        }
    }
}
