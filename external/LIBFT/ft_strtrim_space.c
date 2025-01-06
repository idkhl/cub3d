/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:54:50 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/04 04:28:10 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_space(char const *s1)
{
	int i;
	int j;
	char *dest;

	if (!s1)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;

	while (s1[i] && (s1[i] == '\n' || s1[i] == ' ' || s1[i] == '\t' \
			|| s1[i] == '\v' || s1[i] == '\f' || s1[i] == '\r'))
		i++;

	while (j >= i && (s1[j] == '\n' || s1[j] == ' ' || s1[j] == '\t' \
			|| s1[j] == '\v' || s1[j] == '\f' || s1[j] == '\r'))
		j--;

	dest = ft_substr(s1, i, j - i + 1);
	return (dest);
}