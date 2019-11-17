#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

# define MAX_LINES 1500
# define X_MAX 159
# define Y_MAX 47
# define WATER ' '
# define PLAYER 'P'
# define VISITOR 'V'
# define DRAGON 165 | A_ALTCHARSET
# define POI_COUNT 17

typedef struct s_poi
{
    int         x;
    int         y;
    char        *name;
}               t_poi;

t_poi g_poi_tab[POI_COUNT] = {
    {55, 4, "Haukkalampi"},
    {95, 22, "Haltia"},
    {101, 21, "Solvalla"},
    {61, 31, "Siikajärvi"},
    {49, 38, "Siikajärvi"},
    {164, 40, "Heinäslampi"},
    {90, 39, "Sahajärvi"},
    {45, 19, "Kolmoislampi"},
    {44, 36, "Hotelli Nuuksio"},
    {109, 2, "Ruuhijärvi"},
    {126, 8, "Orajärvi"},
    {109, 2, "Ruuhijärvi"},
    {145, 10, "Urja"},
    {106, 28, "Nuuksion Pitkäjärvi"},
    {85, 17, "Watch out! Dragon!"},
    {126, 42, "Nuuksion Pitkäjärvi"},
    {158, 39, "Pirttimäki"}
};

char    **read_map(char *filename);

int     get_distance(t_poi poi, int cx, int cy)
{
    int d;

    d = abs(cx - poi.x) + abs(cy - poi.y);
    return (d);
}

char *nearest_poi_name(int cx, int cy)
{
    int i;
    int n;
    char *name;

    n = INT32_MAX;
    i = 0;
    while (i < POI_COUNT)
    {
        int cd = get_distance(g_poi_tab[i], cx, cy);
        if (cd < n)
        {
            name = g_poi_tab[i].name;
            n = cd;
        }
        i++;
    }
    return (name);
}

const char *getfield( char *line, int num)
{
    const char *token;

    for (token = strtok(line, ";");
         token && *token;
         token = strtok(NULL, ";\n"))
    {
        if (!--num)
            return (token);
    }
    return (NULL);
}

void    draw_trees(WINDOW *win, int amount)
{
    char c;
    while (amount--)
    {
        srand(amount);
        int x = rand() % X_MAX;
        int y = rand() % Y_MAX;
        c = mvwinch(win, y, x);
        if (c != WATER && x != 0 && y != 0)
        {
            mvwdelch(win, y, x);
            mvwinsch(win, y, x, 'F');
        }
    }
}

int    move_player(WINDOW *win, int *px, int *py, int nx, int ny)
{
    char c;

    if (nx < 1 || nx > X_MAX || ny < 1 || ny > Y_MAX)
        return (0);
    c = mvwinch(win, ny, nx);
    if (c == WATER)
        return (0);
    *px = nx;
    *py = ny;
    return (1);
}

void    draw_map(WINDOW *win, char *map)
{
    int y;

    y = 0;
    while (y < Y_MAX - 1)
    {
        waddnstr(win, map, X_MAX + 1);
        map += X_MAX + 1;
        y++;
    }
}

void    draw_welcome(WINDOW *win, char *map)
{
    int y;

    y = 0;
    while (y < 32)
    {
        waddnstr(win, map, 106);
        map += 107;
        y++;
    }
}

void draw_info(WINDOW *win, int x, int y)
{
    char xs[10];
    char ys[10];
    char pname[50];
    bzero(pname, 50);
    sprintf(pname, "%-49s", nearest_poi_name(x, y));
    sprintf(xs, "x: %2d", x);
    sprintf(ys, "y: %2d", y);
    box(win, ACS_VLINE, ACS_HLINE);
    wmove(win, 1, 1);
    waddstr(win, pname);
    wmove(win, 2,1);
    waddstr(win, xs);
    wmove(win, 2,10);
    waddstr(win, ys);
    wrefresh(win);
}

int     main(int argc, char **argv)
{
    int dragonx;
    int dragony;

    int px;
    int py;
    int exit = 0;
    char *map;
    char *welcome;
    char c;
    int show_w = 1;
    map = (char*)read_map("nuuksio.map");
    if (!map)
        return (1);
    welcome = (char *)read_map("welcome");
    if (!welcome)
        return (1);
    initscr();

    WINDOW *win = newwin(Y_MAX + 1, X_MAX + 1, 0, 0);
    WINDOW *infowin = newwin(4, X_MAX + 1, Y_MAX + 1, 0);
    WINDOW *wel_win = newwin(32, 106, 10, 26);
    px = 39;
    py = 39;

    dragonx = 85;
    dragony = 17;

    while(!exit)
    {
        wmove(win, 1, 0);
        draw_map(win, map);
        box(win, ACS_VLINE, ACS_HLINE);
        draw_trees(win, 8000);
        draw_info(infowin, px, py);

        start_color();
	    init_pair(1, COLOR_RED, COLOR_BLACK);

	    attron(COLOR_PAIR(1));

        wmove(win, dragony, dragonx);
        mvwdelch(win, dragony, dragony);
        mvwinsch(win, dragony, dragonx, DRAGON);
    	attroff(COLOR_PAIR(1));

        mvwdelch(win, py, px);
        mvwinsch(win, py, px, PLAYER);
        wrefresh(win);

        if (show_w)
        {
            //wmove(wel_win, 30, 10);
            draw_welcome(wel_win, welcome);
            box(wel_win, ACS_VLINE, ACS_HLINE);
            wrefresh(wel_win);
            if (getchar())
                show_w = 0;
        }



        switch (getchar())
        {
            case 'q':
                exit = 1;
                break ;
            case 'w':
                if (move_player(win, &px, &py, px, py - 1))
                break ;
            case 's':
                if (move_player(win, &px, &py, px, py + 1))
                break ;
            case 'a':
                if (move_player(win, &px, &py, px - 1, py))
                break ;
            case 'd':
                if (move_player(win, &px, &py, px + 1, py))
                break;
            default:
                break;
        }
        // touchwin(win);
    }
    endwin();
    printf("x - %d\n", px);
    printf("y - %d\n", py);
    return (0);
}
