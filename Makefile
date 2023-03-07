NAME = fdf
SRCS = fdf.c parse_map.c fdf_utils.c
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
	make -C minilibx_macos/
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
	rm -f $(NAME)
	make all
	./fdf test_maps/42.fdf

test100:
	rm -f $(NAME)
	make all
	./fdf test_maps/100-6.fdf

test10:
	rm -f $(NAME)
	make all
	./fdf test_maps/10-70.fdf

test20:
	rm -f $(NAME)
	make all
	./fdf test_maps/20-60.fdf

testelem:
	rm -f $(NAME)
	make all
	./fdf test_maps/elem.fdf

testmars:
	rm -f $(NAME)
	make all
	./fdf test_maps/mars.fdf

testpylone:
	rm -f $(NAME)
	make all
	./fdf test_maps/pylone.fdf

norm:
	norminette fdf.c fdf.h parse_map.c fdf_utils.c

wrongtest:
	rm -f $(NAME)
	make all
	./fdf test_maps/bullshit.fdf