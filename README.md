# ft_ping

## ICMP
OSI network layer (3) > implying no port associated

IP protocol 1

https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol

intersting fact : `sudo strace ping 127.0.0.1 -c 1 -4` 

```
HEADER
64 bites
00 -> 07	type
				0	echo reply
				3	dest unreach.
				8 	echo request
				11	time exceeded
				14	timestamp reply
				15	timestamp request
08 -> 15	code
				0 for type 0
				0 for type 8
				0 for type 11 if TTL expired in transit
				1 for type 11 if Fragment reassembly time exceeded
16 -> 31	chcksm
32 -> 63	depends on type/code
```
DATA

ICMP error messages contain a data section that includes a copy of the entire IPv4 header, plus at least the first eight bytes of data from the IPv4 packet that caused the error message. The maximum length of ICMP error messages is 576 bytes.


---
## FUNCTIONS
```
int getaddrinfo(const char *node,
				const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);
	#include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
```

not a bad src, thx ibm = https://www.ibm.com/support/knowledgecenter/SSLTBW_2.3.0/com.ibm.zos.v2r3.halc001/ipciccla_getaddrinfo_parm.htm

- return : getaddrinfo() returns 0 if it succeeds, or some nonzero error codes
- parameters :
	- node : 
			Internet host
			it can be a descriptive name or can be an address string. If the specified address family is AF_INET, AF_INET6, or AF_UNSPEC, valid descriptive names include host names.
	-	service : 
			eg "http" or "8000", cf `cat /etc/services`
			If servname is null, the call shall return network-level addresses for the specified nodename. If servname is not null, it is a null-terminated character string identifying the requested service. This can be either a descriptive name or a numeric representation suitable for use with the address family or families. If the specified address family is AF_INET, [IP6] [Option Start]  AF_INET6, [Option End] or AF_UNSPEC, the service can be specified as a string specifying a decimal port number.
			
		One or both of these two arguments shall be supplied by the application as a non-null pointer
		
		hint : The hints argument points to an addrinfo structure that specifies criteria for selecting the socket address structures returned in the list pointed to by res.  If hints is not NULL it points to an addrinfo structure whose ai_family, ai_socktype, and ai_protocol specify criteria that  limit  the  set  of  socket addresses returned by getaddrinfo()
		
		Specifying hints as NULL is equivalent to setting ai_socktype and ai_protocol to 0;

```
struct addrinfo
{
	int ai_flags;				/* Input flags.
								AI_PASSIVE (0x0001)
									Specifies how to fill in the ai_addr pointed to by the returned res. If the AI_PASSIVE flag is not set in hints.ai_flags, then the returned socket addresses will be suitable for use with connect(2), sendto(2), or sendmsg(2).
								AI_CANONNAMEOK, AI_NUMERICHOST, ...
								*/
	int ai_family;				/* Protocol family for socket
								AF_INET (2), AF_INET6 (10)
								*/
	int ai_socktype;			/* Socket type
								SOCK_STREAM (1), SOCK_DGRAM (2), SOCK_RAW (3)
								SOCK_STREAM is for connection oriented sockets, where the underlying OS creates and manages the headers for L4 (TCP), L3 and L2. OTOH SOCK_RAW provides more fine-grained control over header and packet construction, where the user has to construct and supply the headers and can also manage the contents.
								*/
	int ai_protocol;			/* Protocol for socket
								0 => socket addresses with any protocol can be returned by getaddrinfo()
								IPPROTO_TCP (6)
								IPPROTO_UDP (17)
								If both ai_socktype and ai_protocol are specified as nonzero then they should be compatible, regardless of the value specified by servname. In this context, compatibility means one of the following
								ai_socktype=SOCK_STREAM and ai_protocol=IPPROTO_TCP
								ai_socktype=SOCK_DGRAM and ai_protocol=IPPROTO_UDP
								ai_socktype=SOCK_RAW. In this case, ai_protocol can be anything
								*/
	socklen_t ai_addrlen;		/* Length of socket address => unsigned int On input, this field must be 0 */
	struct sockaddr *ai_addr;	/* Socket address for socket. 				On input, this field must be 0 */
	char *ai_canonname;			/* Canonical name for service location.  	On input, this field must be 0 */
	struct addrinfo *ai_next;	/* Pointer to next in list. 				On input, this field must be 0. */
};

struct sockaddr
{
	__SOCKADDR_COMMON (sa_);	/* Common data: address family and length =>  unsigned short int  */
	char sa_data[14];			/* Address data.  */
};
```

