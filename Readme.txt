Camus Tristan
Cojez Arnaud


Q11.
  L'avion se penche toujours de la même façon sans prendre en compte sa rotation.
  Nous constatons également qu'en mettant l'avion à la verticale, A-E et Q-D ont le même effet. (rotation de l'avion autour de la verticale)

Q12.
  Les angles sont modifiés dans l'ordre yaw, pitch, roll.
  Seulement, comme on modifie le repère à chaque fois, le yaw est modifié par rapport à un repère neutre. Puis le pitch par rapport au repère de base + yaw. Enfin le roll par rapport au repère de base + yaw + pitch.
  Donc le pitch ne prend pas en compte la rotation effectuée par le roll. D'où les problèmes d'interaction vus plus haut.

Q13.
Maintenant on modifie le repère en "ajoutant" de la rotation à la matrice de rotation précédente. Ce qui fait que tous les axes sont pris en compte lors de la rotation. 

Doit contenir :
- ce que vous n'avez pas fait (et pourquoi). Précisez explicitement "tout à été fait et fonctionne parfaitement" si c'est le cas.
- difficultés rencontrées.
- commentaires éventuels sur le TP (points à éclaircir, longueur du sujet, etc). 
