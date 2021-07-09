/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:20:29 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/03 20:20:31 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void	ping_print_intro(char *address_ip, struct addrinfo *addrinfo)
{
	ft_bzero(address_ip, sizeof(address_ip));
	inet_ntop(
		addrinfo->ai_addr->sa_family,
		addrinfo->ai_addr->sa_data + 2, 
		address_ip,
		addrinfo->ai_addrlen
	);
	ft_printf("PING %s (%s) %d(%d) bytes of data.\n",
		addrinfo->ai_canonname,
		address_ip,
		ICMP_DATA_LEN,
		ICMP_DATA_LEN + sizeof(struct icmphdr) + sizeof(struct ip)
	);
	return ;
}

void	ping_print_stats(struct addrinfo *addrinfo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	ft_printf("\n--- %s ping statistics ---\n", addrinfo->ai_canonname);
	ft_printf("%d packets transmitted, %d received, %d%% packet loss, time %lms\n",
		g_pingu.stats.received + g_pingu.stats.lost,
		g_pingu.stats.received,
		ft_percent(g_pingu.stats.lost, g_pingu.stats.received + g_pingu.stats.lost),
		(tv_to_ms(&now) - tv_to_ms(&g_pingu.stats.begin))
	);
	ft_printf("rtt min/avg/max/mdev = xxxxxxxxxxxx\n");
}
#include <stdio.h>
void	ping_print_loop(struct ip *ipheader, struct icmp_packet *icmp, t_options *options)
{
	struct timeval	now;
	float			delta;

	(void)options;
	gettimeofday(&now, NULL);
	delta = tv_to_f(&now) - tv_to_f(&g_pingu.previous_ping_sendtime);
	ft_printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%5f ms\n",
		ICMP_DATA_LEN + sizeof(struct icmphdr),
		g_pingu.addrinfo->ai_canonname,
		g_pingu.address_ip,
		ft_htons(icmp->header.un.echo.sequence),
		ipheader->ip_ttl,
		delta
	);
	return ;
}