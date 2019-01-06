#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
// cette fonction (récursive) affiche le nom de tous les éléments du document XML
static void print_element_names(xmlNode *a_node)
{
    xmlNode *cur_node = NULL;
    for(cur_node = a_node; cur_node; cur_node = cur_node->next) 
    {
        if (
cur_node->type == XML_ELEMENT_NODE
) 
       {
            printf("node type: Element, name: %s\n", 
cur_node->name
);
        }        
print_element_names(cur_node->children);
    }
}
int main(int argc, char **argv)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    if (argc != 2)
        return(1);
    doc = xmlReadFile(argv[1], NULL, 0);
    if (doc == NULL)     { printf("Parse erreur ! (%s)\n", argv[1]);
return 1;
}
    /* Get the root element node */
root_element = xmlDocGetRootElement(doc);
print_element_names(root_element);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}

