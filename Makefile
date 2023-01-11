NAME = my_program
SRCS = my_program.c
OBJS = $(SRCS:.c=.o)

LIBMLX = minilibx_macos/libmlx.a
LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIBMLX) $(LIBFT)
	gcc $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBMLX) $(LIBFT)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
