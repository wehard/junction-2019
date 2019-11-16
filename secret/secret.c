#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void delay(int number_of_seconds) 
{ 
	// Converting time into milli_seconds 
	int milli_seconds = 1000 * number_of_seconds; 
	// Stroing start time 
	clock_t start_time = clock(); 
	// looping till required time is not acheived 
	while (clock() < start_time + milli_seconds) 
		; 
} 
int		ft_strequ(const char *s1, const char *s2)
{
	int	i;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	else
		return (0);
}
int ft_strlen(char *str)
{
	int i;
	i = 0;
	while (str[i] != '\0')
	{
		++i;
	}
	return (i);
}
char	*ft_rotone_back(char *str)
{
	int i;
	int k;
	char *newstring;
	int len;
	i = 0;
	k = 0;
	len = ft_strlen(str);
	if(!(newstring = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] > 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - 1;
			newstring[k] = str[i];
			++i;
			++k;
		}
		else if (str[i] > 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] - 1;
			newstring[k] = str[i];
			++i;
			++k;
		}
		else if (str[i] > '0' && str[i] <= '9')
		{
			str[i] = str[i] - 1;
			newstring[k] = str[i];
			++i;
			++k;
		}
		else if (str[i] == 'a')
		{
			newstring[i] = 'z';
			++k;
			++i;
		}
		else if (str[i] == 'A')
		{
			newstring[i] = 'z';
			++k;
			++i;
		}
		else if (str[i] == '0')
		{
			newstring[k] = '9';
			++k;
			++i;
		}
		else
		{
			++i;
		}
	}
	newstring[i] = '\0';
	return (str);
}
int main()
{
	int i;
	char str1[50] = "esbhpotmbzfst";
	char str2[50];
	char srccd[60] = "Uijt jt uif tpvsef dpef: 121212121212";
	char *newstr1;
	char *newsrccd;
	newstr1 = ft_rotone_back(str1);
	newsrccd = ft_rotone_back(srccd);
	printf("Generating source code...\n");
	delay(1000);
	delay(1000);
	delay(1000);
	delay(1000);
	printf("Compiling source code...\n");
	delay(1000);
	delay(1000);
	delay(1000);
	printf("Souce code ready\n");
	delay(1000);
	printf("Initializing One-time access key\n");
	delay(1000);
	delay(1000);
	printf("Please wait.\n");
	delay(1000);
	i = 10;
	while (i > 0)
	{
		printf("Estimated time left: %d seconds\n", i - 1);
		delay(1000); 
		--i;
	}
	printf("Please insert your personal access key\n");
	scanf("%s", str2);
	if (ft_strequ(newstr1, str2) == 1)
	{
		printf("Source code ready\n");
		delay(1000);
		delay(1000);
		printf("\n$$========$$ TOP SECRET $$========$$\n\n");
		printf("%s\n", newsrccd);
		printf("\n$$========$$ TOP SECRET $$========$$\n");
		delay(1000);
		printf("\nOperation Successful\n");
		return (0);
	}
	else if (ft_strequ(newstr1, str2) == 0)
	{
		delay(1000);
		printf("\nUNAUTHORIZED ACCESS KEY DETECTED\n");
		delay(1000);
		printf("\nSELF DELETION SEQUENCE STARTED\n");
		delay(1000);
		i = 5;
		while (i > 0)
		{
			printf("Time left until self deletion: %d seconds\n", i - 1);
			delay(1000);
			--i;
		}
		printf("\e[1;1H\e[2J");
		printf("Incident reported to host.\n");
	}
	return (0);
}