SHELL	= /bin/sh
CC		= gcc
VPATH 	= sources
OBJDIR 	= obj

.SUFFIXES:
.SUFFIXES: .c .o

NAME	= ft_ping

INCDIR	= includes

SRCS	= 	main.c \
			check_requirements.c \
			checksum.c \
			parsing.c \
			parsing_fns.c \
			ping.c \
			ping_alarm.c \
			ping_prepare.c \
			ping_print.c \
			ping_reception.c \
			ping_send.c \
			ping_stats.c \
			ping_end.c \
			ping_time.c \
			print_return_code.c
NAME_H	= 	ft_ping.h \
			ft_ping_errors.h \
			ft_ping_parser.h

NAME_O	= $(SRCS:.c=.o)
FILES_O	= $(addprefix $(OBJDIR)/, $(NAME_O))
FILES_H	= $(addprefix $(INCDIR)/, $(NAME_H))

CFLAGS= -Wall -Wextra -Werror -g3 #-fsanitize=address
CPPFLAGS= -I ./$(INCDIR) -I ./libft/includes
LDFLAGS = -L ./libft/ -lft

LIBFT	= ./libft/libft.a

all : $(NAME)

$(NAME) : $(FILES_O) $(FILES_H) $(LIBFT) $(MLX)
	$(CC) $(CPPFLAGS) -o $(NAME) $(FILES_O) $(LDFLAGS)
#	sudo chown root:root $(NAME)
#	sudo chmod u+s $(NAME)

$(OBJDIR)/%.o: %.c $(FILES_H) | $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $@

$(LIBFT) :
	make -C ./libft
	make -C ./libft clean

.PHONY : clean
clean :
	$(RM) -f $(FILES_O)
	#make -C ./libft clean

.PHONY : fclean
fclean : clean
	#make -C ./libft fclean
	$(RM) $(NAME)

.PHONY : re
re : fclean all