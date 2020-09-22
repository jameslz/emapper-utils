#include <zlib.h>
#include <stdio.h>
#include <string.h>

#include "khash.h"
#include "kstring.h"

#include "kseq.h"
KSTREAM_INIT(gzFile, gzread, 16384)

KHASH_SET_INIT_STR(set)
void kh_set_destroy(khash_t(set) *h);