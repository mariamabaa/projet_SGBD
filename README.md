# projet_SGBD





Projet SGBD :		Reverse Engineering – Ingenierie inversée

Langage utilisé :	langage C

Membres :		
			MARIAMA  BA et ADJA  AIDA  KONE
			
Lien github : github.com/mariamabaa/projet_SGBD

Commande : gcc main.c JSON_checker.c cJSON.c extraction_XML.c extraction_JSON.c svg.c  `xml2-config --cflags` -std=c11 -o main `xml2-config --libs`

 #   1. Librairies utilisées :
        1. XML
            ▪ Libxml2 
Libxml2 est une bibliothèque utilisée pour l'analyse de documents XML.
Dans le cadre de notre projet, nous avons inclus les fichiers libxml/tree.h et libxml/parser.h pour l’analyse et la validation d’un document XML.
Pour compiler un programme utilisant la libxml2, il faudra les options suivantes :
$ xml2-config --cflags
-I/usr/include/libxml2
-- chemin d'inclusion des fichiers .h
$ xml2-config --libs
-lxml2 -lz -lpthread -lm
-- les librairies dynamiques pour l'édition de liens


        2. JSON
            ▪ JSON_checker

JSON_checker est un automate à pile qui détermine très rapidement si un fichier JSON
le texte est syntaxiquement correct.  Il pourrait être utilisé pour filtrer les entrées d’un système,
ou pour vérifier que les sorties d'un système sont syntaxiquement correctes.  Ça pourrait
être adapté pour produire un analyseur JSON très rapide.

JSON_checker est composé de ces fichiers:

JSON_checker.c Le JSON_checker.
JSON_checker.h Le fichier d'en-tête JSON_checker.

main.c Un exemple d'application.

            ▪ cJSON 

cJSON a pour objectif d'être l'analyseur le plus stupide possible avec lequel vous pouvez effectuer votre travail. C'est un fichier unique de C et un fichier d'en-tête unique.
JSON est mieux décrit ici: http://www.json.org/ C'est comme XML, mais sans gras. Vous l'utilisez pour déplacer des données, stocker des éléments ou simplement représenter l'état de votre programme.
           
        3. SVG

            ▪ svg.c

C’est  une bibliothèque qui peut être compilée et réutilisée dans différents projets, ainsi qu’une application cliente pour la tester et en démontrer l’utilisation. La bibliothèque comprendra les éléments suivants: 

    • Une structure pour contenir le texte du fichier SVG 
    • Une fonction pour créer un nouveau document SVG vide 
    • Fonctions permettant d'ajouter des cercles, des lignes, des rectangles, du texte et des ellipses, ainsi que de remplir l'arrière-plan 
    
    • Une fonction pour finaliser le document SVG (essentiellement fermer la balise SVG) 
    • Une fonction pour l'enregistrer en fichier 
    • Une fonction pour imprimer le contenu du document 
    • Une fonction "libre" très importante pour libérer toute la mémoire utilisée 

Malgré sa simplicité, il présente de nombreuses fonctionnalités C, ainsi que les principes de base nécessaires à la création d’une bibliothèque de codes réutilisable, notamment: 

    • utiliser une structure pour contenir le document et les données associées 
    • créer un ensemble de fonctions pour manipuler le document 
    • gestion de la mémoire: le redouté malloc, realloc et les fonctions gratuites! 
    • créer une bibliothèque réutilisable 
    • main.c - contient le code pour utiliser la bibliothèque 
    • svg.h - le fichier d'en-tête de la bibliothèque 
    • svg.c - l'implémentation de la bibliothèque 

#    2. Fonctions utilisées :
        1. XML :
            ▪ void traverse_dom_trees(svg* psvg,xmlNode * a_node);
la fonction traverse_dom_trees permet de parcourir les noeuds et ensuite afficher leur valeur.

            ▪ int XXtest();
XXtest qui permet d'afficher les entités, attributs et associations du fichier fourni en paramètre.

        2. JSON 

            ▪ char** get_attributs_entite(cJSON* json, char** attributs, int* n_attributs);
            ▪ char** get_attributs_association(cJSON* json, char** attributs, int* n_attributs);
            ▪ void test(cJSON* json, s_entite** tab_entites, s_association** tab_associations);
            ▪ char** get_associations(cJSON* json, cJSON* parent, char** associations, int* n_associations);
            ▪ void afficher_entite(s_entite* entite);
            ▪ void afficher_association(s_association* association);
            ▪ int Jtest();

        3. SVG
            ▪ svg* svg_create(int width, int height);
            ▪ void svg_finalize(svg* psvg);
            ▪ void svg_print(svg* psvg);
            ▪ void svg_save(svg* psvg, char* filepath);
            ▪ void svg_free(svg* psvg);
            ▪ void svg_circle(svg* psvg, char* stroke, int strokewidth, char* fill, int r, int cx, int cy);
            ▪ void svg_line(svg* psvg, char* stroke, int strokewidth, int x1, int y1, int x2, int y2);
            ▪ void svg_rectangle(svg* psvg, int width, int height, int x, int y, char* fill, char* stroke, int strokewidth, int radiusx, int radiusy);
            ▪ void svg_fill(svg* psvg, char* fill);
            ▪ void svg_text(svg* psvg, int x, int y, char* fontfamily, int fontsize, char* fill, char* stroke, char* text);
            ▪ void svg_ellipse(svg* psvg, int cx, int cy, int rx, int ry, char* fill, char* stroke, int strokewidth); 
