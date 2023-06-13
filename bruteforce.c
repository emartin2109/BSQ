/*
** EPITECH PROJECT, 2022
** bruteforce.c
** File description:
** bruteforce
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int is_dot_in_lign (char * lign);

struct best_pos {
    int x;
    int y;
    int score;
};

int can_trace_a_square(int size, int x, int y, char **board)
{
    int i = 0;
    int j = 0;
    while (i <= size) {
        if (board[y + j][x + i] != '.')
            return 0;
        i++;
    }
    while (j <= size) {
        if (board[y + j][x + i] != '.' || !board[y + j + 1])
            return 0;
        j++;
    }
    while (i >= 0) {
        if (board[y + j][x + i] != '.')
            return 0;
        i--;
    }
    return 1;
}

int trace_a_square(int x, int y, int size, char **board)
{
    int i = 0;
    int j = 0;
    while (i <= size)
        board[y + j][x + i++] = 'x';
    while (j <= size && board[y + j + 1])
        board[y + j++][x + i] = 'x';
    while (i >= 1)
        board[y + j][x + i--] = 'x';
    while (j >= 1)
        board[y + j--][x + i] = 'x';
    return 1;
}

struct best_pos try_this_pos (int x, int y, char **board, int size)
{
    int size_max = 0;
    struct best_pos temp_square;
    while (can_trace_a_square(size_max, x, y, board))
        size_max++;
    temp_square.x = x;
    temp_square.y = y;
    temp_square.score = size_max + 1;
    return temp_square;
}

int fill_map_with_one_or_zero (char **board)
{
    int y = -1;
    while (board[++y]) {
        if (is_dot_in_lign(board[y]))
            return 0;
    }
    return 0;
}

int bruteforce (char **board, int size)
{
    int i = 0;
    int y = 0;
    struct best_pos best_square = {0};
    struct best_pos temp_square = {0};
    while (y < size) {
        temp_square = try_this_pos(i, y, board, size);
        if (temp_square.score > best_square.score && board[y][i] == '.')
            best_square = temp_square;
        if (!board[y][++i]) {
            i = 0;
            y++;
        }
    }
    i = -1;
    if (best_square.score < 2)
        fill_map_with_one_or_zero(board);
    while (++i < best_square.score - 1)
        trace_a_square(best_square.x, best_square.y, i, board);
}
