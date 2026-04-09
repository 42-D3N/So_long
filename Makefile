NAME = so_long

SRCS =	sources/main.c sources/setup.c sources/parsing.c sources/flood_fill.c \
		sources/game_core.c

OBJS = $(SRCS:.c=.o)
MLX = ./mlx_linux/libmlx.a
LIBFT = ./sources/libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I/usr/include -Imlx_linux
LDFLAGS = -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(OBJS) $(MLX) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(MLX):
	make -C ./mlx_linux

$(LIBFT):
	make -C ./sources/libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C ./mlx_linux
	make clean -C ./sources/libft

fclean: clean
	$(RM) $(NAME)
	make clean -C ./mlx_linux
	make fclean -C ./sources/libft

re: fclean all

.PHONY: all clean fclean re

