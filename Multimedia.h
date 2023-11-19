/*!
 * \file Multimedia.h
 * \author Mathieu Delbos
 * \version 0.1
 */

#ifndef Graph_Multimedia
#define Graph_Multimedia
#include <string>
#include <iostream>
#include <fstream>


/*! \class Multimedia
 * \brief classe representant un fichier multimedia
 */
class Multimedia
{
private:
    std::string name;     /*!< Nom du multimédia*/
    std::string fileName; /*!< Nom du fichier associé au multimédia*/

protected:
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Multimédia
     *  \param name : nom du multimédia
     *  \param filename : nom du fichier associé au multimédia
     */
    Multimedia(std::string name, std::string filename);

    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Multimédia
     *  Initialise name et filename avec des valeurs défauts
     */
    Multimedia();

public:
    friend class MultimediaManager;

    virtual ~Multimedia();

    /*!
     *  \brief Getter du nom du Multimédia
     *  Methode qui permet de retourner la valeur de la variable d'instance name
     *  \return la valeur de la variable d'instance name
     */
    std::string getName() const;

    /*!
     *  \brief Getter du nom du fichier du Multimédia
     *  Methode qui permet de retourner la valeur de la variable d'instance filename
     *  \return la valeur de la variable d'instance filename
     */
    std::string getFileName() const;

    /*!
     *  \brief Setter du nom du fichier du Multimédia
     *  Methode qui permet de modifier la valeur de la variable d'instance filename
     *  \param fileName: la nouvelle valeur de la variable d'instance filename
     */
    void setFileName(std::string fileName);

    /*!
     *  \brief Setter du nom du Multimédia
     *  Methode qui permet de modifier la valeur de la variable d'instance name
     *  \param name: la nouvelle valeur de la variable d'instance name
     */
    void setName(std::string name);

    /*!
     *  \brief Affiche les informations du Multimédia
     *  Methode qui permet d'afficher les informations du Multimédia
     *  \param s: flux de sortie souhaité
     */
    virtual void print(std::ostream &s) const;

    /*!
     *  \brief Joue le Multimédia sur le serveur
     *  Methode virtuelles pure qui sera définie dans les classes filles
     * permettant de jouer un Multimédia sur le serveur
     */
    virtual void play() = 0; // méthode abstraite

    /*!
     *  \brief Retourne le nom de la classe
     *  Methode qui permet de retourner le nom de la classe : "Multimedia"
     *  \return "Multimedia"
     */
    virtual std::string getClassName() { return std::string("Multimedia"); }

    /*!
     *  \brief Sérialise un Multimedia
     *  Méthode qui sérialise un objet multimédia en écrivant sur le flux de sortie f
     *  \param f: flux de sortie souhaité
     */
    virtual void write(std::ofstream &f) { f << getClassName() << '\n'
                                             << name << '\n'
                                             << fileName << '\n'; }

    /*!
     *  \brief Désérialise un Multimedia
     *  Méthode qui désérialise un objet multimédia en lisant sur le flux d'entrée f
     *  \param f: flux d'entrée souhaité
     */
    virtual void read(std::ifstream &f)
    {
        getline(f, name);
        getline(f, fileName);
    };
};
#endif
