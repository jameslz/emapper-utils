#include "utils.h"

int eggnog_main(int argc, char *argv[]){
    
    char *catalog = "COG";
    int c;
    while ((c = getopt(argc, argv, "c:")) >= 0) {
        if (c == 'c') catalog = optarg;
    }

    if ( optind == argc || argc != optind + 1) {
        
        fprintf(stderr, "\nUsage: emapper-utils eggnog [options] <emapper>\n\n");
        fprintf(stderr, "Options:\n");
        fprintf(stderr, "  -c  STR  catalog to report [COG, KOG, XOG], XOG for [KC]OG; default: [COG]\n\n");
        return 1;
    
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

        while( ks_getuntil( ks, '\n', &kt, 0) >=  0){
           
           if( kt.s[0] == '#' ) continue;           
           ks_tokaux_t aux;
           char *p;           
           for (p = kstrtok(kt.s, "\t", &aux), k = 0; p; p = kstrtok(0, 0, &aux), ++k){
               if(k == 0){
                    kt.s[aux.p -p] = '\0';
               }else if(k == 18){
                   kv.l = 0;
                   p[aux.p - p] = '\0';
                   kputsn(p, aux.p -p , &kv);
                   break;               
               }
           }

           fields    = ksplit(&kv, ',' , &n);
           for (i = 0; i < n; ++i){
               (kv.s + fields[i])[7] =  '\0';
               km.l = 0;
               ksprintf(&km, "%s\t%s", kt.s, kv.s + fields[i]);
               t = kh_put(set, h,  km.s, &ret);
               
               if(ret == 0){
                  continue;
               }else if(ret == 1){
                  kh_key(h, t) = strdup(km.s);
                  if(catalog[0] != 'X'){
                     if( strncmp(kv.s + fields[i], catalog, 3) == 0) puts(km.s);
                  }else{   
                     if( strncmp(kv.s + fields[i], "COG", 3) == 0  || strncmp(kv.s + fields[i], "KOG", 3) == 0 ) puts(km.s);
                  }
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