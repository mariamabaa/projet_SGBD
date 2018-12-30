#include <stdlib.h>
#include <stdio.h>
#include "JSON_checker.h"
#define ENTREE "test.json"
int main(int argc, char* argv[]) {
FILE *f_in;
int c;
 if (argc > 1)
    {
        f_in = fopen (argv[1], "r"); /* On ouvre le fichier dont le chemin est accessible via argv[1] */
    }
  if (f_in == NULL)
    {
      fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n",ENTREE);
      return(EXIT_FAILURE);
    }
  JSON_checker jc = new_JSON_checker(20);
  while ((c = fgetc(f_in)) != EOF)
    {
        if (c <= 0) {
            break;
        }
        if (!JSON_checker_char(jc, c)) {
            fprintf(stderr, "JSON_checker_char: syntax error\n");
            exit(1);     
        }
        else
        	printf("format valide\n");
        	exit(1);        
    }
  fclose(f_in);
  if (!JSON_checker_done(jc)) {
        fprintf(stderr, "JSON_checker_end: syntax error\n");
        exit(1);
    	}
    	else 
    		printf("format valide");
    		exit(1);
  return(EXIT_SUCCESS);
}
