/*****************************************************************************
  emapper-utils.c

  emapper-utils command line interface.  

  (c) 2018-2020 - LEI ZHANG
  Logic Informatics Co.,Ltd.
  zhanglei@logicinformatics.com
  
  Licenced under The MIT License.
******************************************************************************/

#include <stdio.h>
#include <string.h>

int ann_main(int argc, char *argv[]);
int eggnog_main(int argc, char *argv[]);
int definition_main(int argc, char *argv[]);
int name_main(int argc, char *argv[]);

static int usage(){
    
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage:   emapper-utils <command> <arguments>\n");
    fprintf(stderr, "Version: 0.0.1-dirty\n\n");

    fprintf(stderr, "Command:\n");
    fprintf(stderr, "         ann        kegg|gene ontology annotation\n");
    fprintf(stderr, "         eggnog     cog|kog annotation\n");
    fprintf(stderr, "         name       emapper preferred name\n");
    fprintf(stderr, "         definition emapper annotation\n");
    fprintf(stderr, "\n");

    fprintf(stderr, "\nLicenced:\n");
    fprintf(stderr, "(c) 2018-2020 - LEI ZHANG\n");
    fprintf(stderr, "Logic Informatics Co.,Ltd.\n");
    fprintf(stderr, "zhanglei@logicinformatics.com\n");
    fprintf(stderr, "\n");

    return 1;

}

int main(int argc, char *argv[]){

    if (argc < 2) return usage();
    
    if (strcmp(argv[1], "ann") == 0) ann_main(argc - 1, argv + 1);
    else if (strcmp(argv[1], "eggnog") == 0) eggnog_main(argc - 1, argv + 1);
    else if (strcmp(argv[1], "definition") == 0) definition_main(argc - 1, argv + 1);
    else if (strcmp(argv[1], "name") == 0) name_main(argc - 1, argv + 1);
    else {
        fprintf(stderr, "[main] unrecognized command '%s'. Abort!\n", argv[1]);
        return 1;
    }
    return 0;

}