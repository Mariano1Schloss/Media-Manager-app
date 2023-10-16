#ifndef Graph_Film
#define Graph_Film
#include "Video.h"
#include <cstring>

class Film : public Video
{
private:
    int *chapters;
    int nb_chapter;

public:
    Film(int *array, int nb, int duration, std::string name, std::string fileName);

    Film() : Video(), chapters{nullptr}, nb_chapter{0} {}

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
};
#endif