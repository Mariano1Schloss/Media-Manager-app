/*!
 * \file Group.h
 * \author Mathieu Delbos
 * \version 0.1
 */

#ifndef Graph_MultimediaManager
#define Graph_MultimediaManager
#include <map>
#include <string>
#include <memory>
#include <list>
#include "Multimedia.h"
#include "Film.h"
#include "Video.h"
#include "Photo.h"
#include "Group.h"

/*! \class MultimediaManager
 * \brief Classe representant un manager d'objets Multimedia
 */
class MultimediaManager
{
private:
    std::map<std::string, std::shared_ptr<Multimedia>> multimediaTable; /*!< Map contenant des smarts pointers vers tous les objets multimedias*/
    std::map<std::string, std::shared_ptr<Group>> groupTable;           /*!< Map contenant des smart pointers vers les groupes*/

public:
    /*!
     *  \brief Constructeur
     *  Constructeur de base de la classe MultimediaManager.
     */
    MultimediaManager(){};

    /*!
     *  \brief Créé une vidéo et l'ajoute
     *  Méthode qui permet de créer un objet Video et l'ajoute à multimediaTable
     *  \param duration : durée de la vidéo
     *  \param name : nom de la vidéo
     *  \param filename : nom du fichier associé à la vidéo
     *  \return smart pointer vers l'objet Video résultant
     */
    std::shared_ptr<Video> createVideo(int duration, const std::string &name, const std::string &fileName);

    /*!
     *  \brief Créé une photo et l'ajoute
     *  Méthode qui permet de créer un objet Photo et l'ajoute à multimediaTable
     *  \param latitude : latitude de la photo
     *  \param longitude : longitude de la photo
     *  \param name : nom de la photo
     *  \param filename : nom du fichier associé à la photo
     *  \return smart pointer vers l'objet Photo résultant
     */
    std::shared_ptr<Photo> createPhoto(float latitude, float longitude, std::string name, std::string fileName);

    /*!
     *  \brief Créé un Film et l'ajoute
     *  Méthode qui permet de créer un objet Film et l'ajoute à multimediaTable
     *  \param array : tableau des durées des chapitres
     *  \param nb : nombre de chapitres
     *  \param duration : durée du film
     *  \param name : nom du film
     *  \param filename : nom du fichier associé à la photo
     *  \return smart pointer vers l'objet Film résultant
     */
    std::shared_ptr<Film> createFilm(int *array, int nb, int duration, std::string name, std::string fileName);

    /*!
     *  \brief Créé un Groupe et l'ajoute
     *  Méthode qui permet de créer un objet Group et l'ajoute à groupTable
     *  \param groupName : nom du groupe
     *  \param sourceList: liste contenant tous les noms de médias du groupe
     *  \return smart pointer vers l'objet groupe résultant
     */
    std::shared_ptr<Group> createGroup(std::string groupName, const std::list<std::string> &sourceList);

    /*!
     *  \brief recherche et affiche un objet multimédia par son nom
     *  Méthode qui permet de rechercher et afficher un objet multimédia par son nom
     *  \param name : nom du média
     *  \param s : flux de sortie souhaité
     */
    void findAndPrintMultimedia(const std::string &name, std::ostream &s) const;

    /*!
     *  \brief recherche et affiche un objet groupe par son nom
     *  Méthode qui permet de rechercher et afficher un objet groupe par son nom
     *  \param groupName : nom du groupe
     *  \param s : flux de sortie souhaité
     */
    void findAndPrintGroup(const std::string &groupName, std::ostream &s) const;

    /*!
     *  \brief recherche et joue un objet multimédia par son nom
     *  Méthode qui permet de rechercher et de jouer  un objet multimédia par son nom
     *  \param name : nom du média
     *  \param s : flux de sortie souhaité
     */
    std::string findAndPlayMultimedia(const std::string &name) const;

    /*!
     *  \brief recherche et supprime un objet multimédia par son nom
     *  Méthode qui permet de rechercher et supprimer un objet multimédia de multimediaTable par son nom
     *  \param multimediaName : nom du média
     */
    void deleteMultimedia(const std::string &multimediaName);

    /*!
     *  \brief recherche et supprime un objet groupe par son nom
     *  Méthode qui permet de rechercher et supprimer un objet grouoe de groupTable par son nom
     *  \param groupName : nom du grouoe
     */
    void deleteGroup(const std::string &groupName);

    /*!
     *  \brief retirer un objet multimédia des groupes qui le contiennent
     *  Méthode qui permet de retirer un objet multimédia des groupes qui le contiennent
     *  \param multimediaName : nom du média
     */
    void removeFromAllGroups(const std::string &multimediaName);

    /*!
     *  \brief trouve les noms de médias qui commencent par une chaîne de caractères donnée
     *  \param charSeq : chaine de caractères à comparer
     * \return liste des noms des médias commençant par charSeq
     */
    std::list<std::string> findMediaStartingWithCharSeq(const std::string &charSeq) const;

    /*!
     *  \brief trouve les noms de médias qui contiennent une chaîne de caractères donnée
     *  \param charSeq : chaine de caractères à comparer
     * \return liste des noms des médias contenant charSeq
     */
    std::list<std::string> findMediaContainingCharSeq(const std::string &charSeq) const;

    /*!
     *  \brief Appelle la méthode de lecture appropriée pour un objet Multimedia
     *  \param mediaName : nom du média à lire
     *  \param f : flux d'entrée souhaité
     */
    void read(std::ifstream &f, std::string mediaName);

    /*!
     *  \brief Appelle la méthode d'écriture appropriée pour un objet Multimedia
     *  \param mediaName : nom du média à écrire
     *  \param f : flux de sortie souhaité
     */
    void write(std::ofstream &f, std::string mediaName);

    /*Find media that are from a certain type
    exemple of use :
    std::list<std::string> matchingNames = findMediaByClassType<Video>();
    I put the function in the header file because when defined in the .cpp file I
    was getting an undefined error
    */
    template <typename T>
    std::list<std::string> findMediaByClassType() const
    {
        std::list<std::string> matchingNames;
        for (const auto &pair : multimediaTable)
        {
            const std::shared_ptr<Multimedia> &media = pair.second;
            if (typeid(*media) == typeid(T))
            {
                matchingNames.push_back(pair.first);
            }
        }
        return matchingNames;
    }

    /*!
     *  \brief renvoie la liste de tous les noms des médias dans multimediaTable
     *  \return liste de tous les noms des médias dans multimediaTable
     */
    std::list<std::string> findAllMedia() const;
};

#endif