#include "utils.h"

void kh_set_destroy(khash_t(set) *h){

    khint_t k;
    if (h == 0) return;
    for (k = 0; k < kh_end(h); ++k) {
        if (kh_exist(h, k)) {
           free((char*)kh_key(h, k));
        }
    }
    kh_destroy(set, h);
}
