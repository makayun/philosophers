#include <stdio.h>

typedef struct s_data
{
    int i;
    char c;
}               t_data;

typedef struct s_player{
    t_data data;
    int id;
}               t_player;


int main()
{
    t_data data;
    t_player player;

    data.c = 'a';
    data.i = 42;

    player.data = data;

    printf ("%d %c", player.data.i, player.data.c);

}