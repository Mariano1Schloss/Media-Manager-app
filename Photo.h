#ifndef Graph_Photo
#define Graph_Photo
#include "Multimedia.h"

class Photo : public Multimedia
{
private:
    float latitude;
    float longitude;

protected:
    Photo(float latitude, float longitude, std::string name, std::string fileName) : Multimedia(name, fileName), latitude{latitude}, longitude{longitude} {}
    Photo() : Multimedia(), latitude{0}, longitude{0} {}

public:
    friend class MultimediaManager;
    // Getter for latitude
    float getLatitude() const { return latitude; }

    // Setter for latitude
    void setLatitude(float lat) { latitude = lat; }

    // Getter for longitude
    float getLongitude() const { return longitude; }

    // Setter for longitude
    void setLongitude(float lon) { longitude = lon; }

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

    // return Class name "Photo"
    std::string getClassName() override { return std::string("Photo"); }

    // Write object attributes and class name into a file
    void write(std::ofstream &f) override
    {
        if (f.is_open())
        {
            Multimedia::write(f);
            f << latitude << '\n'
              << longitude << '\n';
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
            std::string lat, longi;
            getline(f, lat);
            getline(f, longi);
            // TODO GESTION d'ERREUR
            latitude = std::stol(lat);
            longitude = std::stol(longi);
        }
        else
        {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier en lecture." << std::endl;
        }
    }
};
#endif