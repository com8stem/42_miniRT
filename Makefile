NAME = miniRT
SRC_DIR = srcs
SRCS = $(SRC_DIR)/calc_vector_utils.c\
	$(SRC_DIR)/calc_vecter_utils_sub.c\
	$(SRC_DIR)/check_validation.c\
	$(SRC_DIR)/check_validation_sub.c\
	$(SRC_DIR)/convert_screen_points.c\
	$(SRC_DIR)/detection.c\
	$(SRC_DIR)/detection_cy.c\
	$(SRC_DIR)/detection_cy_utils.c\
	$(SRC_DIR)/ft_atob.c\
	$(SRC_DIR)/generate_ray.c\
	$(SRC_DIR)/get_next_line.c\
	$(SRC_DIR)/main.c\
	$(SRC_DIR)/mlx_conf.c\
	$(SRC_DIR)/read_file.c\
	$(SRC_DIR)/read_file_utils.c\
	$(SRC_DIR)/set_color_map.c\
	$(SRC_DIR)/parse_shape.c\
	$(SRC_DIR)/parse_shape_sub.c\
	$(SRC_DIR)/color_utils.c\
	$(SRC_DIR)/set_color_utils.c\
	$(SRC_DIR)/set_color_detect_utils.c\
	$(SRC_DIR)/set_color_offset.c\
	$(SRC_DIR)/wrapper_func.c\
	$(SRC_DIR)/parse_shape_sub_sub.c
OBJS = $(SRCS:.c=.o)
HEADERS = include/minirt.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast
LINUX_MLXFLAGS = -lXext -lX11 -lm -Ofast #for Linux
MLXFLAGS = -Imlx -lmlx -framework OpenGL -framework AppKit -lm #for macOS
INCDIR = .
LIBDIR = ./libft
LIBFT = ./libft/libft.a
MLXDIR = ./minilibx-linux
MLXLIB = ./minilibx-linux/libmlx_Linux.a

UNAME_S = $(shell uname -s)

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(MLXLIB) $(HEADERS)
ifeq ($(UNAME_S), Linux)
	@echo "Running on Linux"
	@$(CC) $(OBJS) $(LIBFT) $(MLXLIB) $(CFLAGS) $(LINUX_MLXFLAGS) -o $(NAME)
else ifeq ($(UNAME_S), Darwin)
	@echo "Running on macOS"
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(MLXFLAGS) -o $(NAME)
else
	@echo "Error: Unknown OS"
endif

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCDIR)

$(LIBFT):
	@make -C $(LIBDIR)

$(MLXLIB):
	@make -C $(MLXDIR)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBDIR)
ifeq ($(UNAME_S), Linux)
	@echo "Running on Linux"

else ifeq ($(UNAME_S), Darwin)
	@echo "Running on macOS"
else
	@echo "Error: Unknown OS"
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
	@echo "Error: Unknown OS"
endif

re: fclean all

.PHONY: all clean fclean re
