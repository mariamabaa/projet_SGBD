/* 	Ce programme lit un simple fichier JSON 
	et produit un message d'erreur si le fichier 
	ne respecte pas le format JSON
	*/
#include <stdlib.h>
#include <stdio.h>
#include "JSON_checker.h"
int main(int argc, char* argv[]) {
FILE *f_in;
int c;
 if (argc > 1)
    {
        f_in = fopen (argv[1], "r"); /* On ouvre le fichier dont le chemin est accessible via argv[1] */
    }
  if (f_in == NULL)
    {
      fprintf(stderr, "\nErreur: Impossible de lire le fichier \n");
      return(EXIT_FAILURE);
    }
  JSON_checker jc = new_JSON_checker(20);
  while ((c = fgetc(f_in)) != EOF)
    {
        if (c <= 0) {
            break;
        }
        if (!JSON_checker_char(jc, c)) {
            fprintf(stderr, "Erreur: Erreur de syntax\n");
            exit(1);     
        }
        else
        	printf("Format du fichier valide\n");
        	exit(1);        
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
