#include "../inc/uls.h"

// #include <stdio.h>

void mx_sort_by_flag(List **list, char *flags, char *dir) {
    if (mx_strchr(flags, 'f') != 0) return;
    if (mx_strchr(flags, 'S') != 0) mx_sort_by_size(list, dir);
    else mx_sort_list_l(list);
    if (mx_strchr(flags, 'r') != 0) mx_reverse_list(list);
}

List *mx_get_files_from_dir(char *directory, char *flags) {
    struct dirent *dent;
    DIR *dir = opendir(directory);
    List *files = NULL;

    while ((dent = readdir(dir)) != NULL)
        if (mx_strchr(flags, 'a') != 0 || mx_strchr(flags, 'f') != 0) mx_list_add(&files, mx_strdup(dent->d_name));
        else if (mx_strchr(flags, 'A') != 0) {
            if (mx_strlen(dent->d_name) > 1) {
                if (dent->d_name[1] != '.') {
                    mx_list_add(&files, mx_strdup(dent->d_name));
                }
            }
        }
        else if (dent->d_name[0] != '.')
            mx_list_add(&files, mx_strdup(dent->d_name));
    
    mx_sort_by_flag(&files, flags, directory);
    closedir(dir);
    return files;
}

void mx_print_files(List *files, char *flags, char *dir) {
    if (!files) return; 
    if (mx_strchr(flags, 'l') != 0 || mx_strchr(flags, 'o') != 0) mx_print_full_info(files, dir, flags);
    else if (mx_strchr(flags, '1') != 0) mx_simple_print(files, dir, flags);
    else mx_print_less_info(files, dir, flags);
}

void mx_print_extra_dir(char *dir, char *flags) {
    List *x_data = mx_get_files_from_dir(dir, flags);
    List *x_dirs = NULL;
    List *temp = x_data;
    struct stat buf;
    char *f_path = NULL;

    while (temp) {
        f_path = mx_get_full_path(temp->data, dir);
        if (stat(f_path, &buf) == 0 && (S_ISDIR(buf.st_mode))) {
            if (mx_strcmp(temp->data, ".") != 0 && mx_strcmp(temp->data, "..") != 0)
                mx_list_add(&x_dirs, mx_get_full_path(temp->data, dir));
        }
        free(f_path);
        temp = temp->next;
    }
    if (x_data != NULL && mx_list_size_l(x_dirs) > 0) {
        mx_printchar('\n');
        mx_print_dir(x_dirs, flags, false);
    }
    mx_clear_list_l(&x_data);
    mx_clear_list_l(&x_dirs);
}

void mx_print_dir(List *dirs, char *flags, bool only_dir) {
    List *temp = dirs;
    List *temp_files = NULL;

    while (temp != NULL) {
        temp_files = mx_get_files_from_dir(temp->data, flags);

        if (!only_dir || !(temp->data == dirs->data) || temp->next) {
            mx_printstr(temp->data);
            mx_printstr(":\n");
        }
        mx_print_files(temp_files, flags, temp->data);
        if (mx_strchr(flags, 'R') != 0) mx_print_extra_dir(temp->data, flags);
        if (temp->next != NULL) mx_printchar('\n');
        mx_clear_list_l(&temp_files);
        temp_files = NULL;
        temp = temp->next;
    }
}

void mx_print_all(List *files, List *dirs, char *flags) {
    mx_print_files(files, flags, "./");
    if (dirs != NULL && files != NULL) mx_printchar('\n');
    if (files) mx_print_dir(dirs, flags ,false);
    else mx_print_dir(dirs, flags, true);
}

