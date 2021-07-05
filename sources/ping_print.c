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

void	ping_print_intro(struct addrinfo *addrinfo, t_options *options)
{
	char address_ip[14];

	(void)options;
	ft_bzero(address_ip, sizeof(address_ip));
	inet_ntop(
		addrinfo->ai_addr->sa_family,
		addrinfo->ai_addr->sa_data + 2, 
		address_ip,
		addrinfo->ai_addrlen
	);
	ft_printf("PING %s (%s) %d(%d) bytes of data\n",
		addrinfo->ai_canonname,
		address_ip,
		ICMP_DATA_LEN,
		ICMP_DATA_LEN + sizeof(struct icmphdr) + sizeof(struct ip)
	);
	ft_printf(":: -1\n");
	return ;
}

void	ping_print_loop(struct ip *ipheader, struct addrinfo *addrinfo, t_options *options)
{
	char address_ip[14];
	struct icmphdr *icmp;

	(void)options;
	ft_bzero(address_ip, sizeof(address_ip));
	inet_ntop(
		addrinfo->ai_addr->sa_family,
		addrinfo->ai_addr->sa_data + 2, 
		address_ip,
		addrinfo->ai_addrlen
	);
	icmp = (struct icmphdr *)((char *)ipheader + sizeof(struct ip));
	ft_printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=0.053 ms\n",
		ICMP_DATA_LEN + sizeof(struct icmphdr),
		addrinfo->ai_canonname,
		address_ip,
		ft_htons(icmp->un.echo.sequence),
		ipheader->ip_ttl
	);
	return ;
}

/*

modele

PING localhost (127.0.0.1) 56(84) bytes of data.

loop : 
64 bytes from localhost (127.0.0.1): icmp_seq=1 ttl=64 time=0.053 ms

--- localhost ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2030ms
rtt min/avg/max/mdev = 0.053/0.099/0.128/0.032 ms

*/