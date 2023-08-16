/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:59:42 by binurtas          #+#    #+#             */
/*   Updated: 2022/12/17 12:08:12 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* ---------- GNL ------------ */
char	ft_gnl_strchr(char *str, char c);
char	*ft_gnl_strjoin(char *s1, char *s2);
int		ft_gnl_strlen(char *str);
char	*get_line(char *str);
char	*next_str(char *str);
char	*read_the_line(char *str, int fd);
char	*get_next_line(int fd);
#endif
