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

class MultimediaManager
{
private:
    std::map<std::string, std::shared_ptr<Multimedia>> multimediaTable;
    std::map<std::string, std::shared_ptr<Group>> groupTable;

public:
    // Constructor
    MultimediaManager(const std::map<std::string, std::shared_ptr<Multimedia>> &initialMultimedia,
                      const std::map<std::string, std::shared_ptr<Group>> &initialGroups);

    MultimediaManager(){};

    // Function to create a Video object and add it to multimediaTable
    std::shared_ptr<Video> createVideo(int duration, const std::string &name, const std::string &fileName);

    // Function to create a Photo object and add it to multimediaTable
    std::shared_ptr<Photo> createPhoto(float latitude, float longitude, std::string name, std::string fileName);

    // Function to create a Film object and add it to multimediaTable
    std::shared_ptr<Film> createFilm(int *array, int nb, int duration, std::string name, std::string fileName);

    // Function to create a Group object and add it to groupTable
    std::shared_ptr<Group> createGroup(std::string groupName, const std::list<std::string> &sourceList);

    // Fonction pour rechercher et afficher un objet multimédia par son nom
    void findAndPrintMultimedia(const std::string &name, std::ostream &s) const;

    // Fonction pour rechercher et afficher un groupe par son nom
    void findAndPrintGroup(const std::string &groupName, std::ostream &s) const;

    // Fonction pour afficher et jouer un object multimédia par son nom
    void findAndPlayMultimedia(const std::string &name) const;

    // Méthode pour supprimer un objet multimédia par son nom
    void deleteMultimedia(const std::string &multimediaName);

    // Méthode pour supprimer un groupe par son nom
    void deleteGroup(const std::string &groupName);

    // Méthode pour retirer un objet multimédia des groupes qui le contiennent
    void removeFromAllGroups(const std::string &multimediaName);

    // Method that find media names that start with a given char sequence
    std::list<std::string> findMediaStartingWithCharSeq(const std::string &charSeq) const;

    // Method that find media names containing a given char sequence
    std::list<std::string> findMediaContainingCharSeq(const std::string &charSeq) const;

    //call read method of a media
    void read(std::ifstream &f,std::string mediaName);

    //call read method of a media
    void write(std::ofstream &f,std::string mediaName);

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

    // returns all media names from the map in a list
    std::list<std::string> findAllMedia() const;
};

#endif