--- 

`const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);`

`#include <arpa/inet.h>`

convert IPv4 and IPv6 addresses from binary to text form

- return: On success, inet_ntop() returns a non-null pointer to dst.  NULL is returned if there was an error, with errno set to indicate the error.

- parameters:
	af : adress family, AF_INET, AF_INET6

---

`int inet_pton(int af, const char *src, void *dst);`
`#include <arpa/inet.h>`

convert IPv4 and IPv6 addresses from text to binary form

AF_INET: ddd.ddd.ddd.ddd

AF_INET6: x:x:x:x:x:x:x:x

0:0:0:0:0:0:0:1 can be abbreviated as ::1

return:
- 1 on success
- 0 is returned if src does not contain a character string representing a valid network address in the specified address family
- -1 If af does not contain a valid address family

---

`int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);`
`#include <sys/types.h>`
`#include <sys/socket.h>`

thx ibm : https://www.ibm.com/support/knowledgecenter/SSLTBW_2.3.0/com.ibm.zos.v2r3.hali001/csetopt.htm

- return: 0 if succes, -1 on error
- parameters:
	- level:
		- SOL_SOCKET (1)
		- IPPROTO_ICMP (2)
		- IPPROTO_TCP (6)
		- IPPROTO_RAW (255)
		
		To manipulate options at the socket level, the level parameter must be set to `SOL_SOCKET`, as defined in SOCKET.H. To manipulate options at the TCP level, the level parameter must be set to `IPPROTO_TCP`
	- optname:
	
		SO_RCVBUF Sets the size of the data portion of the TCP/IP receive buffer in OPTVAL
	
		SO_SNDBUF Sets the size of the data portion of the TCP/IP send buffer in OPTVAL
		https://www.ibm.com/support/knowledgecenter/SSLTBW_2.1.0/com.ibm.zos.v2r1.hala001/cvalue.htm#cvalue
	
		The optval parameter points to a buffer containing the data needed by the set command
		optlen => uint

---

`size_t recvmsg(int sockfd, struct msghdr *msg, int flags);`
`#include <sys/types.h>`
`#include <sys/socket.h>`

If  no  messages  are available at the socket, the receive calls wait for a message to arrive, unless the socket is nonblocking 

- return: the number of bytes received, or -1 if an error occurred
- parameters:
	- flags:

		`MSG_DONTWAIT` (Enables nonblocking operation), 
		
		`MSG_WAITALL` (This flag requests that the operation block until the full request is satisfied.  However, the call may still return less data than requested if a signal is caught, an error or disconnect occurs, or the next data to be received is of a different type than that returned.  This flag has no effect for datagram sockets.)

```
struct msghdr {
	void         *msg_name;			/*	optional address
										points to a caller-allocated buffer that is used to return the source address if the socket is unconnected */
	socklen_t     msg_namelen;    	/* size of address */
	struct iovec *msg_iov;        	/* scatter/gather array describe scatter-gather locations */
	size_t        msg_iovlen;     	/* # elements in msg_iov */
	void         *msg_control;    	/* ancillary data, see below
									The  field  msg_control, which has length msg_controllen, points to a buffer for other protocol control-related messages or miscellaneous ancillary data
									*/
	size_t        msg_controllen; 	/* ancillary data buffer len */
	int           msg_flags;      	/* flags on received message */
};

struct iovec {                    /* Scatter/gather array items */
	void  *iov_base;              /* Starting address */
	size_t iov_len;               /* Number of bytes to transfer */
};

struct cmsghdr {
	size_t cmsg_len;    /* Data byte count, including header
							(type is socklen_t in POSIX) */
	int    cmsg_level;  /* Originating protocol */
	int    cmsg_type;   /* Protocol-specific type */
	/* followed by unsigned char cmsg_data[]; */
};
```

