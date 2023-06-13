/*
** EPITECH PROJECT, 2022
** utils.c
** File description:
** utils
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int get_nb_from_file (char const * filepath);

int my_getnbr (char const *str)
{
    int i = 0;
    int n = 0;
    long long int nbr = 0;
    while (str[i] > '9' || str[i] < '0' && str[i])
        if (str[i++] == '-') n += 1;
    while (str[i] <= '9' && str[i] >= '0' && str[i]) {
        if (((nbr >= 214748364 && str[i] > '8') || nbr >= 214748365)
            || (n % 2 == 0 && nbr >= 214748364 && str[i] > '7'))
            return 0;
        nbr = nbr * 10 + str[i] - '0';
        i++;
    }
    if (n % 2 != 0) nbr = -nbr;
    return nbr;
}

int my_strlen (char const * str)
{
    int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

char * fs_cat_x_bytes (char const * filepath , int x, int nb)
{
    int fd = open (filepath, O_RDONLY);
    int check = 0;
    char *temp = malloc(2 * sizeof(char));
    while (check < nb) {
        read(fd, temp, 1);
        if (temp[0] == '\n')
            check++;
    }
    char * buffer = malloc(sizeof(char) * (x + 1));
    int return_value = read(fd, buffer, x);
    close (fd);
    return buffer;
}

int need_a_map (int ac, char **av)
{
    int i = -1;
    if (ac == 2) return 0;
    if (!av[2][0]) return 0;
    while (av[2][++i])
        if (av[2][i] != '.' && av[2][i] != 'o')
            return 0;
    return 1;
}

int is_file_valid (int ac, char ** av)
{
    int size = 0;
    if (ac != 2 || (size = get_nb_from_file(av[1])) < 1)
        return 0;
    return size;
}
