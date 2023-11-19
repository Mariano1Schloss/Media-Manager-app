TO DO :
Constructeur vide et destructeur??
COMMENTER
Pour les segfault : valgrind ./myprog
VERIFIER TOUS les IFDEF etc..
INITIALISER LES POINTEURS ET TYPES DE BASE
Ameliorer la qualité de renvoi des prints?
faire une description des formats de sérialisation utilisés
#### 
solution question 7: implémentation copie profonde???
####

//4 
Pourquoi redéfinir print() dans Photo.h??
Gestion d'erreur dans play()
voir question tp sur la classe abstraite
this.get ou get directement?

//5 
1) C'est le polymorphisme qui nous permet de faire cela
2)EN C++, on doit utiliser des fonctions virtuelles
3)Le type des éléments doit être un pointeur vers le type MultiMedia.
Dynamic Binding: Polymorphism is often achieved through dynamic binding, which means that the correct function implementation is determined at runtime based on the actual type of the object being pointed to. This dynamic binding mechanism relies on using pointers or references to allow the selection of the correct overridden function at runtime.

Avoiding Object Slicing: If you were to work with objects directly (not using pointers or references), you would encounter object slicing issues. Object slicing occurs when you assign a derived class object to a base class object, and the derived class-specific data is sliced off, leaving only the base class portion. By using pointers or references, you avoid this problem and retain the full functionality of the derived class

//6
Checker somme chapitres = duration
QUAND TABLEAU : DEUX VARIABLES : TAILLE TABLEAU ET TABLEAU
INITIALISER LES VARIABLES
//7
A faire, s'aider du cours

//9
Dans main , créer des types pour les smart pointers pour plus de visibilité# Media-Manager-app
UNIFORMISER LA LANGUE DES COMMENTAIRES

//10
Réponse à la question : rendre le constructeur de Multimedia privé et déclarer la classe MultimediaManager comme ami
Faut -il déclarer tous les constructeurs hérédités comme privés aussi?

A voir : est ce nécessaire de passer toujours les variables par référence dans les signatures de fonction

TESTER LA CLASSE

//11
Gérer la gestion d'erreur dans la recherche de fichier ??
PAreil avant de play le fichier dans le cas où aucun fichier n'est trouvé
PAreil dans la suppression
use of typeid dans le template : bof 

//12 ETAPES :
1) Ecrire les méthodes de renvoi de fichier dans MULTIMEDIA,FILM, VIDEO, PHOTO
2)ECRIRE LES methodes de lecture/ecriture dans MULTIMEDIA,FILM, VIDEO, PHOTO
        -> test d'erreur dans la conversion str->long dans Photo??
        si y a le temps faire les questions additionelles

Format de sérialisation : 
Nom de la classe (Photo, Video ou Film)
Nom du média
Chemin d'accès du fichier
Attributs du média:
        -Pour les photos: 
                Latitude
                Longitude
        -Pour les vidéos:
                Durée
        -Pour les films:
                durée
                nombre de chapitres
                Une ligne par durée de chapitre, dans l'ordre chronologique des chapitres