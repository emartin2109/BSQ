/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int need_a_map (int ac, char **av);
int initialisation_with_file (int ac, char **av);
int initialisation_without_file (int ac, char **av);

int main (int argc, char ** argv)
{
    int return_value = 0;
    if (argc < 2)
        return 84;
    if (need_a_map(argc, argv))
        return_value = initialisation_without_file (argc, argv);
    else
        return_value = initialisation_with_file (argc, argv);
    return return_value;
}
