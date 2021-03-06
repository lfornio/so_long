NAME		= 	so_long
SRCS		= 	sources/so_long.c \
				sources/function_0.c \
				sources/function_1.c \
				sources/function_2.c \
				sources/function_3.c \
				sources/function_4.c \
				sources/function_5.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c
SRCS_BONUS	= 	sources_bonus/so_long_bonus.c \
				sources_bonus/function_b_0.c \
				sources_bonus/function_b_1.c \
				sources_bonus/function_b_2.c \
				sources_bonus/function_b_3.c \
				sources_bonus/function_b_4.c \
				sources_bonus/function_b_5.c \
				sources_bonus/function_b_6.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c
CC 			= 	gcc
FLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	so_long.h
INCLUDES_B	=	so_long_bonus.h
OBJS		=	$(SRCS:.c=.o)
OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)
LIBFT_A		=   libft/libft.a

.c.o: $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

${NAME}: $(OBJS) $(INCLUDE)
	$(MAKE) -C ./libft
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

bonus: $(OBJS_BONUS) $(INCLUDE_B)
	$(MAKE) -C ./libft
	$(CC) $(FLAGS) $(OBJS_BONUS) $(LIBFT_A) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all : libft $(NAME)

debug: $(SRCS) $(INCLUDE)
	$(MAKE) -C ./libft
	$(CC) $(FLAGS) -g $(SRCS) $(LIBFT_A) -lmlx -framework OpenGL -framework AppKit -o debug

clean :
	make -C libft clean
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)


fclean : clean
	rm -f libft/libft.a
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
