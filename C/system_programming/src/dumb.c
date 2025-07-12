#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)

{
	int a = 7;
	int b = 12;
	int c = 15;
	int *p = &b;

	FILE *fp;

	if (0 ==(fp = fopen("stoopid", "w")))
	{
		printf("well, that didn\'t work!\n");
		return -1;
	}

	fprintf(fp, "%p\n", (void*)p);

	if (fclose(fp))
	{
		printf("oh well.");
		return -1;
	}
	sleep (30);
	printf("p points to: %d\n", *p);
	return 0;
}

