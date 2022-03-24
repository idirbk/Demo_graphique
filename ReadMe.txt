
auteur : BOUKARI IDIR

                            ____________________________
                           /                           /
                          /      DÉMO GL4DUMIES       /
                         /___________________________/

1) Les animations :

    1- animation 01 :
         Pour cette animation j'ai utilisé un quadrilatère qui a servi de fond , puis j'ai utilisé 
         des cubes, en leurs appliquant des transformations géométriques j'ai dessiné des lettres 
         qui se positionnent avec le facteur temps puis une fois positionné correctement elles 
         bougent selon l'axe Z selon le son ,j'ai aussi ajouté deux lumières qui changent de 
         position selon le temps et changent de couleur à chaque frame.

    2- animation 02 :
         Cette animation est une évolution du diagramme de voronoi en GPU ,les sites sont générés une 
         seule fois au début de l'animation je n'envoie qu'un seul sites au GPU plus on avance dans 
         le temps plus j'en envoie de sites, les cercles que forment les sites sont limité par le 
         facteur son envoyé en GPU, des cercles périodiques sont ajoutés en GPU .  
 
    3- animation 03 :
         Pour cette animation j'ai voulu construire pondule de NEWTON avec des sphères pour les boules, 
         des cubes pour le cadre et des cylindres pour les cordes, selon le facteur temps le point de vue 
         (variation sur l'axe X).
    
    4- animation 04 :
         Pour cette animation tout sa passe en GPU, c'est un disque qui dont la taille varie selon le son
         et des cercles noirs dans le disque dont la position change selon une variable qui s'incrémente 
         en CPU à chaque frame.

    5- animation 05 :
         Pour cette animation j'ai modélisé une sorte de chambre avec des cubes puis j'ai rajouté une 
         sphère au milieu qui tourne au début, puis après un temps T la sphère change de taille 
         selon la hauteur due est et des petites sphères apparaissent dans l'espace, j'ai aussi ajouté 
         plusieurs lumières qui ont toute une trajectoire bien définie.
    
    6- animation 06 : 
         Cette animation est une variante de l'animation 01 avec des rotations de lettres et des 
         translations.

2) Les transitions :

     1- transition 01 :
          pour la transition en carreaux je fais disparaitre la première animation dans plein de 
          petits carreaux (30 X 30) qui devient de plus en plus petit avec le temps.
     
     2- transition 02 :
          C'est une transition que j'ai nommée en rideau car je fais disparaitre la première animation 
          dans des bandes de plus en plus petites ce qui fait apparaitre la dexième animation.
     
     3- transition 03 :
          Cette transition utilise les coordonnées polaires depuis le centre de la fenêtre, où l'angle 
          où j'affiche la deuxième animation est proportionnel à dt (le temps écoulé).
     
     4- transition 04 :
          Pour cette transition ce son plein de petit cercle où j'affiche la deuxième transition qui 
          grandit de plus en plus selon le dt.
     5- transition 05 :
          Cette transition est la même que la transition 02 mais cette fois les bandes sont en verticale.

3) Le choix de la musique:

     J'ai choisi le son Inception de l'artiste Clone Me Twice telechrgé depuis 
     https:/www.auboutdufilcom/, c'est un son house électro qui convient très bien avec l'ambiance 
     que je voulais donner à ma démo, le son est bien sur libre se doit