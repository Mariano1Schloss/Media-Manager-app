#ifndef Graph_Video
#define Graph_Video
#include "Multimedia.h"

class Video : public Multimedia
{
private:
    int duration;

public:
    Video(int duration, std::string name, std::string fileName) : Multimedia(name, fileName), duration{duration} {}
    Video() : Multimedia(), duration{0} {}

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
    void write(std::ostream &f) override
    {
        Multimedia::write(f);
        std::string d = std::to_string(duration);
        f << getClassName() << '\n'
          << d << '\n';
    }

    // read objects attributes from a file
    void read(std::istream &f) override
    {
        Multimedia::read(f);
        std::string d;
        getline(f, d);
        // TODO GESTION d'ERREUR
        duration = std::stoi(d);
    };
};
#endif