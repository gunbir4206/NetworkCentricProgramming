#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* fp = fopen("10MB", "w+");
	int i;
	for(i = 0; i < 10485760; i++)
	{
		fwrite("abcdefgh",1,8,fp);
	}

	fclose(fp);
	return 0;
}
