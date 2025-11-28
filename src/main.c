#include <stdio.h>

void	print_usage(char *filename)
{
	printf("Usage:\n\t%s [...OPTIONS] <target_file> <file_to_embed>\n\nOPTIONS\n- nothing\n", filename);
}

int	main(int argc, char *argv[])
{
	if (argc < 3)
	{
		print_usage(argv[0]);
		return (1);
	}
	return (0);
}
