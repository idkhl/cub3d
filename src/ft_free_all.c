/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:49:40 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/06 17:15:11 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_free_parsing(t_game *data);

void	ft_free_all(t_game *data)
{
	ft_free_parsing(data);
	// ft_free_exec(data);
}


static void	ft_free_parsing(t_game *data)
{
	free_split(data->file);
	ft_free((void **)&data->parsing.no);
	ft_free((void **)&data->parsing.so);
	ft_free((void **)&data->parsing.we);
	ft_free((void **)&data->parsing.ea);
	free_split(data->parsing.map);
}

// static void ft_free_exec(t_game *data)
// {
// 	// t'es fonction a liberer ici utilise ft_free((void **)&ptr); pour liberer la memoire
// }
