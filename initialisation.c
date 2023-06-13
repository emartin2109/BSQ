/*
** EPITECH PROJECT, 2022
** initialisation.c
** File description:
** initialisation
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int my_strlen (char const * str);
int bruteforce (char **board, int size);
int my_getnbr (char const *str);
int initialize_str_array (char **str, int const size);
int initialize_str(char *str, int const size);
int is_file_valid (int ac, char ** av);
int is_buffer_valid (char * buffer, int size);

int get_size_of_lign (char * buffer, int nb_lign)
{
    int i = 0;
    int j = 0;
    int return_value = 0;
    int temp_value = 0;
    while (buffer[i] != '\n' && buffer[i])
        i++;
    i++;
    while (j < nb_lign) {
        while (buffer[i] != '\n' && buffer[i]) {
            i++;
            temp_value++;
        }
        i++;
        if (temp_value > return_value)
            return_value = temp_value;
        j++;
        temp_value = 0;
    }
    return return_value;
}

int get_board (char ** board, int nb_lign, char * buffer)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int nb_col = get_size_of_lign(buffer, nb_lign);
    if (is_buffer_valid(buffer, nb_lign) == 84) return 84;
    while (buffer[i] != '\n')
        i++;
    i++;
    while (buffer[i]) {
        board[j] = malloc((nb_col + 2) * sizeof(char));
        initialize_str(board[j], nb_col + 2);
        while (buffer[i] != '\n' && buffer[i])
            board[j][k++] = buffer[i++];
        if (my_strlen(board[j]) != nb_col)
            return 84;
        board[j++][k] = buffer[i++];
        k = 0;
    }
    return nb_col;
}

int generate_board(char ** board, int size, char *patern)
{
    int i = -1;
    int lign = 0;
    int col = -1;
    board[lign] = malloc((size + 2) * sizeof(char));
    initialize_str(board[lign], size + 2);
    while (++i <= size * size) {
        board[lign][++col] = patern[i % my_strlen(patern)];
        if (col >= size - 1 && lign < size - 1) {
            board[lign][++col] = '\0';
            col = -1;
            lign++;
            board[lign] = malloc((size + 2) * sizeof(char));
            initialize_str(board[lign], size + 2);
        }
    }
}

int initialisation_with_file (int ac, char **av)
{
    int size = 0;
    int i = -1;
    int col_nb = 0;
    struct stat s;
    if (!(size = is_file_valid(ac, av))) return 84;
    stat (av[1], &s);
    int fd = open (av[1], O_RDONLY);
    char * buffer = malloc ((s.st_size + 1) * sizeof (char));
    char ** board = malloc((size + 3) * sizeof (char *));
    board[size] = NULL;
    read(fd, buffer, s.st_size);
    buffer[s.st_size] = '\0';
    if ((col_nb = get_board(board, size, buffer)) == 84) return 84;
    bruteforce (board,  size);
    while (board[++i]) {
        write(1, board[i], col_nb + 1);
        free(board[i]);
    }
    free(board);
    free(buffer);
}

int initialisation_without_file (int ac, char **av)
{
    int size = 0;
    int i = 0;
    char ** board = NULL;
    if (ac != 3)
        return 84;
    if ((size = my_getnbr(av[1])) < 1 || size > 10000)
        return 84;
    board = malloc(sizeof(char *) * (size + 1));
    board[size] = NULL;
    generate_board(board, size, av[2]);
    bruteforce (board, size);
    while (i < size) {
        write(1, board[i], size);
        write(1, "\n", 1);
        free(board[i++]);
    }
    free(board);
    return 0;
}
