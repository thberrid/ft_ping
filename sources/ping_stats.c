/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_stats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:03:32 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/09 17:03:34 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void	ping_update_stats(int status)
{
	if (status == RECEIVED)
		g_pingu.stats.received += 1;
	else
		g_pingu.stats.lost += 1;
	return ;
}