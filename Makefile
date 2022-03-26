HEADER_INC	=	-I./include

LIBFT_PATH	=	./libft/

SRC_PATH	=	./src/

SRCS		=	main.c \
				pipex.c \
				utils.c

OBJ_PATH	=	./bin/

OBJS		=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

CC			=	gcc

CFLAGS		=	-Wall #-Werror -Wextra

CFLAGS_FSAN	=	-Wall -Werror -Wextra -g3 -fsanitize=address

NAME		=	pipex

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
				@mkdir -p $(OBJ_PATH)
				@$(CC) $(CFLAGS) $(HEADER_INC) -I$(LIBFT_PATH) -c $< -o $@

$(NAME):		$(OBJS)
				@make -C $(LIBFT_PATH)
				@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft -o $(NAME)

all:			$(NAME)

clean:
				rm -rf $(OBJ_PATH)
				make -C $(LIBFT_PATH) fclean

fclean:			clean
				rm -f $(NAME)

re: 			fclean all

.PHONY:			all clean fclean re bonus
