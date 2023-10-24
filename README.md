TO DO :
Constructeur vide et destructeur??
COMMENTER
Pour les segfault : valgrind ./myprog

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