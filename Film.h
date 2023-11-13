#ifndef Graph_Film
#define Graph_Film
#include "Video.h"
#include <cstring>

class Film : public Video
{
private:
    int *chapters;
    int nb_chapter;

protected:
    Film(int *array, int nb, int duration, std::string name, std::string fileName);
    Film() : Video(), chapters{nullptr}, nb_chapter{0} {}

public:
    friend class MultimediaManager;
    // destructor : deallocate memory
    ~Film() { delete[] chapters; }

    const int *getChapters() const;

    const int getChapter(int index) const;

    const int getNbChapter() const { return nb_chapter; }

    // Deallocate chapters from memory
    void delete_chapters();

    void setChapterValue(int index, int value);

    void setChapters(const int *newArray, int newArrayLength);

    void print(std::ostream &s) const override;

    // return Class name "Film"
    std::string getClassName() override { return "Film"; }

    // Write object attributes and class name into a file
    void write(std::ofstream &f) override;

    // read objects attributes from a file
    void read(std::ifstream &f) override;
};
#endif