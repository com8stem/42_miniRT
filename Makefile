NAME = miniRT
SRCS = calc_vector_utils.c\
check_validation.c\
convert_screen_points.c\
detection.c\
ft_atob.c\
generate_ray.c\
get_next_line.c\
main.c\
mlx_conf.c\
read_file.c\
set_color_map.c\
window_conf.c\
parse_shape.c\
parse_shape_sub.c\
print_info.c


OBJS = $(SRCS:.c=.o)
HEADERS = minirt.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
LINUX_MLXFLAGS = -lXext -lX11 -lm
MLXFLAGS = -Imlx -lmlx -framework OpenGL -framework AppKit -lm #for macOS
INCDIR = .
LIBDIR = ./libft
LIBFT = ./libft/libft.a
MLXDIR = ./minilibx-linux
MLXLIB = ./minilibx-linux/libmlx_Linux.a


UNAME_S := $(shell uname -s)

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(MLXLIB) $(HEADERS)
ifeq ($(UNAME_S), Linux)
	@echo "Running on Linux"
	@$(CC) $(OBJS) $(LIBFT) $(MLXLIB) $(CFLAGS) $(LINUX_MLXFLAGS) -o $(NAME)
else ifeq ($(UNAME_S), Darwin)
	@echo "Running on macOS"
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(MLXFLAGS) -o $(NAME)
else
	@echo "Unknown OS"
endif

$(OBJS): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS)	-c $(SRCS) -I $(INCDIR)

$(LIBFT):
	@make -C $(LIBDIR)

$(MLXLIB):
	@make -C $(MLXDIR)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBDIR)
ifeq ($(UNAME_S), Linux)
	@echo "Running on Linux"
	@make clean -C $(MLXDIR)
else ifeq ($(UNAME_S), Darwin)
	@echo "Running on macOS"
else
	@echo "Unknown OS"
endif

fclean:	clean
	@rm -f $(NAME)
	@make fclean -C $(LIBDIR)
ifeq ($(UNAME_S), Linux)
	@echo "Running on Linux"
	@make clean -C $(MLXDIR)
else ifeq ($(UNAME_S), Darwin)
	@echo "Running on macOS"
else
	@echo "Unknown OS"
endif

re: fclean all

.PHONY: all clean fclean re
