//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//
/*!
 * \file Group.h
 * \author Mathieu Delbos - adapté de la version d'Eric Lecolinet
 * \brief Serveur TCP qui permet de communiquer avec une interface graphique cliente pour effectuer des actions sur des médias
 * \version 0.1
 */
#define SERVER_MAIN
#ifdef SERVER_MAIN
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
#include "MultimediaManager.h"

const int PORT = 3331;

/*!
 *  \brief Enlève les caractères "\n" et "\r"
 *  \param str : chaine de caractères à traiter
 *  \param manager: objet MultimediaManager utilisé pour manipuler les médias
 *  \return chaine de caractères traitée
 */
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

/*!
 *  \brief requête pour chercher un média et afficher ses informations
 *  \param name : nom du média
 *  \param manager: objet MultimediaManager utilisé pour manipuler les médias
 *  \return infos du média retournées par sa méthode print()
 */
std::string printRequest(std::string const &name, MultimediaManager const *manager)
{
  // Create a string stream to retrieve information from print method
  std::stringstream ss;
  manager->findAndPrintMultimedia(name, ss);
  // removing "\n" and "\r" characters
  std::string str = ss.str();
  return removeEndl(str);
}

/*!
 *  \brief requête pour chercher un média et le jouer
 *  \param name : nom du média
 *  \return status du résultat de la requête
 */
std::string playRequest(std::string const &name, MultimediaManager const *manager)
{

  std::string response = manager->findAndPlayMultimedia(name);
  return removeEndl(response);
}

/*!
 *  \brief Trouve le nom de médias commençant par une séquence de caractères donnée
 *  \param charSeq : séquence de caractères à vérifier
 *  \param manager: objet MultimediaManager utilisé pour manipuler les médias
 *  \return noms de média trouvés
 */
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

/*!
 *  \brief Trouve le nom de médias contenant une séquence de caractères donnée
 *  \param charSeq : séquence de caractères à vérifier
 *  \param manager: objet MultimediaManager utilisé pour manipuler les médias
 *  \return noms de médias trouvés
 */
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

/*!
 *  \brief Trouve le nom de tous les médias gérés par le manager
 *  \param manager: objet MultimediaManager utilisé pour manipuler les médias
 *  \return noms de médias trouvés
 */
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

/*!
 *  \brief Trouve le nom de médias selon leru type (Video, Film ou Photo)
 *  \param type : type des médias à rechercher
 *  \param manager: objet MultimediaManager utilisé pour manipuler les médias
 *  \return noms de médias trouvés
 */
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

/*!
 *  \brief Supprime un groupe par son nom
 *  \param name : nom du groupe à supprimer
 *  \param manager: objet MultimediaManager utilisé pour manipuler les médias
 *  \return status de réponse de la requête
 */
std::string deleteGroupRequest(const std::string &name, MultimediaManager *manager)
{
  manager->deleteGroup(name);
  return "group deleted";
}

/*!
 *  \brief Supprime un média par son nom
 *  \param name : nom du média à supprimer
 *  \param manager: objet MultimediaManager utilisé pour manipuler les médias
 *  \return status de réponse de la requête
 */
std::string deleteMultimediaRequest(const std::string &name, MultimediaManager *manager)
{
  manager->deleteMultimedia(name);
  return "Multimedia deleted";
}

int main(int argc, char *argv[])
{
  //  We need to have a multi-media manager

  // create multimedia manager
  MultimediaManager *manager = new MultimediaManager();
  manager->createVideo(30, "Video 1", "./assets/video1.mp4");
  manager->createVideo(30, "Video 2", "./assets/video2.mp4");
  int array[] = {15, 7, 8};
  manager->createFilm(array, 3, 30, "Film 1", "./assets/film1.mp4");
  manager->createPhoto(640, 426, "Photo 1", "./assets/photo1.jpg");
  manager->createPhoto(1280, 853, "Photo 2", "./assets/photo2.jpg");
  manager->createGroup("Group 1", {"Video 1", "Film 1", "Photo 1"});
  manager->createGroup("Group 2", {"Video 2", "Photo 2"});

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

  // Serialize all the medias in the data.txt file
  std::ofstream outputFile("./assets/data.txt");
  std::list<std::string> medias = manager->findAllMedia();
  for (std::string mediaName : medias)
  {
    manager->write(outputFile, mediaName);
  }
  outputFile.close();

  // cree le TCPServer
  auto *server =
      new TCPServer([&](std::string const &request, std::string &response)
                    {

    // the request sent by the client to the server
    std::cout << "request: " << request << std::endl;

    // the response that the server sends back to the client:
    //converting the request into a string stream
    std::stringstream request_stream (request);
    std::string requestName,requestArgument;
    request_stream >> requestName;
    
// Read the rest of the line into requestArgument
    std::getline(request_stream >> std::ws, requestArgument);    
    if (requestFunctionsMap.find(requestName) != requestFunctionsMap.end()) {
        response = requestFunctionsMap[requestName](requestArgument, manager);  // Call the function
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