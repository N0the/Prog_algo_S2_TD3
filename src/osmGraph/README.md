``Exo 1 :``

Commande pour extract :
./osmGraph.exe extract data/test.osm data/test_extract.graph

Commande pour simplify :
./osmGraph.exe simplify data/test_extract.graph

Commande pour visualize :
./osmGraph.exe visualize data/test_extract.graph

``Exo 2 :``

**1.**
Les structures WeightedGraph et PositionedGraph sont définis dans ces deux fichiers (voici les liens de ces fichiers) :

Chemin des WeightedGraph : [src/dataStructure/weightedGraph.hpp](src/dataStructure/weightedGraph.hpp)

Chemin des PositionedGraph : [src/osm/positionedGraph.hpp](src/osm/positionedGraph.hpp)

La structure WeightedGraph va permettre de stocker les poids des différents arêtes adjacents. Elle possède également les méthodes d'un graphe.
La structure PoisitionedGraph va permettre de stocker la position des différents noeuds (en latitude et longitude) et possède un WeightedGraph, en plus des positions. Elle possède également les méthodes d'un graphe.

**2.**
extraction OSM : Ce module va d'abord charger le fichier OSM rentrer en paramètre, puis extraire du fichier les noeuds, poids et limite (latitude et longitude max).
Elle va afficher le nombre de noeuds et de chemins et enfin, va supprimer les rails et bâtiments afin de retourner un graph.

simplification : Ce module va par différentes étapes, simplifier le graphe (voir partie 3 pour les étapes)

visualisation : Ce module tout simplement permettre de visualiser notre carte et d'y incorporer les différentes commandes possibles dans la visualisation. Elle permet également d'afficher le chemin le plus rapide avec la touche D (via l'algo de Dijkstra).

**3.**

La partie simplification va permettre de simplifier le graphe en plusieurs étapes :

**1. Garder uniquement la plus grande composante connexe** : On supprime tous les îlots
isolés du graphe pour ne garder que la composante la plus grande. Cela permet d'éviter
les zones inaccessibles et de garantir qu'un chemin existe entre n'importe quels
noeuds. L'inconvénient est qu'on perd des zones potentiellement utiles si elles sont
isolées (la carte est donc simplifié à ce niveau là).

**2. Supprimer les petites arêtes terminales** : On supprime les noeuds n'ayant qu'un
seul voisin et dont la distance à ce voisin est inférieure à 10 mètres. Cela permet
d'éliminer les impasses trop courtes qui n'apportent pas d'information utile, ça peut en revanche
supprimer des entrées de bâtiments ou des chemins courts.

**3. Supprimer les noeuds de degré 2 alignés** : On supprime les noeuds qui sont au
milieu d'une route (deux voisins) et dont l'angle avec ses voisins est proche de 180 degré (un noued au milieu d'une droite).
On réduit le nombre de noeuds inutile sur notre trajet. L'inconvénient est qu'on perd la
précision des courbes légères si le seuil d'angle est trop élevé.

**4. Fusionner les noeuds trop proches** : On regroupe les noeuds qui sont très proches
en un seul noeud. Cela permet de simplifier les intersections complexes
(ronds-points, carrefours) qui sont représentées par de nombreux noeuds dans les données
OSM. Mais on réduit la précision de ces zones.

**5. Répéter la suppression des noeuds de degré 2** : On répète l'étape 3 après la
fusion car de nouveaux noeuds alignés ont pu apparaître suite à la phase de fusion.

Toutes ces étapes combinées permettent de réduire drastiquement le nombre de noeuds
tout en conservant la structure essentielle du graphe pour le calcul de chemins. Mais nous perdant en revanche certains détails de la carte


``Exo 3.``

**1.** Voir le code dans : [src/dataStructure/graphUtils.cpp](src/dataStructure/graphUtils.cpp)

Image de la carte : 

![Carte](img/image_map.png)