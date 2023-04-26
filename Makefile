OBJS = fdf.o parse_map.o fdf_utils.o
DEPS = $(OBJS:.o=.d)

LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(LDFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

-include $(DEPS)

%.o: %.c
	cc $(CFLAGS) -Imlx -MMD -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(DEPS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
