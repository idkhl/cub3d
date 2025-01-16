/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_fd_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:22:48 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/15 18:15:34 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_supp(char *str);

int	check_format_rgb(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ',' && !ft_isspace(str[i]))
		{
			if (!ft_isdigit(str[i]))
				return (ERROR);
		}
		if (str[i] == ',')
			count++;
		if (count == 2)
			break ;
		i++;
	}
	if (count != 2)
		return (ERROR);
	if (check_supp(str + i) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	check_supp(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\n' && ft_isspace(str[i]))
		i++;
	while (str[i] != '\n' && ft_isalnum(str[i]))
		i++;
	while (str[i] != '\n' && ft_isspace(str[i]))
		i++;
	if (str[i] != '\n')
	{
		return (ERROR);
	}
	return (SUCCESS);
}
