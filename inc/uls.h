#ifndef ULS_H
#define ULS_H

#include "../libmx/inc/libmx.h"

#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

typedef struct list_ List;

typedef struct list_{
    char *data;
    List *next;
}              List;

// List
int mx_list_size_l(List *list);
void mx_sort_list_l(List **list);
List *mx_create_list(char *data);
void mx_clear_list_l(List **list);
void mx_reverse_list(List **list);
void mx_add_elem(List **list, char* data);
void mx_list_add(List **list, char* data);
bool mx_flag_in_list(List *list, char *flag);
void mx_sort_by_size(List **list, char *dir);

// Full print
char *mx_get_info(char *file);
int mx_get_total(List *files, char *dir);
int mx_get_max_size(List *files, char *dir);
int mx_get_max_links(List *files, char *dir);
char *mx_get_full_path(char *data, char *dir);
void mx_print_full_info(List *files, char *dir, char *flags);

// Part print
void mx_print_less_info(List *list, char* dir, char *flags);

// Simple print
void mx_simple_print(List *list, char* dir, char *flags);

// Pars and checks
bool mx_is_dir(char *path);
bool mx_check_flag(char *flag, char **flags);
void mx_parse(char **flags, List **files, List **dirs, int argc, char *argv[]);

// Dirs and Files
char* get_filename(char* path);
void mx_print_error(char *filename);
void mx_print_extra_dir(char *dir, char *flags);
void mx_print_all(List *files, List *dirs, char *flags);
void mx_print_files(List *files, char *flags, char *dir);
List *mx_get_files_from_dir(char* directory, char *flags);
void mx_print_dir(List *dirs, char *flags, bool only_dir);
void mx_sort_by_flag(List **list, char *flags, char *dir);

//Other
int mx_max_len_names(List *list);

#endif
