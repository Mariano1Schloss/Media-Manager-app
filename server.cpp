//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//
#define SERVER_MAIN
#ifdef SERVER_MAIN
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
#include "MultimediaManager.h"

const int PORT = 3331;

// removing "\n" and "\r" characters
std::string removeEndl(std::string str)
{
  std::string result;
  for (char c : str)
  {
    if (c != '\n' && c != '\r')
    {
      result += c;
    }
  }
  return result;
}

// Search for a multimedia object or a group and display its attributes on the 'remote control'
std::string printRequest(std::string const &name, MultimediaManager const *manager)
{
  // Create a string stream to retrieve information from print method
  std::stringstream ss;
  manager->findAndPrintMultimedia(name, ss);
  // removing "\n" and "\r" characters
  std::string str = ss.str();
  return removeEndl(str);
}

// Play a media by its name
std::string playRequest(std::string const &name, MultimediaManager const *manager)
{
  manager->findAndPlayMultimedia(name);
  std::string response = "Media was played";
  return removeEndl(response);
}

// find media names that start with a given char sequence
std::string startWithCharSeqRequest(const std::string &charSeq, MultimediaManager const *manager)
{
  std::string response;
  std::list<std::string> results = manager->findMediaStartingWithCharSeq(charSeq);
  for (const std::string &item : results)
  {
    response += item + " ";
  }
  return response;
}

// find media names that contain a given char sequence
std::string containCharSeqRequest(const std::string &charSeq, MultimediaManager const *manager)
{
  std::string response;
  std::list<std::string> results = manager->findMediaContainingCharSeq(charSeq);
  for (const std::string &item : results)
  {
    response += item + " ";
  }
  return response;
}

// find all media names contained in the dbb
std::string getAllMediaRequest(const std::string &s, MultimediaManager const *manager)
{
  std::string response;
  std::list<std::string> results = manager->findAllMedia();
  for (const std::string &item : results)
  {
    response += item + " ";
  }
  return response;
}

// find media names for a specific type
std::string getMediaByTypeRequest(const std::string &type, MultimediaManager const *manager)
{
  std::list<std::string> results;
  if (type == "Video")
  {
    results = manager->findMediaByClassType<Video>();
  }
  else if (type == "Film")
  {
    results = manager->findMediaByClassType<Film>();
  }
  else if (type == "Photo")
  {
    results = manager->findMediaByClassType<Photo>();
  }

  std::string response;
  for (const std::string &item : results)
  {
    response += item + " ";
  }
  return response;
}

// delete a group by its name
std::string deleteGroupRequest(const std::string &name, MultimediaManager *manager)
{
  manager->deleteGroup(name);
  return "group deleted";
}

// delete a object by its name
std::string deleteMultimediaRequest(const std::string &name, MultimediaManager *manager)
{
  manager->deleteMultimedia(name);
  return "Multimedia deleted";
}

int main(int argc, char *argv[])
{
  // We need to have a multi-media manager
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
  std::list<std::shared_ptr<Multimedia>> group1Items = {film1, photo2, video1, video2};
  std::shared_ptr<Group> group1 = std::make_shared<Group>("Group 1", group1Items);
  std::list<std::shared_ptr<Multimedia>> group2Items = {photo1, video2};
  std::shared_ptr<Group> group2 = std::make_shared<Group>("Group 2", group2Items);

  // Create a map for Multimedia items
  std::map<std::string, std::shared_ptr<Multimedia>> multimediaMap;
  multimediaMap["Video 1"] = video1;
  multimediaMap["Video 2"] = video2;
  multimediaMap["Film 1"] = film1;
  multimediaMap["Photo 1"] = photo1;
  multimediaMap["Photo 2"] = photo2;

  // Create a map for Groups
  std::map<std::string, std::shared_ptr<Group>> groupMap;
  groupMap["Group 1"] = group1;
  groupMap["Group 2"] = group2;

  // create multimedia manager
  MultimediaManager *manager = new MultimediaManager(multimediaMap, groupMap);

  // create a method map
  std::map<std::string, std::function<std::string(const std::string &, MultimediaManager *)>> requestFunctionsMap;
  requestFunctionsMap["printRequest"] = printRequest;
  requestFunctionsMap["deleteMultimediaRequest"] = deleteMultimediaRequest;
  requestFunctionsMap["deleteGroupRequest"] = deleteGroupRequest;
  requestFunctionsMap["getMediaByTypeRequest"] = getMediaByTypeRequest;
  requestFunctionsMap["getAllMediaRequest"] = getAllMediaRequest;
  requestFunctionsMap["containCharSeqRequest"] = containCharSeqRequest;
  requestFunctionsMap["startWithCharSeqRequest"] = containCharSeqRequest;
  requestFunctionsMap["playRequest"] = playRequest;

  // cree le TCPServer
  auto *server =
      new TCPServer([&](std::string const &request, std::string &response)
                    {

    // the request sent by the client to the server
    std::cout << "request: " << request << std::endl;

    // the response that the server sends back to the client
    //converting the request into a string stream
    std::stringstream request_stream (request);
    std::string first_word,second_word;
    request_stream >> first_word;
    request_stream >> second_word;
    
    if (requestFunctionsMap.find(first_word) != requestFunctionsMap.end()) {
        response = requestFunctionsMap[first_word](second_word, manager);  // Call the function
    } else {
        std::cout << "Function not found." << std::endl;
            response = "RECEIVED: " + request;

    }
    // return false would close the connecytion with the client
    return true; });

  // lance la boucle infinie du serveur
  std::cout << "Starting Server on port " << PORT << std::endl;

  int status = server->run(PORT);

  // en cas d'erreur
  if (status < 0)
  {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
  }

  return 0;
}

#endif