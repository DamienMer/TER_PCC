# Visualisation de Graphe de Flot max et de graphe PCC via Jupyter Notebook

**Auteur : Damien Merret et Matthieu Robeyns**

<br/> Idée principale du projet :
<br/> -Afficher des graphes avec leurs étapes de résolution via Jupyter notebook (Résultat dans [presentation.ipybn]()

<br/> Pour toute compréhesion de nos motivations à faire ce projet, et du code, cliquer sur le fichier [rapport.ipybn]()

Voici les algorithmes exécutables dans ce projet, pour PCC:

- Dikjstra;
- Bellmon-Ford;
- Floyd-Warshall.

Et l'algorithme de calcul de Flot Max :

- FordFulkerson


Lien du Binder (si vous n'avez pas jupyter notebook):

+ [![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/git/https%3A%2F%2Fgitlab.u-psud.fr%2Fter-graphupsud%2Falgorithme_des_plus-courts_chemins_en_cpp.git/master)

### Rappels basiques de Jupyter :

<br/> Installation (sous Linux):

<br/> -Installer Miniconda
<br/> !conda create -n [nomEnv]
<br/> Créer un nouvel environnement Conda
<br/> !conda activate [nomEnv]
<br/>     Active l’environnement Conda 
<br/> !conda install [nomEnv] notebook -c QuantStack
<br/>     Installe Notebook dans l’environnement souhaité
<br/> !conda update jupyter_core jupyter_client
<br/>    Met à jour
<br/> !jupyter notebook
<br/>    Lance le notebook dans le navigateur

<br/>  Il y a plus ou moins 2 types de cellules : les cellules de texte et les cellules de code. Les cellules de textes ne produisent rien lorsqu’elles sont exécutées à la différence des cellules de code. Pour exécuter une cellule de code, il faut la sélectionner en cliquant dessus puis appuyer simultanément sur « ALT » et « ENTER ». Une variable ou un objet vit tant que le kernel n’a pas été Restart. Pour restart le kernel, sélectionner « Kernel » puis « Restart ». Il est possible d’exécuter des commandes Bash en faisant précéder la commande d’un « ! » dans une cellule de code puis en l’exécutant. Le kernel Jupyter exécute initialement du code écrit en python. Il est toutefois possible d’installer un kernel apte à exécuter un autre langage. Par exemple pour installer un kernel C++

<br/> Dans le bash :
<br/> !conda activate [nomEnv]
<br/>    Active l’environnement Conda 
<br/> !conda install -c conda-forge xeus-cling
<br/>    Installe xeus-cling. Xeus-cling permet d’accéder à un kernel C++
<br/> !conda update jupyter_core jupyter_client
<br/>    Met à jour
<br/> !jupyter notebook
<br/>    Lance le notebook dans le navigateur

<br/> Ensuite on sélectionne « New » puis « C++17 ». Du code C++ peut ensuite être écrit et exécuté dans les cellules de codes.