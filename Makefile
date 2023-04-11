# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 10:24:40 by lnambaji          #+#    #+#              #
#    Updated: 2023/04/11 15:55:35 by lnambaji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_printf.c ft_strlen.c hexchars.c putchars.c

OBJS			=	$(SRCS:.c=.o)

CC				=	gcc
RM				=	rm -f
CFLAGS			=	-g -Wall -Wextra -Werror

NAME			= libftprintf.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

%.o:			%.c
				$(CC) -g $(FLAGS) -o $@ -c $<

.PHONY:			all clean fclean re