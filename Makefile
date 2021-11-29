NAME = minitalk

CC	=	@gcc

CFLAGS	=	-Wall -Wextra -Werror

LFLAGS	=  -lncurses -lft -L ./libft

HEADER	=	-I include

RM	=	@rm -rf

SRCS =	srcs/minitalk.c

OBJS	=	$(SRCS:.c=.o)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME) 

$(NAME):	$(OBJS)
		make -s -C ./libft
		gcc $(CFLAGS) $(HEADER) ./libft/libft.a -o $(NAME) $(SRCS) $(LFLAGS)
	
clean:
		$(RM) $(OBJS)
		@make clean -C libft

fclean:	clean
		$(RM) $(NAME)
		@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
