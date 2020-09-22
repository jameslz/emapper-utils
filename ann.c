#include "utils.h"

int ann_main(int argc, char *argv[]){
    
    char *db = "KEGG";
    int c;
    while ((c = getopt(argc, argv, "d:v")) >= 0) {
    
        if (c == 'd') db = optarg;

    }

    if ( optind == argc || argc != optind + 1) {
        
        fprintf(stderr, "\nUsage: emapper-utils ann [options] <emapper>\n");
        fprintf(stderr, "Options:\n");
        fprintf(stderr, "   -d STR   parse annotation, [KEGG, BiGG, GO], default: [KEGG]\n\n");
        return 1;
    
    }

    int target = 6;

    if(strncmp(db, "KEGG", 4)       == 0){
      target = 8;
    }else if(strncmp(db, "GO", 5)   == 0){
      target = 6;
    }else if(strncmp(db, "BiGG", 4) == 0){
      target = 16;
    }

    if(db[0] != 'K' && target == 8){
       fprintf(stderr, "[ERR]: maybe specify the incorrect db: [%s], using [KEGG, BiGG, GO]. \n", db);
       return -1;
    }


    khash_t(set) *h;
    h = kh_init(set);
    khint_t t;

    gzFile fp;
    fp = strcmp(argv[optind], "-")? gzopen(argv[optind], "r") : gzdopen(fileno(stdin), "r"); 

    if(fp){

        kstream_t *ks;
        ks = ks_init(fp);
        int i, *fields, n, k, ret;
        
        kstring_t  kt  = {0, 0, 0};
        kstring_t  kv  = {0, 0, 0};
        kstring_t  km  = {0, 0, 0};

        int r = (db[0] == 'K') ? 3 : 0;

        while( ks_getuntil( ks, '\n', &kt, 0) >=  0){
           
           if( kt.s[0] == '#' ) continue;           
           ks_tokaux_t aux;
           char *p;           
           for (p = kstrtok(kt.s, "\t", &aux), k = 0; p; p = kstrtok(0, 0, &aux), ++k){
               
               if(k == 0){
                    kt.s[aux.p -p] = '\0';
               }else if(k == target){

                   kv.l = 0;
                   p[aux.p - p] = '\0';
                   kputsn(p, aux.p -p , &kv);
                   break;
               
               }
           }

           fields    = ksplit(&kv, ',' , &n);
           for (i = 0; i < n; ++i){
               
               km.l = 0;
               ksprintf(&km, "%s\t%s", kt.s, kv.s + fields[i] + r);
               t = kh_put(set, h,  km.s, &ret);
               if(ret == 0){
                  continue;
               }else if(ret == 1){
                  kh_key(h, t) = strdup(km.s);
                  puts(km.s);
               }
           
           }

        }

        free(kv.s);
        free(kt.s);
        free(km.s);

        ks_destroy(ks);
        gzclose(fp);
    
    }else{
        fprintf(stderr, "[ERR]: can't open file %s\n", argv[optind]);
        exit(1);
    }
    
    kh_set_destroy( h );
    return 0;
}
