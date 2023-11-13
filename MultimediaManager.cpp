#include "MultimediaManager.h"

MultimediaManager::MultimediaManager(const std::map<std::string, std::shared_ptr<Multimedia>> &initialMultimedia,
                                     const std::map<std::string, std::shared_ptr<Group>> &initialGroups)
{
    multimediaTable = initialMultimedia;
    groupTable = initialGroups;
}

// Function to create a Video object and add it to multimediaTable
std::shared_ptr<Video>
MultimediaManager::createVideo(int duration, const std::string &name, const std::string &fileName)
{
    // std::shared_ptr<Video> video = std::make_shared<Video>(duration, name, fileName);
    std::shared_ptr<Video> video(new Video(duration, name, fileName));
    multimediaTable[name] = video;
    return video;
}

// Function to create a Photo object and add it to multimediaTable
std::shared_ptr<Photo>
MultimediaManager::createPhoto(float latitude, float longitude, std::string name, std::string fileName)
{
    std::shared_ptr<Photo> photo(new Photo(latitude, longitude, name, fileName));
    multimediaTable[name] = photo;
    return photo;
}

// Function to create a Film object and add it to multimediaTable
std::shared_ptr<Film>
MultimediaManager::
    createFilm(int *array, int nb, int duration, std::string name, std::string fileName)
{
    std::shared_ptr<Film> film(new Film(array, nb, duration, name, fileName));
    multimediaTable[name] = film;
    return film;
}

// Function to create a Group object and add it to groupTable
// originally I gave a list of Multimedia in argument, but since only MultimediaManager is able
// to manipulate Multimedia objects I had to change the signature
std::shared_ptr<Group>
MultimediaManager::
    createGroup(std::string groupName, const std::list<std::string> &sourceList)
{
    std::list<std::shared_ptr<Multimedia>> list_ptr;
    for (const std::string &element : sourceList)
    {
        auto it = multimediaTable.find(element);
        if (it != multimediaTable.end())
        {
            list_ptr.push_back(it->second);
        }
        else
        {
            std::cerr << "Media :" << element << "not found \n";
        }
    }
    std::shared_ptr<Group> group = std::make_shared<Group>(groupName, list_ptr);
    groupTable[groupName] = group;
    return group;
}

// Fonction pour rechercher et afficher un objet multimédia par son nom
void MultimediaManager::
    findAndPrintMultimedia(const std::string &name, std::ostream &s) const
{
    auto it = multimediaTable.find(name);
    if (it != multimediaTable.end())
    {
        std::shared_ptr<Multimedia> multimedia = it->second;
        multimedia->print(s);
    }
    else
    {
        std::cout << "Multimedia object with name " << name << " not found." << std::endl;
    }
}

// Fonction pour rechercher et afficher un groupe par son nom
void MultimediaManager::
    findAndPrintGroup(const std::string &groupName, std::ostream &s) const
{
    auto it = groupTable.find(groupName);
    if (it != groupTable.end())
    {
        std::shared_ptr<Group> group = it->second;
        std::cout << "Group Name: " << groupName << std::endl;
        std::cout << "Contents of the Group:" << std::endl;
        group->print(s);
    }
    else
    {
        std::cout << "Multimedia object with name " << groupName << " not found." << std::endl;
    }
}

// Fonction pour afficher et jouer un object multimédia par son nom
void MultimediaManager::findAndPlayMultimedia(const std::string &name) const
{
    auto it = multimediaTable.find(name);
    if (it != multimediaTable.end())
    {
        std::shared_ptr<Multimedia> multimedia = it->second;
        multimedia->play();
    }
    else
    {
        std::cout << "Multimedia object with name " << name << " not found." << std::endl;
    }
}

// Méthode pour supprimer un objet multimédia par son nom
void MultimediaManager::deleteMultimedia(const std::string &multimediaName)
{
    auto it = multimediaTable.find(multimediaName);
    if (it != multimediaTable.end())
    {
        // Retirer l'objet multimédia de tous les groupes
        removeFromAllGroups(multimediaName);
        // Supprimer l'objet multimédia de la table
        multimediaTable.erase(it);
    }
}

// Méthode pour supprimer un groupe par son nom
void MultimediaManager::deleteGroup(const std::string &groupName)
{
    auto it = groupTable.find(groupName);
    if (it != groupTable.end())
    {
        // Supprimer le groupe de la table
        groupTable.erase(it);
    }
}

// Méthode pour retirer un objet multimédia des groupes qui le contiennent
void MultimediaManager::removeFromAllGroups(const std::string &multimediaName)
{
    for (auto &group : groupTable)
    {
        group.second->removeMultimediaByName(multimediaName);
    }
}

// Method that find media names that start with a given char sequence
std::list<std::string> MultimediaManager::findMediaStartingWithCharSeq(const std::string &charSeq) const
{
    std::list<std::string> matchingNames;
    for (const auto &pair : multimediaTable)
    {
        const std::string &name = pair.first;
        if (name.find(charSeq) == 0)
        {
            matchingNames.push_back(name);
        }
    }
    return matchingNames;
}

// Method that find media names containing a given char sequence
std::list<std::string> MultimediaManager::findMediaContainingCharSeq(const std::string &charSeq) const
{
    std::list<std::string> matchingNames;
    for (const auto &pair : multimediaTable)
    {
        const std::string &name = pair.first;
        if (name.find(charSeq) != std::string::npos)
        {
            matchingNames.push_back(name);
        }
    }
    return matchingNames;
}

// returns all media names from the map in a list
std::list<std::string> MultimediaManager::findAllMedia() const
{
    std::list<std::string> allNames;
    for (const auto &pair : multimediaTable)
    {
        allNames.push_back(pair.first);
    }
    return allNames;
}

// call read method of a media
void MultimediaManager::read(std::ifstream &f, std::string mediaName){
    auto it = multimediaTable.find(mediaName);
        if (it != multimediaTable.end())
        {
            it->second->read(f);
        }
        else
        {
            std::cerr << "Media :" << mediaName << "not found \n";
        }
}

// call read method of a media
void MultimediaManager::write(std::ofstream &f, std::string mediaName){
    auto it = multimediaTable.find(mediaName);
        if (it != multimediaTable.end())
        {
            it->second->write(f);
        }
        else
        {
            std::cerr << "Media :" << mediaName << "not found \n";
        }
}