#include "Film.h"

Film::Film(int *array, int nb, int duration, std::string name, std::string fileName) : Video(duration, name, fileName)
{
    int sum = 0;
    for (int i = 0; i < nb; ++i)
    {
        sum += array[i];
    }

    if (sum == duration && nb > 0)
    {
        chapters = new int[nb];
        nb_chapter = nb;
        std::memcpy(chapters, array, nb * sizeof(int));
    }
    else
    {
        std::cerr << "Invalid array of chapters" << std::endl;
        chapters = nullptr;
        nb_chapter = 0;
    }
}

void Film::delete_chapters()
{
    delete[] chapters;
    nb_chapter = 0;
    chapters = nullptr;
}

// Getter for chapters
const int *Film::getChapters() const
{
    return chapters;
}

// getter for chapter value
const int Film::getChapter(int index) const
{
    if (chapters && index >= 0 && index < getNbChapter())
    {
        return chapters[index];
    }
    else
    {
        std::cerr << "Invalid index or 'chapters' is not initialized." << std::endl;
        return -1;
    }
}

// Setter for 'Chapter' at a specific index
void Film::setChapterValue(int index, int value)
{
    if (chapters && index >= 0 && index < getNbChapter())
    {
        if (value > 0)
        {
            chapters[index] = value;
        }
        else
        {
            std::cerr << "Invalid duration. Must be >=0." << std::endl;
        }
    }
    else
    {
        std::cerr << "Invalid index or 'chapters' is not initialized." << std::endl;
    }
}

// Setter to modify the entire array 'Chapters'
void Film::setChapters(const int *newArray, int newArrayLength)
{
    delete_chapters();

    if (newArrayLength > 0)
    {
        chapters = new int[newArrayLength];
        for (int i = 0; i < newArrayLength; ++i)
        {
            if (newArray[i] < 0)
            {
                std::cerr << "Invalid data: Elements must be non-negative." << std::endl;
                return;
            }
        }
        std::memcpy(chapters, newArray, newArrayLength * sizeof(int));
        nb_chapter = newArrayLength;
    }
    else
    {
        std::cerr << "Invalid data. Array length must be >0" << std::endl;
    }
}

void Film::print(std::ostream &s) const
{
    Video::print(s);
    s << "Nombre de chapitres du film : " << getNbChapter() << std::endl;
    if (chapters)
    {
        for (int i = 0; i < getNbChapter(); i++)
        {
            s << "Durée du chapitre " << i << " : " << getChapter(i) << std::endl;
        }
    }
}

void Film::write(std::ofstream &f)
{
    if (f.is_open())
    {
        Video::write(f);
        std::string n = std::to_string(nb_chapter);
        f << n << '\n';
        for (int i = 0; i < nb_chapter; i++)
        {
            std::string c = std::to_string(chapters[i]);
            f << c << '\n';
        }
    }
    else
    {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier en écriture." << std::endl;
    }
}

void Film::read(std::ifstream &f)
{
    if (f.is_open())
    {
        Video::read(f);
        std::string n;
        getline(f, n);
        // TODO GESTION d'ERREUR
        nb_chapter = std::stoi(n);
        for (int i = 0; i < nb_chapter; i++)
        {
            std::string c;
            getline(f, c);
            chapters[i] = std::stoi(c);
        }
        f.close();
    }
    else
    {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
};