/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 07:00:38 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/07 18:23:12 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_tab(char **str);
void	debbuger(t_game *data);

int main_parser(int argc, char **argv, t_game *data)
{
	if (handle_parsing(argc, argv, data) == ERROR)
		return (ERROR);
	debbuger(data);
	return (SUCCESS);
}


void	print_tab(char **str)
{
	int i = 0;
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
	}
	return ; 
}

void	debbuger(t_game *data)
{
	printf("\n============= MAPS ===============\n");
	printf("\n");
	printf("============= INITIAL MAP =================\n");
	print_tab(data->parsing.map);
	printf("\n");
	printf("============= MAPS FOR EXEC ===============\n");
	replace_space_by_set(data->parsing.map, '1');
	print_tab(data->parsing.map);
	printf("\n");
	printf("=========== VALUE FOLDER ============\n");
	printf("\n");
	printf("NO: %s\n", data->parsing.no);
	printf("SO: %s\n", data->parsing.so);
	printf("WE: %s\n", data->parsing.we);
	printf("EA: %s\n", data->parsing.ea);
	printf("\n");
	printf("r_c: %d\n", data->parsing.r_c);
	printf("g_c: %d\n", data->parsing.g_c);
	printf("b_c: %d\n", data->parsing.b_c);
	printf("\n");
	printf("r_f: %d\n", data->parsing.r_f);
	printf("g_f: %d\n", data->parsing.g_f);
	printf("b_f: %d\n", data->parsing.b_f);
	printf("\n");
	printf("=========== VALUE FOR EXEC ============\n");
	printf("\n");
	printf("pos_x: %f\n", data->parsing.pos_x);
	printf("pos_y: %f\n", data->parsing.pos_y);
	printf("height_maps: %d\n", data->parsing.height_maps);
	printf("lenth_maps: %d\n", data->parsing.lenth_maps);
	printf("direction: %c\n", data->parsing.direction);
	printf("\n");
	printf("\n============= parsing done ! ===============\n");
}

