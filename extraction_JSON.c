#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "extraction_JSON.h"



int px=300 , py=50;

/* Parse text to JSON, then render back to text, and print! */
void doit(char *text)
{
    char *out = NULL;
    cJSON *json = NULL;

    json = cJSON_Parse(text);
    if (!json)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    }
    else
    {
        out = cJSON_Print(json);
        cJSON_Delete(json);
        printf("%s\n", out);
        free(out);
    }
}

/* Cette fonction permet de recuper le contenu du fichier json au niveau d'une chaine de caracteres */
char* chaine_json(char *filename)
{
    FILE *f = NULL;
    long len = 0;
    char *json_data = NULL;

    /* Ouverture du fichier json en mode lecture et binaire */
    f = fopen(filename,"rb");
    /* On place le curseur a la fin et on recupere le nombre de caracteres du fichier, du debut jusqu'a la fin */
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);

    /*Creation d'une chaine de len+1 caracteres */
    json_data = (char*)malloc(len + 1);

    /* On lit et on stocke toutes les caracteres au niveau de json_data*/
    fread(json_data, 1, len, f);
    json_data[len] = '\0';
    fclose(f);

    return json_data;
}

void test2(cJSON* json, s_entite** tab_entites, s_association** tab_associations){
    int n_attributs = 0;
    int n_associations = 0;
    static int current_entite = 0;
    static int current_association = 0;
    char** attributs = NULL;
    char** associations = NULL;
    s_entite* e = NULL;
    s_association* a = NULL;
    cJSON *current_element = NULL;
    static cJSON* parent = NULL;
    if(cJSON_IsArray(json)){
        attributs = get_attributs_entite(json->child, attributs, &n_attributs);
        associations = get_associations(json->child, parent, associations, &n_associations);
        e = creer_entite(e, json->string, attributs, associations, n_attributs, n_associations);
        tab_entites[current_entite] = e;
        current_entite++;
        // afficher_entite(e);
        if(json->child)
            test2(json->child, tab_entites, tab_associations);
    }

    if(cJSON_IsString(json)){
        if(json->next)
            test2(json->next, tab_entites, tab_associations);
    }

    if(cJSON_IsObject(json)){
        if(json->string){
            attributs = get_attributs_association(json, attributs, &n_attributs);
            a = creer_association(a, json->string, attributs, n_attributs);
            tab_associations[current_association] = a;
            current_association++;
            // afficher_association(a);
            parent = json;
        }
        if(json->child)
            test2(json->child, tab_entites, tab_associations);
    }
}

void test(cJSON* json, s_entite** tab_entites, s_association** tab_associations){
    // printf("Size : %d\n", cJSON_GetArraySize(json));
    cJSON *current_element = NULL;
    char *current_key = NULL;

    cJSON_ArrayForEach(current_element, json)
    {
     
        test2(current_element, tab_entites, tab_associations);
    }
}

char** get_attributs_entite(cJSON* json, char** attributs, int* n_attributs){
    *n_attributs = 0;
    int i = 0;
    cJSON *current_element = NULL;
    /*On recupere le nombre d'attributs*/
    cJSON_ArrayForEach(current_element, json){
        if(cJSON_IsString(current_element))
            *n_attributs = *n_attributs + 1;
    }
    /*Allocation dynamique d'un tableau de n_attributs*/
    attributs = malloc( (*n_attributs) * sizeof(char*));
    current_element = NULL;
    /*On remplit le tableau passe en parametre avec les attributs*/
    cJSON_ArrayForEach(current_element, json){
        if(cJSON_IsString(current_element)){
            attributs[i] = (char*)malloc((strlen(current_element->string)+1)*sizeof(char));
            attributs[i] = current_element->string;
            i++;
        }
    }
    return attributs;
}

