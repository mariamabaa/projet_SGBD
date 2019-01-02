#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
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
			break;
		case 'o':
			cpt_o++;
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
