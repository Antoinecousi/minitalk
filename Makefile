SERVER = server

CLIENT = client

CC	=	@gcc

CFLAGS	=	-Wall -Wextra -Werror

LFLAGS	=  -lncurses -lft -L ./libft

LIBFT = ./libft/libft.a

HEADER	=	-I include

RM	=	@rm -rf

SRC_CLIENT =	srcs/client.c
SRC_SERVER =	srcs/server.c

CLIENT_OBJ = $(SRC_CLIENT:.c=.o)
SERVER_OBJ = $(SRC_SERVER:.c=.o)


$(CLIENT) : $(CLIENT_OBJ) $(SERVER)
			$(CC) $(CFLAGS) $(HEADER) $(SRC_CLIENT) $(LIBFT) -o $(CLIENT)

$(SERVER) : $(SERVER_OBJ) 
			make -C ./libft
			$(CC) $(CFLAGS) $(HEADER) $(SRC_SERVER) $(LIBFT) -o $(SERVER)

all: $(MAKELIB) $(SERVER) $(CLIENT)
	
clean:
		$(RM) $(CLIENT_OBJ)
		$(RM) $(SERVER_OBJ)
		@make clean -C libft

fclean:	clean
		$(RM) $(SERVER) $(CLIENT)
		@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
