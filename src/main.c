#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>
#include "stegan.h"

void	print_usage(char *filename)
{
	printf("Usage:\n\t%s [...OPTIONS] <target_file> <file_to_embed>\n\nOPTIONS\n- nothing\n", filename);
}


image_type_t	get_image_type(char *path)
{
	int PNG_SIG[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

	int				i;
	unsigned char	b[8] = {0};
	FILE			*f;

	f = fopen(path, "rb");
	if (!f)
	{
		print_err("Cannot open file \"%s\"", path);
		return UNKNOWN;
	}
	fread(b, 1, 8, f);
	for (i = 0; i < 8; i++)
	{
		if (b[i] != PNG_SIG[i])
		{
			fclose(f);
			return UNKNOWN;
		}
	}
	fclose(f);
	return PNG;
}

steg_params_t	parse_params(int argc, char *argv[])
{
	steg_params_t	params;

	params.cover_name = argv[argc - 2];
	params.embed_name = argv[argc - 1];

	return (params);
}


void	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
}

int		ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

static void	ft_print_format(int fd, char c, va_list *args)
{
	if (c == '%')
		ft_putchar(fd, '%');
	else if (c == 's')
		ft_putstr(fd, va_arg(*args, char *));
}

int	print_err(const char *format, ...)
{
	va_list	args;
	int		i;

	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!format[i])
				return (0);
			ft_print_format(2, format[i], &args);
		}
		else
		{
			ft_putchar(2, format[i]);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc < 3)
	{
		print_usage(argv[0]);
		return (1);
	}

	steg_params_t params = parse_params(argc, argv);
	printf("Acces cov: %d\n", access(params.cover_name, F_OK));
	printf("Acces emb: %d\n", access(params.embed_name, F_OK));
	if (access(params.cover_name, F_OK) != 0)
	{
		print_err("\"%s\" not found or can't be opened.\n", params.cover_name);
		return (1);
	}

	if (access(params.embed_name, F_OK) != 0)
	{
		print_err("\"%s\" not found or can't be opened.\n", params.embed_name);
		return (1);
	}

	image_type_t	cover = get_image_type(params.cover_name);

	if (cover == UNKNOWN)
	{
		print_err("The cover file \"%s\" is not the good file format.\n", params.cover_name);
		return (1);
	}

	FILE	*f;

	f = fopen(params.cover_name, "r+");

	unsigned char	magic[8];
	unsigned char	ihdr[16];
	unsigned char	idat[12];
	int				i;
	fread(magic, 1,8,f);
	fread(ihdr, 4, 4, f);
	
	i = 0;
	printf(" OPENED FILE \n\n");
	while (i < 16)
	{
		printf("%d ", (unsigned int)ihdr[i]);
		i++;
	}
	unsigned long	width = 0;
	unsigned long	height = 0;

	for (int j = 0; j < 4; j++)
	{
		width = (width << 8) | ihdr[8 + j];
		height = (height << 8) | ihdr[12 + j];
	}

	printf("Width x Height : %lux%lu\n", width, height);

	fclose(f);
	return (0);
}
