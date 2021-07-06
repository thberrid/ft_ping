/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 11:24:00 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/01 11:24:03 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <libft.h>
# include <ft_ping_errors.h>
# include <sys/types.h> 
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <signal.h>

# define HELP_STRING		"Usage: sudo ./ft_ping [-v] [-c count] destination"

/*
	iovlen = sizeof ip header (20)	+
					icmp hedr (8)	+
					ping data (56)
*/

# define IOVLEN  				84
# define ICMP_DATA_LEN			56

# define ICMP_TYPE_ECHO_REQUEST	8
# define ICMP_CODE_ECHO_REPLY	0

struct icmp_packet
{
	struct icmphdr	header;
	char			data[ICMP_DATA_LEN];
};

/*
struct icmphdr
{
	u_int8_t	type;
	u_int8_t	code;
	u_int16_t	checksum;
	union
	{
		struct
		{
			u_int16_t	id;
			u_int16_t	sequence;
		} echo;                        
		u_int32_t gateway;      
		struct
		{
			u_int16_t __unused;
			u_int16_t mtu;
		} frag;                        
	} un;
};
*/

typedef struct	s_options
{
	char		verbose_required;
	int			count;
	int			ttl_max;
	char		*hostname;
	char		*address_ipv4;
}				t_options;

typedef struct	s_ping_stats
{
	int				sent_count;
	int				received_count;
	struct timeval	total;
	struct timeval	min;
	struct timeval	avg;
	struct timeval	max;
	struct timeval	mdev;
}				t_ping_stats;

typedef struct	s_pingdata
{
	int					sockfd;
	int					sequence;
	struct icmp_packet	sendpacket;
	struct addrinfo		*addrinfo;
	char 				address_ip[16];
	t_options			*options;
}				t_pingdata;

extern			t_pingdata g_pingu;

int				check_requirements(int ac);

unsigned short	checksum(void *data, int len);

int 			ping_prepare(int ac, char **av, t_options *options);
int				ping_reception(int sockfd, struct addrinfo *addrinfo, t_options *options);

void			ping_send(int signum);
void			ping_end(int signum);

void 			ping_print_intro(char *address_ip, struct addrinfo *addrinfo);
void			ping_print_loop(struct ip *ipheader, struct icmp_packet *icmp, t_options *options);
void			ping_print_stats(struct addrinfo *addrinfo);

#endif
