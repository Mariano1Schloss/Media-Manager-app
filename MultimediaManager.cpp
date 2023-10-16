#include "MultimediaManager.h"

MultimediaManager::MultimediaManager(const std::map<std::string, std::shared_ptr<Multimedia>> &initialMultimedia,
                                     const std::map<std::string, Group> &initialGroups)
{
    multimediaTable = initialMultimedia;
    groupTable = initialGroups;
}

// Function to create a Video object and add it to multimediaTable
MultimediaManager::
    std::shared_ptr<Video>
    createVideo(int duration, const std::string &name, const std::string &fileName)
{
    std::shared_ptr<Video> video = std::make_shared<Video>(duration, name, fileName);
    multimediaTable[name] = video;
    return video;
}

// Function to create a Photo object and add it to multimediaTable
MultimediaManager::
    std::shared_ptr<Photo>
    createPhoto(float latitude, float longitude, std::string name, std::string fileName)
{
    std::shared_ptr<Photo> photo = std::make_shared<Photo>(latitude, longitude, name, fileName);
    multimediaTable[name] = photo;
    return photo;
}

// Function to create a Film object and add it to multimediaTable
MultimediaManager::
    std::shared_ptr<Film>
    createFilm(int *array, int nb, int duration, std::string name, std::string fileName)
{
    std::shared_ptr<Film> film = std::make_shared<Film>(array, nb, duration, name, fileName);
    multimediaTable[name] = film;
    return film;
}

// Function to create a Group object and add it to groupTable
MultimediaManager::
    std::shared_ptr<Group>
    createGroup(std::string groupName, const std::list<std::shared_ptr<Multimedia>> &sourceList)
{
    std::shared_ptr<Group> group = std::make_shared<Group>(groupName, sourceList);
    groupTable[groupName] = group;
    return group;
}