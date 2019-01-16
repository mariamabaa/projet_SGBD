#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "svg.h"


struct entite
{
    char* nom;
    char** attributs;
    int n_attributs;
    char** associations;
    int n_associations;
};

struct association
{
    char* nom;
    char** attributs;
    int n_attributs;
};
typedef struct entite s_entite;
typedef struct association s_association;

void get_nombre_entites_associations(cJSON* json, int* nb_entites, int* nb_associations);
char** get_attributs_entite(cJSON* json, char** attributs, int* n_attributs);
char** get_attributs_association(cJSON* json, char** attributs, int* n_attributs);
void test(cJSON* json, s_entite** tab_entites, s_association** tab_associations);
char** get_associations(cJSON* json, cJSON* parent, char** associations, int* n_associations);
void afficher_entite(s_entite* entite);
void afficher_association(s_association* association);
s_entite* creer_entite(s_entite* e, char* nom, char** attributs, char** associations, int n_attributs, int n_associations);
s_association* creer_association(s_association* a, char* nom, char** attributs, int n_attributs);
int Jtest();
