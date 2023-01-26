NAME = fdf
SRCS = fdf.c parse_map.c
OBJS = $(SRCS:.c=.o)

LIBMLX = minilibx_macos/libmlx.a
LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIBMLX) $(LIBFT)
	gcc $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBMLX) $(LIBFT)

%.o: %.c
	make -C libft/
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C minilibx_macos
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

test:
	make all
	./fdf