#include "../inc/uls.h"

List *mx_create_list(char *data) {
    List *list = (List *)malloc(sizeof(List));
    list->next = NULL;
    list->data = data;
    return list;
}

void mx_add_elem(List **list, char* data) {
    List *temp = *list;
    while (temp->next != NULL) temp = temp->next;
    temp->next = mx_create_list(data);
}

void mx_list_add(List **list, char* data) {
    if (*list == NULL) *list = mx_create_list(data);
    else mx_add_elem(list, data);
}

int mx_list_size_l(List *list) {
    int size = 0;
    while (list) {
        size++;
        list = list->next;
    }
    return size;
}

void mx_sort_by_size(List **list, char *dir) {
    List *temp = *list;
    int size = mx_list_size_l(temp);
    char **words = (char**)malloc(sizeof(char *) * size);
    struct stat buf1;
    struct stat buf2;
    char *f_path_1 = NULL;
    char *f_path_2 = NULL;

    for (int i = 0; i < size; i++) {
        words[i] = temp->data;
        temp = temp->next;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            f_path_1 = mx_get_full_path(words[j], dir);
            f_path_2 = mx_get_full_path(words[j + 1], dir);
            lstat(f_path_1, &buf1);
            lstat(f_path_2, &buf2);
            if (((int)buf1.st_size) < ((int)buf2.st_size)) {
                char *temp_ = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp_;
            }
            free(f_path_1);
            free(f_path_2);
        }
        
    }

    temp = *list;
    for (int i = 0; i < size; i++) {
        temp->data = words[i];
        temp = temp->next;
    }
    
    free(words);
}

void mx_reverse_list(List **list) {
    List *temp = *list;
    int size = mx_list_size_l(temp);
    char **words = (char**)malloc(sizeof(char *) * size);

    for (int i = 0; i < size; i++) {
        words[i] = temp->data;
        temp = temp->next;
    }

    temp = *list;
    for (int i = size - 1; i >= 0; i--) {
        temp->data = words[i];
        temp = temp->next;
    }
    
    free(words);
}

void mx_sort_list_l(List **list) {
    List *temp = *list;
    int size = mx_list_size_l(temp);
    char **words = (char**)malloc(sizeof(char *) * size);

    for (int i = 0; i < size; i++) {
        words[i] = temp->data;
        temp = temp->next;
    }

    mx_bubble_sort(words, size);

    temp = *list;
    for (int i = 0; i < size; i++) {
        temp->data = words[i];
        temp = temp->next;
    }
    
    free(words);
}

bool mx_flag_in_list(List *list, char *flag) {
    List *temp = list;

    while (temp) {
        if (temp->data[1] == flag[0]) return true;
        temp = temp->next;
    }
    return false;
}

void mx_clear_list_l(List **list) {
    List *temp = *list;
    List *t = NULL;
    while (temp) {
        t = temp;
        temp = temp->next;
        if (t->data) free(t->data);
        free(t);
    }
}
