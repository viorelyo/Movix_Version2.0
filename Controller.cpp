#include "Controller.h"


Controller::~Controller()
{
}


FileRepository Controller::getRepo()
{
    return repo;
}

int Controller::addFilmToRepo(const std::string & title, const std::string & genre, unsigned year)
{
//    try
//    {
        Film f(title, genre, year);
        //repo.add(f);
        return repo.add(f);
   // }
//    catch (FilmNotFound& e)
//    {
        //return -1;
    //}
}

void Controller::updateFilmFromRepo(unsigned pos, const std::string & newTitle, const std::string & newGenre, const unsigned newYear)
{
    repo.update(pos, newTitle, newGenre, newYear);
}

int Controller::deleteFilmFromRepo(const std::string & title, unsigned year)
{
//    try {
        Film f = repo.findByID(title, year);
        if (f.getTitle() != "")
        {
            repo.remove(f);			//fileREPO remove
            return 0;
        }
        else
            return -1;
//    }
//    catch (FilmNotFound& e)
//    {
//        return -1;
//    }

}

std::vector<Film> Controller::getFilmsGenre(const std::string& genre) const
{
    std::vector<Film> allFilms = repo.getFilms();
    if (genre == "")
        return allFilms;
    else {
        std::vector<Film> foundFilms;
        for (unsigned i = 0; i < allFilms.size(); i++)
            if (allFilms[i].getGenre() == genre)
                foundFilms.push_back(allFilms[i]);
        return foundFilms;
    }
}

void Controller::incLikes(const std::string& title, unsigned year)
{
    Film f = repo.findByID(title, year);
    repo.incLikes(f);
}

void Controller::addNewUserToRepo(const User & u)
{
    repo.addUser(u);
}

int Controller::deleteFilmFromWatchlist(const std::string & userName, const std::string & title, unsigned year)
{
//    try
//    {
        Film f = repo.findByID(title, year);
        repo.deleteFromWatchlist(userName, f);
        return 0;
}

int Controller::addFilmToWatchlist(const std::string & userName, const Film & f)
{
    //return repo.addUsersFilmToWatchlist(userName, f
        repo.addWatchList(userName, f);
        return 0;
}

void Controller::selectFileType(const std::string & userName, const std::string & fileType)
{
    if (fileType == "html")
        repo.init_html(userName + "Watchlist.html");
    else if (fileType == "csv")
        repo.init_csv(userName + "Watchlist.csv");
}

void Controller::setListForFileRepo(const std::vector<Film>& v)
{
    repo.setVectorToFile(v);
}

void Controller::saveFile()
{
    repo.save_file();
}

void Controller::openFileInApp()
{
    repo.open();
}

