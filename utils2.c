/*
** EPITECH PROJECT, 2022
** utils2.c
** File description:
** utils2
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int initialize_str(char *str, int const size)
{
    int i = 0;
    while (i < size) {
        str[i] = '\0';
        ++i;
    }
}

int get_nb_from_file (char const * filepath)
{
    int fd = 0;
    char *temp = malloc(2 * sizeof(char));
    initialize_str(temp, 2);
    int result = 0;
    fd = open (filepath, O_RDONLY);
    if (fd == -1)
        return -2;
    int return_value = 0;
    while (temp && temp[0] != '\n') {
        return_value = read(fd, temp, 1);
        if (return_value <= 0)
            return result;
        if (temp[0] <= '9' && temp[0] >= '0')
            result = result * 10 + (temp[0] - '0');
        if (temp[0] != '\n' && (temp[0] > '9' || temp[0] < '0'))
            return -1;
    }
    close (fd);
    free(temp);
    return result;
}

int is_dot_in_lign (char * lign)
{
    int x = -1;
    while (lign[++x]) {
        if (lign[x] == '.') {
            lign[x] = 'x';
            return 1;
        }
    }
    return 0;
}

int is_buffer_valid (char * buffer, int size)
{
    int i = 0;
    int nb_lign = 0;
    while (buffer[i] != '\n')
        i++;
    while (buffer[++i]) {
        if (buffer[i] != '.' && buffer[i] != 'o' && buffer[i] != '\n')
            return 84;
        if (buffer[i] == '\n')
            nb_lign++;
    }
    if (nb_lign != size) return 84;
    return 0;
}
