/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:47:28 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/16 11:05:56 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_content
{
	char				*content;
	struct s_content	*next;
}						t_content;

char		*get_next_line(int fd);

int			found_newline(t_content *inventaire);

t_content	*ft_lst_get_last(t_content *inventaire);

void		lire_et_addlist(int fd, t_content **inventaire, int *compteur);

void		ajouter_a_inventaire(t_content **inventaire, char *buf, \
				int compteur);

void		extraire_ligne(t_content *inventaire, char **ligne);

void		malloc_ligne(char **ligne, t_content *inventaire);

void		clean_inventaire(t_content	**inventaire);

int			ft_strlen(char *str);

void		free_inventaire(t_content *inventaire);

#endif