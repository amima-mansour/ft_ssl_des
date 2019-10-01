/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_expr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 10:25:08 by amansour          #+#    #+#             */
/*   Updated: 2019/09/30 11:08:30 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"

int		hex_expr(char *hex)
{
	int i;

	i = -1;
	if (!hex)
		return (1);
	while (hex[++i])
	{
		if (!((hex[i] >= '0' && hex[i] <= '9') \
		|| (hex[i] >= 'A' && hex[i] <= 'F') \
		|| (hex[i] >= 'a' && hex[i] <= 'f')))
			return (0);
	}
	return (1);
}
