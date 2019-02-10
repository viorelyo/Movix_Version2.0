#include "FileRepository.h"
#include <QMessageBox>

FileRepository::~FileRepository()
{
}


void FileRepository::init_csv(const std::string& filename)
{
    //load_from_file(this->mainFilename);

    this->filename = filename;
    iFileWriterr.reset(new CSVFileWriter);
}

void FileRepository::init_html(const std::string& filename)
{
    this->filename = filename;
    iFileWriterr.reset(new HTMLFileWriter);
}

void FileRepository::setVectorToFile(const std::vector<Film>& v)
{
    this->vectorToSaveToFile = v;
    vectorInitialized = true;
}

int FileRepository::add(const Film & f)
{
//    try
//    {
        int code = this->addFilm(f);
        save_file();

        return code;
    //}
//    catch (FilmNotFound& e)
//    {
//        throw FilmNotFound();
//    }
}

void FileRepository::update(unsigned pos, const std::string & newTitle, const std::string & newGenre, const unsigned newYear)
{
    this->updateFilm(pos, newTitle, newGenre, newYear);
    save_file();
}

void FileRepository::remove(const Film & f)
{
//    try
//    {
        this->deleteFilm(f);
        save_file();
//    }
//    catch (FilmNotFound& e) {
//        throw FilmNotFound();
//    }
}

void FileRepository::addWatchList(const std::string & userName, const Film & f)
{
//    try {
        this->addUsersFilmToWatchlist(userName, f);
        if (this->iFileWriterr != nullptr) {
            int foundPos = this->findUser(userName);
            this->vectorToSaveToFile = this->users[foundPos].watchList.getFilms();
            vectorInitialized = true;
            save_file();
        }
//    }
//    catch (FilmInWatchlist& e)
//    {
//        throw FilmInWatchlist();
//    }
}

void FileRepository::deleteFromWatchlist(const std::string & userName, const Film & f)
{
    //try {
        this->deleteUsersFilmFromWatchlist(userName, f);
        if (this->iFileWriterr != nullptr) {
            int foundPos = this->findUser(userName);
            this->vectorToSaveToFile = this->users[foundPos].watchList.getFilms();
            vectorInitialized = true;
            save_file();
        }
//    }
//    catch (FilmInWatchlist& e)
//    {
//        throw FilmInWatchlist();
//    }
}

void FileRepository::save_file()
{
    std::ofstream dataBase;
    dataBase.open(mainFilename);

    if (vectorInitialized == true) {
        std::ofstream file;
        file.open(filename);
        if (iFileWriterr != nullptr)
            iFileWriterr->write(file, this->vectorToSaveToFile);			//personalized vector
        file.close();
    }
    iFileSaver->write(dataBase, this->films);

    dataBase.close();
}


void FileRepository::load_from_file()
{
    std::ifstream file(this->mainFilename);
    if (file.is_open())
    {
        this->films = iFileReader->read(file);
        file.close();
    }
}

void FileRepository::open()
{
    iFileWriterr->open(filename);

}



