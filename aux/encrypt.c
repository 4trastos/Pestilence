#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int i = 0;
	char *str = "Pestilence version 1.0 (c)oded by davgalle";

	while(str[i] != '\0')
	{
		printf("0x%02x", (unsigned char)str[i] ^ 0x42);
		if (str[i] != '\0')
			printf(", ");
		i++;
	}
	printf("0x00;\n"); 
	return (0);
}
