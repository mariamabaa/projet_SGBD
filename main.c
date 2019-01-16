#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "JSON_checker.h"
#include "extraction_XML.h"

#define TRUE 1
#define FALSE 0

int main (int argc, char *argv[])
{
	/*Les options de commande*/
	int opt;
	/*compteur des paramètres de commande*/
	int cpt_i, cpt_h, cpt_f, cpt_o, cpt_t;
	cpt_f = cpt_h = cpt_i = cpt_o = cpt_t = 0;
	
	char * format;
	char * opto;
	char * optf;
	while ((opt = getopt(argc, argv, "i:h:f:o:t")) != -1)
	{
		switch (opt)
		{
		case 'i':
			cpt_i++;
			format = optarg;
			break;
		case 't':
			cpt_t++;
			break;
		case 'h':
			cpt_h++;
			break;
		case 'f':
			cpt_f++;
			optf = optarg;
			break;
		case 'o':
			cpt_o++;
			opto = optarg;
		break;
		}	
	}
	if (cpt_i == 1)
	{
		if (strcmp(format, "json")==0 || strcmp(format, "xml")==0)
		{
			if (cpt_h==1 ^ cpt_f==1) 
			{
				if (cpt_o ==1)
				{	
				
					if (cpt_t == 1)
					{
						printf("traces\n");
						printf("...\n");
					}

					if (strcmp(format, "xml")==0 ){
					/* Génération SVG du fichier XML*/
					 xmlDoc *doc = NULL;
					/*Analyse du fichier fourni en paramètre */
					    if ((doc = xmlReadFile(optf, NULL, 0)) == NULL){
					       printf("Document %s invalide\n", optf);
					       exit(-1);
					       }
					       else{
						printf("Document %s valide\n", optf);
					        svg* psvg;
						    psvg = svg_create(600, 600);

						    if(psvg == NULL)
						    {
							puts("psvg is NULL");
						    }
						    else
						    {
							 XXtest(psvg,optf);
						       
						    }
						    
						    
						     svg_save(psvg, opto);
							svg_free(psvg);
						    return EXIT_SUCCESS;
					       }
					       
					    xmlFreeDoc(doc);       // free document
					    xmlCleanupParser();    // Free globals
					    return 0;
					}
					/*génération SVG du fichier JSON fourni en paramètre*/
					else {
						FILE *f_in;
						int c;
						 if (argc > 1)
						    {
							f_in = fopen (optf, "r"); 
					/* On ouvre le fichier dont le chemin est accessible via optf*/
						    }
						  if (f_in == NULL)
						    {
						      fprintf(stderr, "\nErreur: Impossible de lire le fichier \n");
						      return(EXIT_FAILURE);
						    }
						  JSON_checker jc = new_JSON_checker(20);
						  while ((c = fgetc(f_in)) != EOF)
						    {
							if (c <= 0)
							{
							    break;
							}
							if (!JSON_checker_char(jc, c)) {
							    fprintf(stderr, "Erreur: Erreur de syntax\n");
							    exit(1);     
							}
							else{
							
								printf("Format du fichier valide\n");
							    svg* psvg;
							    psvg = svg_create(600, 600);

							    if(psvg == NULL)
							    {
								puts("psvg is NULL");
							    }
							    else
							    {
								 Jtest(psvg,optf);
							       
							    }
							    
							    
							     svg_save(psvg, opto);
							     svg_free(psvg);				    
							    return EXIT_SUCCESS;
							}     
						    }
						  fclose(f_in);
						  if (!JSON_checker_done(jc)) {
							fprintf(stderr, "Erreur: Erreur de syntax\n");
							exit(1);
						    	}
						    	else 
						    		printf("Format du fichier valide\n");
						    		exit(1);
						  return(EXIT_SUCCESS);
					}
				}
				else 
				{
					printf("Entrez un argument pour la sortie\n");
					exit(EXIT_FAILURE);
				}
			}
			else 
			{
				printf("entrez un flux http [-h] ou un fichier [-f]\n");
				exit (EXIT_FAILURE);
			}
		}
		else
		{
			printf("Entrez un format de fichier en entrée correct [-i] (xml ou json) \n");
			exit(EXIT_FAILURE);
			}
		}
		else
		{
			printf("Précisez le format de données en entrée\n");
			exit(EXIT_FAILURE);
		}
		return 0;
	
}
