#include "Multimedia.h"

Multimedia::Multimedia(std::string name, std::string fileName)
{
    this->fileName = fileName;
    this->name = name;
}

Multimedia::Multimedia()
{
    this->fileName = "/";
    this->name = "defaultName";
}

Multimedia::~Multimedia()
{
    std::cout << "Destructor called for " << this->name << std::endl;
}

std::string Multimedia::getFileName() const
{
    return fileName;
}

std::string Multimedia::getName() const
{
    return name;
}

void Multimedia::setName(std::string n)
{
    name = n;
}

void Multimedia::setFileName(std::string fn)
{
    fileName = fn;
}

void Multimedia::print(std::ostream &s) const
{
    s << this->getName() << " " << this->getFileName() << std::endl;
}
