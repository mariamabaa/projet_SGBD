#include <stdio.h>
  #include <libxml/parser.h>
  #include <libxml/tree.h>
 


 int main(int argc, char **argv)
 {
    xmlDoc *doc = NULL;
   

    if (argc != 2)  return(1);


    /*Analyse du fichier fourni en paramètre */
    if ((doc = xmlReadFile(argv[1], NULL, 0)) == NULL){
       printf("Document %s invalide\n", argv[1]);
       exit(-1);
       }
       else{
        printf("Document %s valide\n", argv[1]);
       exit(-1);
       }
       
    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
    return 0;
 }
