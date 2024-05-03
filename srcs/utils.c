/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 03:57:46 by emma              #+#    #+#             */
/*   Updated: 2024/05/01 16:56:31 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
	{
		return (0);
	}
	while (n > 0)
	{
		if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0')
		{
			return ((unsigned char)(*s1) - (unsigned char)(*s2));
		}
		++s1;
		++s2;
		--n;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	malloc_error(void)
{
	ft_putstr_fd("Error\nMalloc error\n", 2);
	exit(1);
}

// double	atof(const char *str)
// {
// 	double	res;
// 	double	res2;
// 	char	*c;
// 	int		len;

// 	c = (char *)str;
// 	res = (double)ft_atoi(c);
// 	while (*c && *c != '.')
// 		c++;
// 	if (*c == '.')
// 		c++;
// 	res2 = (double)ft_atoi(c);
// 	len = ft_strlen(c);
// 	while (len--)
// 		res2 /= 10;
// 	if (res >= 0)
// 		return (res + res2);
// 	else
// 		return (res + -res2);
// }