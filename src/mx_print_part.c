#include "../inc/uls.h"

void mx_print_less_info(List *list, char *dir, char *flags) {
    List *temp = list;
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int max_len = mx_max_len_names(list);
    int win_col = w.ws_col;
    int cols = (win_col / max_len) == 0 ? 1: (win_col / max_len);
    int list_len = mx_list_size_l(list);
    bool is_p = true ? mx_strchr(flags, 'p') != 0 : false;
    int g = 0;
    if (max_len * cols > win_col && cols != 1) cols--;
    
    int rows = list_len /cols;
    if (rows == 0 || list_len % cols != 0) rows += 1;

    for (int y = 0; y < rows; y++) {
        for (int i = 0; i < cols; i++) {
            temp = list;

            for (int j = 0; temp != NULL && j < (i * rows) + y; j++) temp = temp->next;
            if (temp) {
                g = 0;
                mx_printstr(temp->data);
                if (is_p && mx_is_dir(mx_get_full_path(temp->data, dir))) {
                    mx_printchar('/');
                    g = 1;
                }
                for (int x = 0; x < max_len - mx_strlen(temp->data) - g; x++) mx_printstr(" ");
            }

        }
        mx_printchar('\n');
    }
}
