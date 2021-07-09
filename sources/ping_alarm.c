/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_alarm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:40:13 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/07 17:40:15 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void			ping_alarm(int signum)
{
	if (signum != SIGALRM)
		return ;
	if (g_pingu.status_previous_ping != RECEIVED && g_pingu.options->verbose_required)
		ft_printf("Request timeout for icmp_seq %d\n", g_pingu.sequence);
	g_pingu.sequence += 1;
	if (g_pingu.options->count > 0 && g_pingu.sequence > g_pingu.options->count)
		ping_end(e_error_none);
	ping_send(
		g_pingu.sockfd,
		g_pingu.addrinfo,
		&g_pingu.sendpacket,
		g_pingu.sequence
	);
	alarm(PING_INTERVAL);
	return ;
}
