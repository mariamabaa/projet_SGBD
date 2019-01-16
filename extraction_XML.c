#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include "extraction_XML.h"

struct node *head = NULL;
int pxx=300 , pyy=50;

// declaration de la fonction traverse_dom_trees qui permet de parcourir les noeuds et ensuite afficher leur valeur
void traverse_dom_trees(svg* psvg,xmlNode * a_node)
{
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
               char *pol, *dev, *stat, *srcz, *dstz;
                if(strcmp((const char *)cur_node->name,(const char *)"nomEntite") == 0){
                 xmlChar *a = xmlNodeGetContent(cur_node);
                        printf("Nom entite: %s\n", a);
                    
                       svg_rectangle(psvg, 180, 100, pxx, pyy, "#00FF00", "#000000", 4, 4, 4);
                       
                       svg_rectangle(psvg, 180, 100, pxx, pyy+34, "#00FF00", "#000000", 4, 4, 4);
                       
                       svg_text(psvg, pxx+15, pyy+15, "sans-serif", 16, "#000000", "#000000",a);
                       pyy=pyy+300;
                       
                        }
             else if(strcmp((const char *)cur_node->name,(const char *)"numero") == 0)  {
                    xmlChar *b = xmlNodeGetContent(cur_node);
                        printf("NUMERO : %s\n", b);
                     
                       svg_text(psvg, pxx+15, pyy-250, "sans-serif", 16, "#000000", "#000000",b);
                   
                        }
            else if(strcmp((const char *)cur_node->name,(const char *)"nom") == 0){
                    xmlChar *c = xmlNodeGetContent(cur_node);
                        printf("NOM : %s\n", c);
                       
                        svg_text(psvg, pxx+15, pyy-225, "sans-serif", 16, "#000000", "#000000",c);
                   
                        }
            else if(strcmp((const char *)cur_node->name,(const char *)"prenom") == 0){
                    xmlChar *d = xmlNodeGetContent(cur_node);
                        printf("PRENOM : %s\n", d);
                      
                        svg_text(psvg, pxx+15, pyy-200, "sans-serif", 16, "#000000", "#000000",d);
                  
                        }
                 
               else if(strcmp((const char *)cur_node->name,(const char *)"ville") == 0){
                        xmlChar *e = xmlNodeGetContent(cur_node);
                         printf("VILLE : %s\n", e);
                         svg_text(psvg, pxx+15, pyy-175, "sans-serif", 16, "#000000", "#000000",e);
                        
                        }
           	else if(strcmp((const char *)cur_node->name,(const char *)"telephone") == 0){
                        xmlChar *f = xmlNodeGetContent(cur_node);
                         printf("TELEPHONE : %s\n", f);
                      svg_text(psvg, pxx+15, pyy-150, "sans-serif", 16, "#000000", "#000000",f);
                        
                        }
                else if(strcmp((const char *)cur_node->name,(const char *)"nomAssos") == 0){
                        xmlChar *g = xmlNodeGetContent(cur_node);
                         printf("ASSOCIATION : %s\n", g);
                         svg_ellipse(psvg, 380, 260, 75, 30, "#FFFFFF", "#800000", 4);
                         svg_text(psvg, pxx+15, pyy-390, "sans-serif", 16, "#000000", "#000000",g);
                         svg_line(psvg, "#800000", 2, 450, 265, 303, 265);
                         svg_line(psvg, "#000000", 2, 350, 230, 350, 180);
                         svg_line(psvg, "#000000", 2, 350, 350, 350, 288);
                 
                        }
               else if(strcmp((const char *)cur_node->name,(const char *)"date") == 0){
                        xmlChar *h = xmlNodeGetContent(cur_node);
                         printf("DATE : %s\n", h);
                         svg_text(psvg, pxx+26, pyy-370, "sans-serif", 16, "#000000", "#000000",h);
                         
                        }


        traverse_dom_trees(psvg,cur_node->children);
    }
}
/* déclaration de la fonction XXtest qui permet d'afficher les entités, attributs et associations du fichier fourni en paramètre*/
	
int XXtest(svg* psvg,char *fileName)
{
    xmlDocPtr doc;
    xmlNode *roo_element = NULL;

//vérification de la validité du document contenant le code XML
    
    doc = xmlReadFile(fileName, NULL, XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING | XML_PARSE_NONET);
    if (doc == NULL)
    {
        fprintf(stderr, "Document not parsed successfully.\n");
        return 0;
    } 

    roo_element = xmlDocGetRootElement(doc);
    
//On vérifie si le document contenant le code XML passé en paramètre est vide

    if (roo_element == NULL)
 {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return 0;
    }
	
    printf("Root Node is %s\n", roo_element->name);
    traverse_dom_trees(psvg,roo_element);

    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
  
    return 0;
}
