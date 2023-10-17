#ifndef Graph_Group
#define Graph_Group
#include <list>
#include <string>
#include <memory>
#include "Multimedia.h"

class Group : public std::list<std::shared_ptr<Multimedia>>
{
private:
    std::string name;

public:
    Group(std::string groupName, const std::list<std::shared_ptr<Multimedia>> &sourceList)
        : std::list<std::shared_ptr<Multimedia>>(sourceList), name(groupName) {}

    ~Group()
    {
        std::cout << "Destroying Group object: " << name << std::endl;
    }
    const std::string getName() const
    {
        return name;
    }
    void print(std::ostream &s) const
    {
        for (const auto &media : *this)
        {
            media->print(s);
        }
    }
    
    //Méthode pour vérifier si un groupe contient un objet multimédia par son nom et le retire de la liste le cas échéant
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
