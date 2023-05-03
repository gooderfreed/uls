#include "../inc/uls.h"

char *mx_get_info(char *file) {
    char *info = mx_strnew(11);
    struct stat buf;
    lstat(file, &buf);

    info[0] = (buf.st_mode & S_IFDIR) ? 'd' : '-';
    info[1] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
    info[2] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
    info[3] = (buf.st_mode & S_IXUSR) ? 'x' : '-';
    info[4] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
    info[5] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
    info[6] = (buf.st_mode & S_IXGRP) ? 'x' : '-';
    info[7] = (buf.st_mode & S_IROTH) ? 'r' : '-';
    info[8] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
    info[9] = (buf.st_mode & S_IXOTH) ? 'x' : '-';
    info[10] = '\0';
    return info;
}

char *mx_get_full_path(char *data, char *dir) {
    char *tmp = mx_strnew(mx_strlen(data) + mx_strlen(dir) + 1);
    char *c = tmp;
    char *t = dir;

    while (*t != '\0') *c++ = *t++;
    if (*--t != '/') *c++ = '/';
    t = data;
    while (*t != '\0') *c++ = *t++;
    return tmp;
}

int mx_get_max_links(List *files, char *dir) {
    List *temp = files;
    struct stat buf;
    int max_links = 0;

    while (temp) {
        char *tmp = mx_get_full_path(temp->data, dir);
        lstat(tmp, &buf);
        if ((int)buf.st_nlink > max_links) max_links = buf.st_nlink;
        temp = temp->next;
        free(tmp);
    }

    return max_links;
}

int mx_get_max_size(List *files, char *dir) {
    List *temp = files;
    struct stat buf;
    int max_size = 0;

    while (temp) {
        char *tmp = mx_get_full_path(temp->data, dir);
        lstat(tmp, &buf);
        if (buf.st_size > max_size) max_size = buf.st_size;
        temp = temp->next;
        free(tmp);
    }

    return max_size;
}

int mx_get_total(List *files, char *dir) {
    struct stat buf;
    List *temp = files;
    int blocks_count = 0;

    while (temp) {
        char *tmp = mx_get_full_path(temp->data, dir);
        lstat(tmp, &buf);
        blocks_count += buf.st_blocks;
        temp = temp->next;
        free(tmp);
    }
    return blocks_count;
}

void mx_print_full_info(List *files, char *dir, char *flags) {
    struct stat buf;
    struct passwd *user_name;
    struct group *group_name;
    int max_links = mx_get_max_links(files, dir);
    int max_size = mx_get_max_size(files, dir);
    List *temp = files;
    bool is_p = true ? mx_strchr(flags, 'p') != 0 : false;

    mx_printstr("total ");
    mx_printint(mx_get_total(files, dir));
    mx_printchar('\n');
    char *t1 = NULL;
    char *t2 = NULL;

    while (temp) {
        char *tmp = mx_get_full_path(temp->data, dir);

        lstat(tmp, &buf);
        char *info = mx_get_info(tmp);
        user_name = getpwuid(buf.st_uid);
        group_name = getgrgid(buf.st_gid);
        char *str_time = ctime(&buf.st_mtime);

        mx_printstr(info);
        mx_printstr("  ");
        t1 = mx_itoa(max_links);
        t2 = mx_itoa((int)buf.st_nlink);
        for (int i = 0; i < mx_strlen(t1) - mx_strlen(t2); i++) mx_printchar(' ');
        free(t1);
        free(t2);
        mx_printint((int)buf.st_nlink);
        mx_printstr(" ");
        mx_printstr(user_name->pw_name);
        if (mx_strchr(flags, 'o') == 0) {
            mx_printstr("  ");
            mx_printstr(group_name->gr_name);
        }
        mx_printstr("  ");
        t1 = mx_itoa(max_size);
        t2 = mx_itoa((int)buf.st_size);
        for (int i = 0; i < mx_strlen(t1) - mx_strlen(t2); i++) mx_printchar(' ');
        free(t1);
        free(t2);
        mx_printint((int)buf.st_size);
        mx_printstr(" ");
        for (int t = 4; t < mx_strlen(str_time) - 15; t++) mx_printchar(str_time[t]);
        if (15811200 > (time(NULL) - buf.st_ctime))
            for (int t = 10; t < mx_strlen(str_time) - 9; t++) mx_printchar(str_time[t]);
        else {
            mx_printstr(" ");
            for (int t = 19; t < mx_strlen(str_time) - 1; t++) mx_printchar(str_time[t]);
        }
        mx_printstr(" ");
        mx_printstr(temp->data);
        if (is_p && mx_is_dir(mx_get_full_path(temp->data, dir))) mx_printchar('/');
        mx_printstr("\n");
        
        free(info);
        free(tmp);

        temp = temp->next;
    }
}
