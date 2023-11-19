/*!
 * \file Film.h
 * \author Mathieu Delbos
 * \version 0.1
 */

#ifndef Graph_Film
#define Graph_Film
#include "Video.h"
#include <cstring>

/*! \class Film
 * \brief Classe representant un Film, hérite de Video
 */
class Film : public Video
{
private:
    int *chapters = nullptr; /*!< pointeur vers les durées des chapitres du Film*/
    int nb_chapter;          /*!< Nombre de chapitres du film*/

protected:
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Film.
     *  Appelle d'abord le constructeur de Video
     *  Contrainte : la somme des durées des chapitres doit être égale à la durée du film
     *  \param array : tableau des durées des chapitres
     *  \param nb : nombre de chapitres
     *  \param name : nom du Film
     *  \param fileName : nom du fichier associé au Film
     *  \param duration : durée du Film
     */
    Film(int *array, int nb, int duration, std::string name, std::string fileName);

    /*!
     *  \brief Constructeur
     *  Constructeur de base de la classe Film
     *  Appelle d'abord le constructeur de base de Video
     *  Initialise chapters et nb_chapter avec des valeurs défauts
     */
    Film() : Video(), chapters{nullptr}, nb_chapter{0} {}

public:
    friend class MultimediaManager; /*!< On souhaite que seule la classe MultimediaManager puisse instancier Video*/

    /*!
     *  \brief Destructeur
     *  Destructeur de la classe Film
     *  Déalloue la mémoire de chapters
     */
    ~Film() { delete[] chapters; }

    /*!
     *  \brief Getter deu tableau de chapitres
     *  Methode qui permet de retourner la variable d'instance chapters
     *  \return la valeur de la variable d'instance chapters
     */
    const int *getChapters() const;

    /*!
     *  \brief Getter indexé de chapters
     *  Methode qui permet de retourner la durée du chapitre à un index spéicifié
     * \param index: index du chapitre dont on veut connaitre la durée
     *  \return la durée du chapitre à l'index "index"
     */
    const int getChapter(int index) const;

    /*!
     *  \brief Getter du nombre des chapitres
     *  Methode qui permet de retourner la valeure de la variable d'instance nb_chapter
     *  \return le nombre de chapitres nb_chapter
     */
    const int getNbChapter() const { return nb_chapter; }

    /*!
     *  \brief Getter indexé de chapters
     *  Déalloue la mémoire de chapters et initialsie chapters à nullptr et nb_chapter à 0
     */
    void delete_chapters();

    /*!
     *  \brief Setter indexé de chapters
     *  Méthode qui permet de modifier la durée d'un chapitre à un index spécifié
     *  \param index : index du chapitre à modifier
     *  \param value : nouvelle durée du chapitre à modifier
     */
    void setChapterValue(int index, int value);

    /*!
     *  \brief Remplace chapter par un nouveau tableau d'entiers
     *  Supprime le tableau chapters actuel avec la méthode delete_chapters() et le remplace par le tableau passé en paramètres
     *  \param newArray : nouveau tableau de chapitres
     *  \param newArrayLength : longueur du nouveau tableau de chapitres
     */
    void setChapters(const int *newArray, int newArrayLength);

    /*!
     *  \brief Affiche les informations du Film
     *  Methode qui permet d'afficher les informations de Film
     *  Appelle d'abord la méthode print() de Video
     *  \param s: flux de sortie souhaité
     */
    void print(std::ostream &s) const override;

    /*!
     *  \brief Retourne le nom de la classe
     *  Methode qui permet de retourner le nom de la classe : "Film"
     *  \return "Film"
     */
    std::string getClassName() override { return "Film"; }

    /*!
     *  \brief Sérialise un Film
     *  Méthode qui sérialise un objet Film en écrivant sur le flux de sortie f
     *  Appelle d'abord la méthode write() de Video
     *  \param f: flux de sortie souhaité
     */
    void write(std::ofstream &f) override;

    /*!
     *  \brief Désérialise un Film
     *  Méthode qui désérialise un objet Film en lisant sur le flux d'entrée f
     *  Appelle d'abord la méthode read() de Video
     *  \param f: flux d'entrée souhaité
     */
    void read(std::ifstream &f) override;
};
#endif