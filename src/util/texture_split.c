#include "../../inc/cub3.h"

int	ft_split_point_lenght(char *str, char *split_point)
{
	int	i;

	i = 0;
	while (str != split_point)
	{
		str++;
		i++;
	}
	return (i);
}

char	*ft_get_first_piece(char *str, char *split_point)
{
	int		len;
	int		i;
	char	*newline;

	len = ft_split_point_lenght(str, split_point);
	newline = malloc(len + 1);
	i = 0;
	while (str != split_point)
	{
		newline[i] = str[i];
		i++;
		str++;
	}
	return (newline);
}

char	**ft_texture_split(char *str, char c)
{
	char	*split_point;
	char	**spl;

	spl = malloc(3 * sizeof(char *));
	split_point = ft_strchr(str, c);
	spl[0] = ft_get_first_piece(str, split_point);
	spl[1] = ft_strdup(split_point + 1);
	spl[2] = 0;
	return (spl);
}
