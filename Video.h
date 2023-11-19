/*!
 * \file Video.h
 * \author Mathieu Delbos
 * \version 0.1
 */

#ifndef Graph_Video
#define Graph_Video
#include "Multimedia.h"

/*! \class Video
 * \brief Classe representant une Vidéo
 */
class Video : public Multimedia
{
private:
    int duration; /*!< durée de la photo*/

protected:
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Video.
     *  Appelle d'abord le constructeur de Multimedia
     *  \param name : nom de la Video
     *  \param fileName : nom du fichier associé à la Video
     *  \param duration : durée de la Video
     */
    Video(int duration, std::string name, std::string fileName) : Multimedia(name, fileName), duration{duration} {}

    /*!
     *  \brief Constructeur
     *  Constructeur de base de la classe Photo
     *  Appelle d'abord le constructeur de base de Multimedia
     *  Initialise duration avec une valeur défaut
     */
    Video() : Multimedia(), duration{0} {}

public:
    friend class MultimediaManager; /*!< On souhaite que seule la classe MultimediaManager puisse instancier Video*/

    /*!
     *  \brief Getter de la durée de la Video
     *  Methode qui permet de retourner la valeur de la variable d'instance duration
     *  \return la valeur de la variable d'instance duration
     */
    float getDuration() const
    {
        return duration;
    }

    /*!
     *  \brief Setter de la durée de Video
     *  Methode qui permet de modifier la valeur de la variable d'instance duration
     *  \param dur: la nouvelle valeur de la variable d'instance duration
     */
    void setDuration(int dur)
    {
        duration = dur;
    }

    /*!
     *  \brief Affiche les informations de Video
     *  Methode qui permet d'afficher les informations de Video
     *  Appelle d'abord la méthode print() de Multimedia
     *  \param s: flux de sortie souhaité
     */
    void print(std::ostream &s) const override
    {
        Multimedia::print(s);
        s << "Video duration : " << getDuration() << std::endl;
    }

    /*!
     *  \brief Joue la vidéo sur le serveur
     *  Méthode qui permet de lire la vidéo sur le serveur à l'aide de mpv
     */
    void play() override
    {
        std::string fileName = this->getFileName();
        std::string systemArg = "mpv " + fileName + " &";
        system(systemArg.data());
    }

    /*!
     *  \brief Retourne le nom de la classe
     *  Methode qui permet de retourner le nom de la classe : "Photo"
     *  \return "Photo"
     */
    std::string getClassName() override { return std::string("Video"); }

    /*!
     *  \brief Sérialise une Video
     *  Méthode qui sérialise un objet Video en écrivant sur le flux de sortie f
     *  Appelle d'abord la méthode write() de Multimedia
     *  \param f: flux de sortie souhaité
     */
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

    /*!
     *  \brief Désérialise une Video
     *  Méthode qui désérialise un objet Video en lisant sur le flux d'entrée f
     *  Appelle d'abord la méthode read() de Multimedia
     *  \param f: flux d'entrée souhaité
     */
    void read(std::ifstream &f) override
    {
        if (f.is_open())
        {
            Multimedia::read(f);
            std::string d;
            getline(f, d);
            // TODO GESTION d'ERREUR
            duration = std::stoi(d);
        }
        else
        {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier en lecture." << std::endl;
        }
    };
};
#endif