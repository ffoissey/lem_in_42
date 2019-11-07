# Lem_in
*Ce projet permet d'appréhender les algorithmes de parcours de graphe et de gestion de flots.*

Le but du projet est de trouver l'ensemble de chemins le plus rapide pour déplacer n fourmis de la salle definie par '##start'
à la salle définie par '##end'. Une seule fourmi peut etre présente par salle et par tour.

Nous avons voulu partir de zéro pour développer notre propre algorithme et ainsi pouvoir être confronté aux problèmes
amenés par ce projet sans avoir une solution toute faite, puis seulement ensuite,
apprendre comment les algorithmes déjà existant resolvent ceux-ci.

Voici une description non-exhaustive de notre algorithme:
* Pour chaque salle: Faire la somme de la distance à la salle START et celle de la salle END.
 1. Si aucune salle ne succède à la salle courante, toute sa lignée est marquée comme morte et ne sera plus explorée.
 2. Tout les salles ayant un score supérieur au score le plus haut des salles mitoyennes à START ou END seront également marquées comme morte.
 
     --> Ces deux dernières opérations ont pour but de minimiser le nombre de chemins possibles.
* Chaque salle va émettre un 'traceur' vers START et END de sorte que chaque salle soit associé au chemin le plus court passant par celle-ci.
* Les doublons sont éliminés pour n'avoir que des chemins uniques.
* Les chemins obtenus sont triés de celui qui contient le moins de salles à celui qui en contient le plus.
* Chaque chemin est associés à une liste de chemins qui ne croisent pas celui-ci et ne se croisent pas entre eux.
* Un score est calculé pour chaque ensemble de chemin en fonction du nombre de chemins, de la taille de ceux-ci et
du nombre de fourmis à déplacer.
* Le déplacement est effectué sur le meilleur ensemble.

### Exemple de marquage:
![lemin](https://user-images.githubusercontent.com/40762210/68407578-17831980-0184-11ea-9680-1a86997bae2a.png)

### Utilisation:
Le programme lit sur l'entrée standard.
Des maps d'exemples sont présentes dans le dossier maps2 tandis que le dossier maps contient des maps d'erreur.
Un executable 'generator' est également présent à la racine pour générer d'autres maps.

#### Usage: 
make && ./lem-in < maps_exemple 
