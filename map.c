#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

char	*read_map(char *filename)
{
	//char *data;
	char buffer[12000];
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	printf("%d\n", fd);
	//char **res = (char**)malloc(sizeof(char*) * 67);
    // if (!res)
    // {
    //     printf("Malloc fail\n");
    //     getch();
    //     return (0);
    // }
	int bytes = read(fd, buffer, 12000);
    //printf("%d\n", bytes);
	buffer[bytes] = '\0';
	// int i = -1;
	
	// while (buffer[++i])
	// 	if (buffer[i] == '@')
	// 		buffer[i] = '.';
	//int i;
	//i = 0;
	// data = strtok(buffer, "\n");
	// while (data)
	// {
	// 	res[i] = data;
	// 	data = strtok(NULL, "\n");
	// 	i++;
	// }
	//res[i] = NULL;
    close(fd);
	return ((char*)strdup(buffer));
}