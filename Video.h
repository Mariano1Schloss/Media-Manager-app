#ifndef Graph_Video
#define Graph_Video
#include "Multimedia.h"

class Video : public Multimedia
{
private:
    int duration;

protected:
    Video(int duration, std::string name, std::string fileName) : Multimedia(name, fileName), duration{duration} {}
    Video() : Multimedia(), duration{0} {}

public:
    friend class MultimediaManager;

    // Getter for duration
    float getDuration() const
    {
        return duration;
    }

    // Setter for duration
    void setDuration(int dur)
    {
        duration = dur;
    }

    void print(std::ostream &s) const override
    {
        Multimedia::print(s);
        s << getDuration() << std::endl;
    }

    // Play the Video
    void play() override
    {
        std::string fileName = this->getFileName();
        std::string systemArg = "mpv " + fileName + " &";
        system(systemArg.data());
    }

    // return Class name "Video"
    std::string getClassName() override { return std::string("Video"); }

    // Write object attributes and class name into a file
    void write(std::ofstream &f) override
    {
        if (f.is_open())
        {
            Multimedia::write(f);
            std::string d = std::to_string(duration);
            f << d << '\n';
        }
        else
        {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier en écriture." << std::endl;
        }
    }

    // read objects attributes from a file
    void read(std::ifstream &f) override
    {
        if (f.is_open())
        {
            Multimedia::read(f);
            std::string d;
            getline(f, d);
            // TODO GESTION d'ERREUR
            duration = std::stoi(d);
            f.close();
        }
        else
        {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier en lecture." << std::endl;
        }
    };
};
#endif