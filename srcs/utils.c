/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 03:57:46 by emma              #+#    #+#             */
/*   Updated: 2024/05/06 00:44:01 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1 = s1;
	const unsigned char	*p2 = s2;

	while (n > 0)
	{
		if (*p1 != *p2)
		{
			return (*p1 - *p2);
		}
		n--;
		p1++;
		p2++;
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
