#include "mainwindow.h"
#include <QApplication>
#include "Controller.h"
#include "FileRepository.h"
#include <QFile>
#include <QTextStream>
#include <cassert>


//void Tests()
//{
//    FileRepository repo;
//    repo.setDB("test.csv");

//    User u;
//    u.userName = "tester";
//    repo.addUser(u);
//    repo.init_html("testerr.html");

//    Controller ctrl(repo);

//    ctrl.addFilmToRepo("Sherlock", "crime", 2008);
//    ctrl.addFilmToRepo("V for Vendetta", "thriller", 2005);

//    assert(ctrl.getRepo().getFilms().size() == 2);

//    ctrl.updateFilmFromRepo(0, "Sherlock Holmes");
//    assert(ctrl.getRepo().getFilms()[0].getTitle() == "Sherlock Holmes");
//    ctrl.updateFilmFromRepo(0, "", "comedy");
//    assert(ctrl.getRepo().getFilms()[0].getGenre() == "comedy");
//    ctrl.updateFilmFromRepo(0, "", "", 2020);
//    assert(ctrl.getRepo().getFilms()[0].getYear() == 2020);

//    assert(ctrl.getFilmsGenre("thriller").size() == 1);

//    ctrl.incLikes("Sherlock Holmes", 2020);
//    assert(ctrl.getRepo().getFilms()[0].getLikes() == 1);

//    ctrl.deleteFilmFromRepo("Sherlock Holmes", 2020);
//    assert(ctrl.getRepo().getFilms().size() == 1);

//    assert(ctrl.addFilmToRepo("V for Vendetta", "thriller", 2005) == -1);
//    assert(ctrl.deleteFilmFromRepo("Sherlock Holmes", 2020) == -1);

//    Film f2("V for Vendetta", "thriller", 2005);
//    assert(ctrl.addFilmToWatchlist("tester", f2) == 0);
//    assert(ctrl.addFilmToWatchlist("tester", f2) == -1);

//    assert(ctrl.deleteFilmFromWatchlist("tester", "V for Vendetta", 2005) == 0);
//    assert(ctrl.deleteFilmFromWatchlist("tester", "V for Vendetta", 2005) == -1);

//    assert(Validation::validateTitle("") == -1);
//    assert(Validation::validateGenre("") == -1);
//    assert(Validation::validateYear("1700") == -1);
//    assert(Validation::validateYear("test") == -2);
//    assert(Validation::validateTitle("Test") == 0);
//    assert(Validation::validateGenre("test") == 0);
//    assert(Validation::validateYear("2016") == 2016);
//}


int main(int argc, char *argv[])
{

    //Tests();
    QApplication a(argc, argv);

    FileRepository repo;
    repo.setDB("DB.csv");
    repo.load_from_file();

    Film f2("V for Vendetta", "thriller", 2005);
    /*
    Film f3("Inception", "thriller", 2010);
    Film f4("Game of Thrones", "drama", 2019);
    Film f5("Westworld", "drama", 2016);
    Film f6("Avengers", "action", 2012);
    Film f7("Wonder Woman", "fantasy", 2017);
    Film f8("Annihilation", "action", 2018);
    Film f9("Blade Runner 2049", "thriller", 2017);
    Film f10("True Detective", "crime", 2014);

    repo.add(f1);
    repo.add(f2);
    repo.add(f3);
    repo.add(f4);
    repo.add(f5);
    repo.add(f6);
    repo.add(f7);
    repo.add(f8);
    repo.add(f9);
    repo.add(f10)*/

    User u;
    u.userName = "viorel";
    repo.addUser(u);
    repo.addUsersFilmToWatchlist("viorel", f2);


    Controller ctrl(repo);

    QFile f(":qdarkstyle/style.qss");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&f);


    MainWindow w;
    w.setController(ctrl);
    w.setStyleSheet(ts.readAll());
    w.show();

    return a.exec();
}
