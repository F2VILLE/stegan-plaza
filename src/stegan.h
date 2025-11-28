#ifndef STEGAN_H
# define STEGAN_H


void	print_usage(char *filename);
typedef enum image_type_e
{
	PNG = 0x00,
	JPG = 0x01,
	UNKNOWN = 0x99
} image_type_t;

typedef struct steg_params_s
{
	char	*cover_name;
	char	*embed_name;
} steg_params_t;

image_type_t	get_image_type(char *path);
steg_params_t	parse_params(int argc, char *argv[]);
void	ft_putchar(int fd, char c);
int		ft_strlen(char *s);
void	ft_putstr(int fd, char *s);
static void	ft_print_format(int fd, char c, va_list *args);
int	print_err(const char *format, ...);

#endif