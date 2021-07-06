/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:35:08 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/06 20:35:10 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void	ping(int signum)
{
	int		retrn;

	if (signum != SIGALRM)
		return ;
	if (g_pingu.status_previous_ping == NOT_RECEIVED)
	{
		ft_printf("Request timeout for icmp_seq %d\n", g_pingu.sequence);
		// stat update
	}
	g_pingu.sequence += 1;
	if (g_pingu.options->count > 0 && g_pingu.sequence > g_pingu.options->count)
		ping_end(e_error_none);
	else
		alarm(PING_INTERVAL);
	retrn = ping_send(g_pingu.sockfd, g_pingu.addrinfo, &g_pingu.sendpacket, g_pingu.sequence);
	g_pingu.status_previous_ping = NOT_RECEIVED;
	if (retrn == e_error_none)
		retrn = ping_reception(g_pingu.sockfd, g_pingu.addrinfo, g_pingu.options, g_pingu.sequence);
	if (retrn != e_error_none)
	{
		print_return_code(retrn);
		exit(retrn);
	}
	g_pingu.status_previous_ping = RECEIVED;
	return ;
}
