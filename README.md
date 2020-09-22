# emapper-utils: utils for emapper annotation

### 0. compatibility

`emapper 2.0.1`

### 1. compile

```bash
cc -c -g -Wall -O2 -Wc++-compat  utils.c   -o  utils.o
cc -c -g -Wall -O2 -Wc++-compat  kstring.c   -o  kstring.o
cc -c -g -Wall -O2 -Wc++-compat  ann.c   -o  ann.o
cc -c -g -Wall -O2 -Wc++-compat  eggnog.c -o eggnog.o
cc -c -g -Wall -O2 -Wc++-compat  definition.c -o definition.o
cc -c -g -Wall -O2 -Wc++-compat  name.c -o name.o
cc -c -g -Wall -O2 -Wc++-compat  emapper-utils.c -o  emapper-utils.o
cc  -g -Wall -O2 -Wc++-compat  *.o  -o  emapper-utils -lz
```