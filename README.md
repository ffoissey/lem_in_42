# Lem_in
Ce projet permet d'appréhender les algorithmes de parcours de graphe et de gestion de flots.
Le but du projet est de trouver l'ensemble de chemin le plus rapide pour déplacer n fourmis de la salle definis par '##start'
à la salle définie par '##end'. Une seule fourmi peut etre présente par salle et par tour.

Nous avons voulu partir de zero pour developper notre propre algorithme et ainsi pouvoir etre confronter aux problèmes
amenés par ce projet sans avoir de solution toute faite, puis seulement ensuite,
apprendre comment les algorithmes déjà existant resolvent ceux-ci.

Voici une description non-exhaustive de notre algorithme:
* Pour chaque salle: Faire la somme de la distance à la salle START et celle de la salle END.
 1. Si une salle ne donne sur aucune nouvelle salle, toute sa lignée est marquée comme morte et ne sera plus exploré.
 2. Tout les salles ayant un score supérieur au score le plus haut des salles mitoyennes à START ou END seront également marquées comme morte.
 3. --> Ces deux dernières opérations ont pour but de minimiser le nombres de chemins possibles.
* Chaque salle va emettre un 'traceur' vers START et END de sorte que chaque salle est associé qu chemin le plus court passant par celle-ci.
* Les doublons sont éliminés pour n'avoir que des chemins uniques.
* Les chemins obtenus sont triés de celui qui contient le moins de salles à celui qui en contient le plus.
* Chaque chemin est associés à une liste de chemin qui ne croise pas celui-ci et ne se croisent pas entre eux.
* Un score est calculé pour chaque ensemble de chemin en fonction du nombre de chemins, de la taille de ceux-ci et
du nombre de fourmis à déplacer.

### Exemple:
![lemin](https://user-images.githubusercontent.com/40762210/68407578-17831980-0184-11ea-9680-1a86997bae2a.png)
