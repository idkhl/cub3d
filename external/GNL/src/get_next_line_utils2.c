/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 07:40:57 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/16 11:22:23 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_free_all_(t_content *inventaire, char *ligne)
{
	if (inventaire)
		free_inventaire(inventaire);
	inventaire = NULL;
	if (ligne)
		ft_free_((void **)&ligne);
	return (NULL);
}

void	ft_free_(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return ;
}
