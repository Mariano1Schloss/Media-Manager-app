#ifndef Graph_MultimediaManager
#define Graph_MultimediaManager
#include <map>
#include "Multimedia.h"
#include "Film.h"
#include "Video.h"
#include "Photo.h"
#include "Group.h"

Class MultimediaManager
{
private:
    std::map<std::string, std::shared_ptr<Multimedia>> multimediaTable;
    std::map<std::string, Group> groupTable;

public:
    MultimediaManager(const std::map<std::string, std::shared_ptr<Multimedia>> &initialMultimedia,
                      const std::map<std::string, Group> &initialGroups);

    std::shared_ptr<Video> createVideo(int duration, const std::string &name, const std::string &fileName);

    std::shared_ptr<Photo> createPhoto(float latitude, float longitude, std::string name, std::string fileName);

    std::shared_ptr<Film> createFilm(int *array, int nb, int duration, std::string name, std::string fileName);

    std::shared_ptr<Group> createGroup(std::string groupName, const std::list<std::shared_ptr<Multimedia>> &sourceList);
}

#endif