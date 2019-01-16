#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include "extraction_JSON.h"


//declaration de la strcuture node et ses varables 
struct node {
	char *nomEntite;
	char *numero;
	char *nom;
	char *prenom;
	char *ville;
	char *telephone;
	char *nomAssos;
	char *date;

	struct node *next;
};

void insert(char *a, char *b, char *c, char *d, char *e, char *f);
void traverse_dom_trees(svg* psvg,xmlNode * a_node);
int XXtest();
