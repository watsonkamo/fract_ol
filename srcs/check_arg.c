/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshintan <eshintan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:25:14 by eshintan          #+#    #+#             */
/*   Updated: 2024/06/13 23:25:17 by eshintan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	validate_start(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '\0') || ((str[i] == '.') && (str[i + 1] == '\0')))
		return (0);
	if (str[i] == '-' || str[i] == '+')
		if (!ft_isdigit(str[++i]))
			return (0);
	if (str[i] == '.')
		return (0);
	return (i);
}

int	validate_characters(char *str, int *i, int *dot)
{
	if (str[*i] == '.')
	{
		if (!ft_isdigit(str[*i + 1]))
			return (0);
		(*dot)++;
	}
	if (!ft_isdigit(str[*i]) && str[*i] != '.')
		return (0);
	(*i)++;
	return (1);
}

int	is_double(char *str)
{
	int	i;
	int	dot;

	dot = 0;
	i = validate_start(str);
	if (i == 0)
		return (0);
	while (str[i])
	{
		if (!validate_characters(str, &i, &dot))
			return (0);
	}
	if (dot > 1)
		return (0);
	return (1);
}
