#include "utils.h"

int definition_main(int argc, char *argv[]){
    
    if (  argc != 2 ) {
        
        fprintf(stderr, "\nUsage: emapper-utils definition <emapper>\n\n");
        return 1;
    
    }

    gzFile fp;
    fp = strcmp(argv[1], "-")? gzopen(argv[1], "r") : gzdopen(fileno(stdin), "r"); 
    if(fp){

        kstream_t *ks;
        ks = ks_init(fp);
        int k;
        kstring_t  kt  = {0, 0, 0};
        kstring_t  kv  = {0, 0, 0};
        
        printf("#gene\tdefinition\n");
        while( ks_getuntil( ks, '\n', &kt, 0) >=  0){
           
           if( kt.s[0] == '#' ) continue;
           ks_tokaux_t aux;
           char *p;           
  
           kv.l = 0;
           
           for (p = kstrtok(kt.s, "\t", &aux), k = 0; p; p = kstrtok(0, 0, &aux), ++k){
               
               if(k == 0){
                    kt.s[aux.p -p] = '\0';
               }else if(k == 21){

                   p[aux.p - p] = '\0';
                   kputsn(p, aux.p -p , &kv);
                   break;
               
               }
           }

           if(kv.l == 0) continue;
           printf("%s\t%s\n", kt.s, kv.s);

        }

        free(kt.s);
        free(kv.s);
        ks_destroy(ks);
        gzclose(fp);
    
    }else{
        fprintf(stderr, "[ERR]: can't open file %s\n", argv[1]);
        exit(1);
    }

    return 0;
}
