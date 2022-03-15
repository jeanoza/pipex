HEADER_INC	=	-I./include

LIBFT_PATH	=	./libft/

SRC_PATH	=	./src/

SRCS		=	main.c \

OBJ_PATH	=	./bin/

OBJS		=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

CC			=	gcc

CFLAGS		=	-Wall
#FIXME: -Wall -Werror -Wextra

CFLAGS_FSAN	=	-Wall -Werror -Wextra -g3 -fsanitize=address

NAME		=	pipex

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
				@mkdir -p $(OBJ_PATH)
				@$(CC) $(CFLAGS) $(HEADER_INC) -I$(LIBFT_PATH) -c $< -o $@

$(NAME):		$(OBJS)
				@make -C $(LIBFT_PATH)
				@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft -o $(NAME)


$(CHECKER):		$(CHECK_OBJS)
				@$(CC) $(CFLAGS) $(CHECK_OBJS) -L$(LIBFT_PATH) -lft -o $(CHECKER)


all:			$(NAME)

clean:
				rm -rf $(OBJ_PATH)
				make -C $(LIBFT_PATH) fclean

fclean:			clean
				rm -f $(NAME)

re: 			fclean all

.PHONY:			all clean fclean re bonus
