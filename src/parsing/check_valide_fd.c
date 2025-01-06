/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valide_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:51:14 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/06 17:14:54 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_invalid_param(t_game *data);

int	check_valid_fd(t_game *data)
{
	if (check_no(data) == ERROR)
		return (ERROR);
	if (check_so(data) == ERROR)
		return (ERROR);
	if (check_we(data) == ERROR)
		return (ERROR);
	if (check_ea(data) == ERROR)
		return (ERROR);
	if (check_f(data) == ERROR)
		return (ERROR);
	if (check_c(data) == ERROR)
		return (ERROR);
	if (check_invalid_param(data) == ERROR)
		return (ERROR);
	if (check_double_param(data) == ERROR)
		return (ERROR);
	if (check_map_is_last_param(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
