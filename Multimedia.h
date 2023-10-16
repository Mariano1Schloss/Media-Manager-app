#ifndef Graph_Multimedia
#define Graph_Multimedia
#include <string>
#include <iostream>
#include <iostream>

class Multimedia
{
private:
    std::string name;
    std::string fileName;

public:
    Multimedia(std::string name, std::string filename);

    Multimedia();

    virtual ~Multimedia();

    std::string getName() const;

    std::string getFileName() const;

    void setFileName(std::string fileName);

    void setName(std::string Name);

    virtual void print(std::ostream &s) const;

    virtual void play() = 0; // méthode abstraite
};
#endif
