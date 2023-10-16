#ifndef Graph_Photo
#define Graph_Photo
#include "Multimedia.h"

class Photo : public Multimedia
{
private:
    float latitude;
    float longitude;

public:
    Photo(float latitude, float longitude, std::string name, std::string fileName) : Multimedia(name, fileName), latitude{latitude}, longitude{longitude} {}

    Photo() : Multimedia(), latitude{0}, longitude{0} {}

    // Getter for latitude
    float getLatitude() const
    {
        return latitude;
    }

    // Setter for latitude
    void setLatitude(float lat)
    {
        latitude = lat;
    }

    // Getter for longitude
    float getLongitude() const
    {
        return longitude;
    }

    // Setter for longitude
    void setLongitude(float lon)
    {
        longitude = lon;
    }

    void print(std::ostream &s) const override
    {
        Multimedia::print(s);
        s << getLatitude() << " " << getLongitude() << std::endl;
    }

    // Play the photo
    void play() override
    {
        std::string fileName = this->getFileName();
        std::string systemArg = "imagej " + fileName + " &";
        system(systemArg.data());
    }
};
#endif