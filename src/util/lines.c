#include "../../inc/cub3.h"

int	ft_line_lenght(char *line)
{
	int	i;
	int total;

	i = 0;
	total = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			total += 4;
		else
			total++;
		i++;
	}
	return (total);
}

char	*modificate_line(char *line)
{
	int		i;
	int		j;
	int		limit;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = malloc(ft_line_lenght(line) + 1);
	while (line[i])
	{
		if (line[i] == '\t')
		{
			limit = 4;
			while (limit)
			{
				new_line[j] = '2';
				limit--;
				j++;
			}
		}
		else if (line[i] == ' ')
		{
			new_line[j] = '2';
			j++;
		}
		else
		{
			new_line[j] = line[i];
			j++;
		}
		i++;
	}
	new_line[j] = '\0';
	free(line); // buffer'ı freelerken burası sıkıntı çıkarabilir
	return (new_line);
}
