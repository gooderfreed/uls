#include "../inc/libmx.h"

void mx_printerr_char(const char *s) {
    write(2, s, 1);
}

