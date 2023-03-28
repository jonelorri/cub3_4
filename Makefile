NAME= Cub3d
CC= gcc
CFLAGS= -Wall -Wextra -Werror 
#SANITIZE= -g3 -fsanitize=address
RM= rm -rf
FILES= 	main \
		ft_utils8_m \
		ft_utils7_m \
		ft_utils6_m \
		ft_utils5_m \
		ft_utils4_m \
		ft_utils3_m \
		ft_utils2_m \
		ft_utils_m \
		ft_char_check \

SRC= $(addsuffix .c, $(FILES))
OBJ= $(addsuffix .o, $(FILES))
LIBFT = libft/libft.a

.c.o:
	$(CC) $(CFLAGS) $(SANITIZE) -o $@ -c $^

$(NAME): $(OBJ) 
	@${MAKE} -C libft
	@${MAKE} -s -C mlx 2>.errors
	@$(CC) $(FLAGS) $(SANITIZE) -c $(SRC) 
	@$(CC) $(FLAG) $(SANITIZE) -L mlx  -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ) $(LIBFT)

all: $(NAME)

clean: 
	${MAKE} clean -s -C libft
	$(RM) $(OBJ)

fclean: clean
	${MAKE} fclean -s -C libft
	$(RM) $(NAME)

re: fclean all

run:
	./$(NAME)

.PHONY:all clean fclean re