Ancillary data should be accessed only by the macros defined in cmsg(3).

The msg_flags field in the msghdr is set on return of recvmsg() : `MSG_EOR` (end of rec), `MSG_TRUNC`

---
```
size_t sendto(	int sockfd,
				const void *buf, 
				size_t len, 
				int flags,
                const struct sockaddr *dest_addr, 
				socklen_t addrlen);
	#include <sys/types.h>
    #include <sys/socket.h>
```
used to transmit a message to another socket

If  sendto() is used on a connection-mode (SOCK_STREAM, SOCK_SEQPACKET) socket, the arguments dest_addr and addrlen are ignored

Otherwise, the address of the target is given by dest_addr with addrlen specifying its size 

The message is found in buf and has length len

- return: the number of bytes sent.  On error, -1
- parameters: flags MSG_DONTWAIT (Enables nonblocking operation), MSG_EOR, MSG_MORE (the caller has more datato send)

---

```
int socket(int domain, int type, int protocol);
	#include <sys/types.h> 
    #include <sys/socket.h>
```

socket() creates an endpoint for communication and returns a file descriptor

- return: created fd or -1
- parameters:
	- domain: `AF_UNIX`, `AF_INET`, `AF_INET6`
	- type:
		- `SOCK_STREAM` Provides sequenced, two-way byte streams that are reliable and connection-oriented. 
		- `SOCK_DGRAM` Provides datagrams, which are connectionless messages of a fixed maximum length whose reliability is not guaranteed. 
		- `SOCK_RAW` Provides the interface to internal protocols (such as IP and ICMP)
			
			need to be root do use it
			
			chown root:root a.out
		
			chmod u+s a.out
		- protocol: `0 / IPPROTO_TCP / IPPROTO_UDP`

		Normally only a single protocol exists to support a particular socket type within a given protocol family, in which case protocol can be specified as 0
		
		`SOCK_DGRAM` and `SOCK_RAW` sockets allow sending of datagrams to correspondents named in sendto(2) calls.

---

```
int gettimeofday(struct timeval *tv, struct timezone *tz);
#include <sys/time.h>

struct timeval {
	time_t      tv_sec;     /* seconds */
	suseconds_t tv_usec;    /* microseconds */
};

struct timezone {
	int tz_minuteswest;     /* minutes west of Greenwich */
	int tz_dsttime;         /* type of DST correction */
};
```
- return: return 0 for success, or -1 for failure + errno
- parameters: The use of the timezone structure is obsolete; the tz argument should normally be specified as NULL
		
---
```
pid_t getpid(void);
#include <sys/types.h>
#include <unistd.h>
```	
- return id of current process
- cannot fail
	
pid_t	=> int

---
```
uid_t getuid(void);
#include <unistd.h>
#include <sys/types.h>
```	
- return real user ID of calling process
- cannot fail
	
uid		=> unsigned int

---

`void	_exit(int status);`
`#include <unistd.h>`
status 0 ok

---
```
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
#include <signal.h>
```

Avoid its use: use sigaction(2) instead

---

`unsigned int alarm(unsigned int seconds);`
`#include <unistd.h>`

alarm() arranges for a SIGALRM signal to be delivered to the calling process in seconds seconds.

return: the number of seconds remaining until any previously scheduled alarm was due to be delivered, or zero if there was no previously scheduled alarm.
