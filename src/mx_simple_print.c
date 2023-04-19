#include "../inc/uls.h"

void mx_simple_print(List *list, char *dir, char *flags) {
    List *temp = list;
    bool is_p = true ? mx_strchr(flags, 'p') != 0 : false;

    for (int i = 0; temp != NULL; i++) {
        mx_printstr(temp->data);
        if (is_p && mx_is_dir(mx_get_full_path(temp->data, dir))) mx_printchar('/');
        mx_printchar('\n');
        temp = temp->next;
    }
}

