/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:07:20 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/06 20:07:22 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

static long	tv_to_ms(struct timeval *tv)
{
	return ((tv->tv_sec * 1000) + (tv->tv_usec / 1000));
}

int		ping_istimeout(struct timeval *start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	ft_printf(":: %d %d\n", tv_to_ms(start), tv_to_ms(&now));
	if (tv_to_ms(&now) - tv_to_ms(start) > PING_INTERVAL)
		return (1);
	return (0);
}
