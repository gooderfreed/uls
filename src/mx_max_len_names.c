#include "../inc/uls.h"

int mx_max_len_names(List *list) {
    int max = 0;
    List *temp = list;

    while (temp) {
        if (mx_strlen(temp->data) > max) max = mx_strlen(temp->data);
        temp = temp->next;
    }

    if (max % 8 == 0) max += 8;
    else max = 8 - (max % 8) + max;
    return max;
}

