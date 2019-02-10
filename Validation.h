#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

class Validation
{
public:
    static int validateTitle(const std::string& title);
    static int validateGenre(const std::string& genre);
    static int validateYear(const std::string& year);
};

#endif // VALIDATION_H
