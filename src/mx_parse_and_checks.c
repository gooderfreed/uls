#include "../inc/uls.h"

bool mx_is_dir(char *path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

bool mx_check_flag(char *flag, char **flags) {
    char allowed_options[11] = "1AaflopRrS";
    char *point = NULL;
    for (int i = 0; i < mx_strlen(flag); i++) {
        int size = mx_strlen(*flags);
        if ((int)mx_strchr(*flags, flag[i]) == 0 && flag[i] != '-') {
            if ((int)mx_strchr(allowed_options, flag[i]) == 0) {
                mx_printerr("uls: illegal option -- ");
                mx_printerr_char(&flag[i]);
                mx_printerr("\nusage: uls [-1AaflopRrS] [file ...]\n");
                return false;
            }
            if (flag[i] == 'A' && (int)(point = mx_strchr(*flags, 'a')) != 0)       *point = 'A';
            else if (flag[i] == 'a' && (int)(point = mx_strchr(*flags, 'A')) != 0)  *point = 'a';
            else {
                char *tmp = mx_strnew(size + 1);
                tmp = mx_strcat(tmp, *flags);
                tmp[size] = flag[i];
                free(*flags);
                *flags = tmp;
            }
        }
    }
    return true;
}

void mx_parse(char **flags, List **files, List **dirs, int argc, char *argv[]) {
    char **temp = (char **)malloc(sizeof(char *) * argc);
    struct stat buf;
    bool t = false;

    for (int i = 1; i < argc; i++) temp[i - 1] = argv[i];

    mx_bubble_sort(temp, argc - 1);

    for (int i = 0; i < argc - 1; i++) { 
        if (temp[i][0] == '-') {
            if (!mx_check_flag(temp[i], flags)) exit(0);
        }
        else if (stat(temp[i], &buf) == 0) {
            if ((S_ISREG(buf.st_mode))) mx_list_add(files, mx_strdup(temp[i]));
            else mx_list_add(dirs, mx_strdup(temp[i]));
        }
        else {
            mx_printerr("uls: ");
            mx_printerr(temp[i]);
            mx_printerr(": No such file or directory\n");
            t = true;
        }
    }
    // if (!t)
    //     if ((!*files && !*dirs)) mx_list_add(dirs, mx_strdup("."));
    if (!t && !(*files || *dirs)) mx_list_add(dirs, mx_strdup("."));
    free(temp);
}

