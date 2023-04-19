#include "../inc/uls.h"

//h f

int main(int argc, char *argv[]) {
    char *flags = mx_strnew(0);
    List *files = NULL;
    List *dirs  = NULL;

    mx_parse(&flags, &files, &dirs, argc, argv);
    mx_print_all(files, dirs, flags);

    mx_clear_list_l(&dirs);
    mx_clear_list_l(&files);
    free(flags);

    return 0;
}
