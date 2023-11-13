#ifndef Graph_Multimedia
#define Graph_Multimedia
#include <string>
#include <iostream>
#include <fstream>

class Multimedia
{
private:
    std::string name;
    std::string fileName;

protected:
    Multimedia(std::string name, std::string filename);
    Multimedia();

public:
    friend class MultimediaManager;

    virtual ~Multimedia();

    std::string getName() const;

    std::string getFileName() const;

    void setFileName(std::string fileName);

    void setName(std::string Name);

    virtual void print(std::ostream &s) const;

    virtual void play() = 0; // méthode abstraite

    // return class name "Multimedia"
    virtual std::string getClassName() { return std::string("Multimedia"); }

    virtual void write(std::ofstream &f) { f << getClassName() << '\n'
                                            << name << '\n'
                                            << fileName << '\n'; }

    virtual void read(std::ifstream &f)
    {
        getline(f, name);
        getline(f, fileName);
    };
};
#endif