char** get_attributs_association(cJSON* json, char** attributs, int* n_attributs){
    *n_attributs = 0;
    int i = 0;
    cJSON *current_element = NULL;
    /*On recupere le nombres d'attributs*/
    cJSON_ArrayForEach(current_element, json){
        if(cJSON_IsString(current_element))
            *n_attributs = *n_attributs + 1;
    }
    /*Allocation dynamique d'un tableau de n_attributs*/
    attributs = malloc((*n_attributs) * sizeof(char*));
    current_element = NULL;
    /*On remplit le tableau passe en parametre avec les attributs*/
    cJSON_ArrayForEach(current_element, json){
        if(cJSON_IsString(current_element)){
            attributs[i] = (char*)malloc((strlen(current_element->string)+1)*sizeof(char));
            attributs[i] = current_element->string;
            i++;
        }
    }
    return attributs;
}

char** get_associations(cJSON* json, cJSON* parent, char** associations, int* n_associations){
    *n_associations = 0;
    int i = 0;
    cJSON *current_element = NULL;
    if(cJSON_IsObject(parent) && parent->string){
        *n_associations = *n_associations + 1;
    }
    /*On recupere le nombre d'associations*/
    cJSON_ArrayForEach(current_element, json){
        if(cJSON_IsObject(current_element))
            *n_associations = *n_associations + 1;
    }
    /*Allocation dynamique d'un tableau de n_associations*/
    associations = malloc( (*n_associations) * sizeof(char*));
    if(cJSON_IsObject(parent) && parent->string){
        associations[i] = (char*)malloc((strlen(parent->string)+1)*sizeof(char));
        associations[i] = parent->string;
        i++;
    }
    current_element = NULL;
    /*On remplit le tableau passe en parametre avec les associations*/
    cJSON_ArrayForEach(current_element, json){
        if(cJSON_IsObject(current_element)){
            associations[i] = (char*)malloc((strlen(current_element->string)+1)*sizeof(char));
            associations[i] = current_element->string;
            i++;
        }
    }
    return associations;
}

void afficher_entite(s_entite* entite){
    int i = 0;
    printf("\n\nENTITE: %s\n", entite->nom);
    printf("ATTRIBUTS: ");
    for(i = 0; i < entite->n_attributs; i++)
    {
        printf("%s, ", entite->attributs[i]);
    }
  
}

void afficher_association(s_association* association){
    int i = 0;
    printf("\n\nASSOCIATION: %s\n", association->nom);
    printf("ATTRIBUTS: ");
    for(i = 0; i < association->n_attributs; i++)
    {
        printf("%s, ", association->attributs[i]);
    }
    printf("\n");
}

s_entite* creer_entite(s_entite* e, char* nom, char** attributs, char** associations, int n_attributs, int n_associations){
    int i = 0;
    e = malloc(sizeof(*e) + sizeof(char)*strlen(nom) + n_attributs*sizeof(char*) + n_associations*sizeof(char*));
    e->nom = nom;
    e->attributs = malloc(n_attributs * sizeof(char*));
    for(i = 0; i < n_attributs; i++)
    {
        // e->attributs[i] = malloc(sizeof(char) * (strlen(attributs[i]) + 1));
        e->attributs[i] = attributs[i];
    }
    e->associations = malloc(n_associations * sizeof(char*));
    for(i = 0; i < n_associations; i++)
    {
        // e->associations[i] = malloc(sizeof(char) * (strlen(associations[i]) + 1));
        e->associations[i] = associations[i];
    }

    e->n_attributs = n_attributs;
    e->n_associations = n_associations;
    
    return e;
}

s_association* creer_association(s_association* a, char* nom, char** attributs, int n_attributs){
    int i = 0;
    a = malloc(sizeof(*a) + sizeof(char)*strlen(nom) + n_attributs*sizeof(char*));
    a->nom = nom;
    a->attributs = malloc(n_attributs*sizeof(char*));
    for(i = 0; i < n_attributs; i++)
    {
        a->attributs[i] = attributs[i];
    }
    a->n_attributs = n_attributs;
}

void get_nombre_entites_associations(cJSON* json, int* nb_entites, int* nb_associations){
    if(cJSON_IsArray(json)){
        if(json->string)
            *nb_entites = *nb_entites + 1;
        if(json->child)
            get_nombre_entites_associations(json->child, nb_entites, nb_associations);
    }

    if(cJSON_IsString(json)){
        if(json->next)
            get_nombre_entites_associations(json->next, nb_entites, nb_associations);
    }

    if(cJSON_IsObject(json)){
        if(json->string)
            *nb_associations = *nb_associations + 1;
        if(json->child)
            get_nombre_entites_associations(json->child, nb_entites, nb_associations);
    }
}



