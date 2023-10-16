//
// main.cpp
// Created on 21/10/2018
//
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"
#include <iostream>
#include <memory>
using namespace std;

// Function that displays Media and plays it disregarding of its type
void playMedias(Multimedia **tab, unsigned int count)
{
    for (unsigned int k = 0; k < count; ++k)
    {
        tab[k]->print(std::cout);
        tab[k]->play();
    }
}

int main(int argc, const char *argv[])
{
    //typedef std::shared_ptr<Video> VideoPtr;
    //typedef std::shared_ptr<Photo> PhotoPtr;

    // Prints questions 3 et 4
    std::cout << "Hello brave new world" << std::endl;
    // Multimedia *media = new Multimedia("test name ", "test fileName");
    // media->print(std::cout, media); -> Cannot work since Multimedia became abstract

    // Prints question 4
    /*Photo *photo = new Photo(1,1,"photo 1","/mnt/c/Users/ICM2 A/césure/photos asie sud est/Ekas/20220426133550_IMG_2623.JPG");
    photo->print(std::cout);
    photo->play();*/

    /*Video *video = new Video(5,"test","/mnt/c/Users/mathi/Videos/VID_20220314_150046.mp4");
    video->print(std::cout);
    video->play();*/

    // Prints question 5
    /*Film f1 = Film();
    int array[] = {1, 2, 3};
    Film f2 = Film(array, 3, 6, "first film", "./mvie.mp4");
    printf("\nprint1\n");
    f1.print(std::cout);
    printf("\n");
    const int *chapters = f2.getChapters();
    int chapter = f2.getChapter(1);
    f2.setChapterValue(0, 3);
    printf("\nprint2\n");
    f2.print(std::cout);
    int array2[] = {3, 4, 5, 6};
    f2.setChapters(array2, 4);
    printf("\nprint3\n");

    f2.print(std::cout);*/

    // prints question 8

    // VideoPtr video = new Video(5, "test", "/mnt/c/Users/mathi/Videos/VID_20220314_150046.mp4");
    /*VideoPtr video = std::make_shared<Video>(5, "test", "/mnt/c/Users/mathi/Videos/VID_20220314_150046.mp4");
    int array[] = {1, 2, 3};
    Film *f2 = new Film(array, 3, 6, "first film", "./mvie.mp4");
    // PhotoPtr photo = new Photo(1, 1, "photo 1", "/");
    PhotoPtr photo = std::make_shared<Photo>(1, 1, "photo 1", "/");
    std::list<Multimedia *> list1 = {video, f2, photo};
    std::list<Multimedia *> list2 = {video, f2, photo};
    Group *group1 = new Group("group 1", list1);
    Group *group2 = new Group("group 2", list2);*/

    // Create Video objects
    std::shared_ptr<Multimedia> video1 = std::make_shared<Video>(5, "Video 1", ".");
    std::shared_ptr<Multimedia> video2 = std::make_shared<Video>(6, "Video 2", ".");

    // Create Film objects
    int array[] = {1, 2, 3};
    std::shared_ptr<Multimedia> film1 = std::make_shared<Film>(array, 3, 6, "Film 1", "./movie.mp4");

    // Create Photo objects
    std::shared_ptr<Multimedia> photo1 = std::make_shared<Photo>(1, 1, "Photo 1", ".");
    std::shared_ptr<Multimedia> photo2 = std::make_shared<Photo>(2, 2, "Photo 2", ".");

    // Create Group objects composed of films, videos, and photos
    Group *group1 = new Group("Group 1", {film1, photo2, video1, video2});
    Group *group2 = new Group("Group 2", {photo1, video2});

    group1->print(std::cout);
    delete group1;
    group2->print(std::cout);
    group2->pop_front();
    return 0;
};