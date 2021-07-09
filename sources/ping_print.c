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
	ft_printf("\n--- %s ping statistics ---\n", addrinfo->ai_canonname);
	ft_printf("%d packets transmitted, %d received, %d%% loss, time %dms\n",
		1,
		1,
		0,
		0
	);
	ft_printf("rtt min/avg/max/mdev = xxxxxxxxxxxx\n");
}

void	ping_print_loop(struct ip *ipheader, struct icmp_packet *icmp, t_options *options)
{
	(void)options;
	ft_printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=0.053 ms\n",
		ICMP_DATA_LEN + sizeof(struct icmphdr),
		g_pingu.addrinfo->ai_canonname,
		g_pingu.address_ip,
		ft_htons(icmp->header.un.echo.sequence),
		ipheader->ip_ttl
	);
//	print_memory(ipheader, sizeof(struct ip));
//	ft_printf("\n");
//	print_memory((char *)ipheader + sizeof(struct ip), sizeof(struct icmp_packet));
	return ;
}