int Jtest(svg* psvg,char *fileName)
{

    /*Tableau pour stocker les entites*/
    s_entite** tab_entites = NULL;
    /*Tableau pour stocker les associations*/
    s_association** tab_associations = NULL;
    int nb_entites = 0;
    int nb_associations = 0;
    char* json_data;
    json_data = chaine_json(fileName);
    cJSON* json = NULL;
    json = cJSON_Parse(json_data);
    get_nombre_entites_associations(json, &nb_entites, &nb_associations);
    tab_entites = malloc(nb_entites*sizeof(s_entite*));
    tab_associations = malloc(nb_associations*sizeof(s_association*));
    //printf("%d, %d\n", nb_entites, nb_associations);
    test(json, tab_entites, tab_associations);
    
    for(int i = 0; i < nb_entites; i++)
    {
        afficher_entite(tab_entites[i]);
       
        svg_rectangle(psvg, 190, 100, px, py, "#00FF00", "#008000", 4, 4, 4);
        
        svg_rectangle(psvg, 190, 100, px, py+34, "#00FF00", "#008000", 4, 4, 4);
                       
        svg_text(psvg, px+15, py+15, "sans-serif", 16, "#000000", "#000000", tab_entites[i]->nom);
        py=py+300;
        
        svg_text(psvg, px+15, py-250, "sans-serif", 16, "#000000", "#000000",tab_entites[i]->attributs[i]);
   
        svg_text(psvg, px+15, py-230, "sans-serif", 16, "#000000", "#000000",tab_entites[i]->attributs[i+1]);
        svg_text(psvg, px+15, py-210, "sans-serif", 16, "#000000", "#000000",tab_entites[i]->attributs[i+2]);
        svg_text(psvg, px+15, py-190, "sans-serif", 16, "#000000", "#000000",tab_entites[i]->attributs[i+3]);
        svg_text(psvg, px+15, py-170, "sans-serif", 16, "#000000", "#000000",tab_entites[i]->attributs[i+4]);
       
        afficher_entite(tab_entites[i+1]);
        svg_rectangle(psvg, 190, 100, px, py, "#00FF00", "#008000", 4, 4, 4);
        
        svg_rectangle(psvg, 190, 100, px, py+34, "#00FF00", "#008000", 4, 4, 4);
                       
        svg_text(psvg, px+15, py+15, "sans-serif", 16, "#000000", "#000000", tab_entites[i+1]->nom);
        py=py+300;
        
        svg_text(psvg, px+15, py-250, "sans-serif", 16, "#000000", "#000000",tab_entites[i+1]->attributs[i]);
        
        svg_text(psvg, px+15, py-230, "sans-serif", 16, "#000000", "#000000",tab_entites[i+1]->attributs[i+1]);
        svg_text(psvg, px+15, py-210, "sans-serif", 16, "#000000", "#000000",tab_entites[i+1]->attributs[i+2]);
        svg_text(psvg, px+15, py-190, "sans-serif", 16, "#000000", "#000000",tab_entites[i+1]->attributs[i+3]);
        svg_text(psvg, px+15, py-170, "sans-serif", 16, "#000000", "#000000",tab_entites[i+1]->attributs[i+4]);
             
    }
    for(int i = 0; i < nb_associations; i++)
    {
        afficher_association(tab_associations[i]);
        
        svg_ellipse(psvg, 380, 260, 75, 30, "#FFFFFF", "#800000", 4);
                         svg_text(psvg, px+15, py-390, "sans-serif", 16, "#000000", "#000000",tab_associations[i]->nom);
        svg_line(psvg, "#800000", 2, 450, 265, 303, 265);
        svg_line(psvg, "#000000", 2, 350, 230, 350, 185);
        svg_line(psvg, "#000000", 2, 350, 350, 350, 288);
        svg_text(psvg, px+50, py-370, "sans-serif", 16, "#000000", "#000000",tab_associations[i]->attributs[i]);
    
        }
    
    return 0;
}
