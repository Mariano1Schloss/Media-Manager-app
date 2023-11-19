/*!
 * \file Photo.h
 * \author Mathieu Delbos
 * \version 0.1
 */

#ifndef Graph_Photo
#define Graph_Photo
#include "Multimedia.h"

/*! \class Photo
 * \brief classe representant une Photo
 */
class Photo : public Multimedia
{
private:
    float latitude;  /*!< latitude de la photo*/
    float longitude; /*!< longitude de la photo*/

protected:
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Photo. Appelle d'abord le vonstructeur de Multimedia.
     *  \param name : nom de la Video
     *  \param fileName : nom du fichier associé à la Video
     *  \param latitude : latitude de la photo
     *  \param longitude : longitude de la photo
     */
    Photo(float latitude, float longitude, std::string name, std::string fileName) : Multimedia(name, fileName), latitude{latitude}, longitude{longitude} {}

    /*!
     *  \brief Constructeur
     *  Constructeur de base la classe Photo
     *  Appelle d'abord le constructeur de base de Multimedia
     *  Initialise longitude et latitude avec des valeurs défauts
     */
    Photo() : Multimedia(), latitude{0}, longitude{0} {}

public:
    friend class MultimediaManager; /*!< On souhaite que seule la classe MultimediaManager puisse instancier Video*/

    /*!
     *  \brief Getter de la latitude de la Photo
     *  Methode qui permet de retourner la valeur de la variable d'instance latitude
     *  \return la valeur de la variable d'instance latitude
     */
    float getLatitude() const { return latitude; }

    /*!
     *  \brief Setter de la latitude de Photo
     *  Methode qui permet de modifier la valeur de la variable d'instance latitude
     *  \param lat: la nouvelle valeur de la variable d'instance latitude
     */
    void setLatitude(float lat) { latitude = lat; }

    /*!
     *  \brief Getter de la longitude de la Photo
     *  Methode qui permet de retourner la valeur de la variable d'instance longitude
     *  \return la valeur de la variable d'instance longitude
     */
    float getLongitude() const { return longitude; }

    /*!
     *  \brief Setter de la longitude Photo
     *  Methode qui permet de modifier la valeur de la variable d'instance longitude
     *  \param lon: la nouvelle valeur de la variable d'instance longitude
     */
    void setLongitude(float lon) { longitude = lon; }

    /*!
     *  \brief Affiche les informations de Photo
     *  Methode qui permet d'afficher les informations de Photo
     *  Appelle d'abord la méthode print() de Multimedia
     *  \param s: flux de sortie souhaité
     */
    void print(std::ostream &s) const override
    {
        Multimedia::print(s);
        s << "Photo latitude : " << getLatitude() << "  Photo longitude : " << getLongitude() << std::endl;
    }

    /*!
     *  \brief Joue la Photo sur le serveur
     *  Méthode qui permet d'afficher la photo sur le serveur à l'aide d'imagej
     */
    void play() override
    {
        std::string fileName = this->getFileName();
        std::string systemArg = "imagej " + fileName + " &";
        system(systemArg.data());
    }

    /*!
     *  \brief Retourne le nom de la classe
     *  Methode qui permet de retourner le nom de la classe : "Photo"
     *  \return "Photo"
     */
    std::string getClassName() override { return std::string("Photo"); }

    /*!
     *  \brief Sérialise une Photo
     *  Méthode qui sérialise un objet Photo en écrivant sur le flux de sortie f
     *  Appelle d'abord la méthode write() de Multimedia
     *  \param f: flux de sortie souhaité
     */
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

    /*!
     *  \brief Désérialise une Photo
     *  Méthode qui désérialise un objet Photo en lisant sur le flux d'entrée f
     *  Appelle d'abord la méthode read() de Multimedia
     *  \param f: flux d'entrée souhaité
     */
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