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
};
#endif