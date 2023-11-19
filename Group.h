/*!
 * \file Group.h
 * \author Mathieu Delbos
 * \version 0.1
 */

#ifndef Graph_Group
#define Graph_Group
#include <list>
#include <string>
#include <memory>
#include "Multimedia.h"

/*! \class Group
 * \brief Classe representant un Groupe
 * Hérite de std::list<std::shared_ptr<Multimedia>>
 */
class Group : public std::list<std::shared_ptr<Multimedia>>
{
private:
    std::string name; /*!< nom du groupe*/

public:
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Group.
     *  Appelle d'abord le constructeur de std::list
     *  \param groupName : nom du groupe
     *  \param sourceList : liste de smart pointers vers des objets Multimedia
     */
    Group(std::string groupName, const std::list<std::shared_ptr<Multimedia>> &sourceList)
        : std::list<std::shared_ptr<Multimedia>>(sourceList), name(groupName) {}

    /*!
     *  \brief Destructeur
     *  Signale quand un groupe est supprimé
     */
    ~Group()
    {
        std::cout << "Destroying Group object: " << name << std::endl;
    }

    /*!
     *  \brief Getter du nom du groupe
     *  Methode qui permet de retourner le nom du groupe
     *  \return la valeur de la variable d'instance name
     */
    const std::string getName() const
    {
        return name;
    }

    /*!
     *  \brief Affiche les informations de tous les médias du groupe
     *  Methode qui permet d'invoquer la méthode print() adaptée pour tous les médias du groupe '
     *  \param s : flux de sortie souhaité
     */
    void print(std::ostream &s) const
    {
        for (const auto &media : *this)
        {
            media->print(s);
        }
    }

    /*!
     *  \brief Vérifie la présence et supprime du groupe
     *    Méthode pour vérifier si un groupe contient un objet multimédia par son nom et le retire de la liste le cas échéant
     *  \param multimediaName : nom du media à rechercher et supprimer
     */
    void removeMultimediaByName(const std::string &multimediaName)
    {
        auto it = begin();
        while (it != end())
        {
            if ((*it)->getName() == multimediaName)
            {
                it = erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
};
#endif
