/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:01:32 by kishizu           #+#    #+#             */
/*   Updated: 2024/09/14 15:18:37 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42
# define WIDTH 1000
# define HEIGHT 1000

# ifndef EPSILON
#  define EPSILON 1e-6
# endif

# define SHADOW_COLOR 0x222222
# define SHADOW_FACTOR 0.5
# define BACKGROUND_COLOR 0x000000

# define _USE_MATH_DEFINES

// keycode and include mlx.h for mac and linux

# ifdef __MACH__
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_R 15
#  define KEY_PLUS 24
#  define KEY_MINUS 27
#  include "mlx.h"
# endif

# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_R 114
#  define KEY_PLUS 59
#  define KEY_MINUS 45
#  include "./minilibx-linux/mlx.h"
# endif

typedef struct s_imgdata
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_imgdata;

typedef struct s_3d_vec
{
	double			x;
	double			y;
	double			z;
}					t_3d_vec;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_ambient_light
{
	double			ratio;
	t_color			color;
}					t_ambient_light;

typedef struct s_camera
{
	t_3d_vec		initial_point;
	t_3d_vec		orient;
	double			fov;
}					t_camera;

typedef struct s_light
{
	t_3d_vec		initial_point;
	double			brightness;
	t_color			color;
}					t_light;

typedef struct s_sphere
{
	t_3d_vec		center_point;
	double			diameter;
	t_color			color;
}					t_sphere;

typedef struct s_plain
{
	t_3d_vec		point;
	t_3d_vec		normal;
	t_color			color;
}					t_plain;

typedef struct s_shape_count
{
	int				sp_count;
	int				pl_count;
	int				cy_count;
}					t_shape_count;

typedef struct s_cylinder
{
	t_3d_vec		center_point;
	t_3d_vec		orient;
	double			diameter;
	double			height;
	t_color			color;
}					t_cylinder;

typedef struct s_rt_info
{
	void			*mlx;
	void			*win;
	t_imgdata		*img_data;
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light			light;
	t_sphere		*sphere;
	t_plain			*plain;
	t_cylinder		*cylinder;
	int				sp_num;
	int				pl_num;
	int				cy_num;
	int				color_map[HEIGHT][WIDTH];
	int				num_camera;
	int				num_light;
	int				num_ambient;
}					t_rt_info;

typedef struct s_detect_status
{
	double			t;
	bool			is_front;
	int				x;
	int				y;
	double			distance;
	double			min_distance;
	double			t_sphere;
	double			t_plain;
	double			t_cylinder;
	t_3d_vec		ray;
	t_3d_vec		hit_point;
	t_3d_vec		shadow_ray;
}					t_detect_status;

typedef struct s_cy_status
{
	double			min_dis;
	bool			hit;
}					t_cy_status;

// get_next_line.c
char				*get_next_line(int fd);

// check_validation.c
int					check_argc(int argc);
int					check_filename(char *filename);
int					check_fileformat(char *filename, t_rt_info *game);

// read_file.c
int					read_rtfile(char *filename, t_rt_info *game);

// mlx_conf.c
int					start_up_window(t_rt_info *game);
int					close_window(void);
int					key_hook(int keycode, t_rt_info *game);
void				set_loop_hook(t_rt_info *game);

// ft_atob.c
double				ft_atob(char *str);

// read_file_utils.c
int					file_open(char *filename);
void				free_split(char **split);
int					count_token(char **line);

// calc_vector_utils.c
double				norm(t_3d_vec vec);
t_3d_vec			vec_add(t_3d_vec vec1, t_3d_vec vec2);
t_3d_vec			vec_sub(t_3d_vec vec1, t_3d_vec vec2);
t_3d_vec			vec_scalar_mult(t_3d_vec vec, double scalar);
t_3d_vec			vec_normalize(t_3d_vec vec);

// calc_vector_utils_sub.c
t_3d_vec			cross_product(t_3d_vec v1, t_3d_vec v2);
double				dot_product(t_3d_vec vec1, t_3d_vec vec2);

// generate_ray.c
t_3d_vec			generate_ray(t_3d_vec initial_point, t_3d_vec target_point);

// convert_screen_points.c
t_3d_vec			convert_screen_points(int x, int y, double fov);
// set_color_map.c
int					set_color_map(t_rt_info *game);

// detection.c
bool				cross_detection_ray_and_plain(t_3d_vec ray,
						t_3d_vec initial_point, t_plain *pl, double *t);
bool				cross_detection_ray_and_sphere(t_3d_vec ray,
						t_3d_vec initial_point, t_sphere *sp,
						t_detect_status *st);
bool				cross_detection_ray_and_cylinder(t_3d_vec ray,
						t_3d_vec initial_point, t_cylinder *cy, double *t);

// detection_cy_utils.c
bool				evaluate_val(double a, double b, double c, double *t_val);

// parse_shape.c
void				config_error(char *message);
void				parse_sp(char **split, t_rt_info *game, int *sp_count);
void				parse_l(char **split, t_rt_info *game);
void				parse_c(char **split, t_rt_info *game);
void				parse_a(char **split, t_rt_info *game);

// parse_shape_sub.c
void				parse_cy(char **split, t_rt_info *game, int *cy_count);
void				parse_pl(char **split, t_rt_info *game, int *pl_count);

// color_utils.c
int					apply_ambient(t_rt_info *game, int color);
int					convert_rgb_to_hex_shadow(int r, int g, int b,
						double brightness);
int					convert_rgb_to_hex(int r, int g, int b, double brightness);

// parse_shape_sub_sub.c
void				check_color_range(int r, int g, int b);

// check_validation_sub.c
void				show_format_error(char c);
void				free_tokens(char **token);

// set_detect_utils.c
void				detect_sphere_on_ray(t_rt_info *game,
						t_detect_status *status);
void				detect_plain_on_ray(t_rt_info *game,
						t_detect_status *status);
void				detect_cylinder_on_ray(t_rt_info *game,
						t_detect_status *status);

// set_detect_utils_sub.c

void				calc_dist_hit_point(t_rt_info *game, t_detect_status *st,
						double t);

// set_color_utils.c
double				calc_dis(t_3d_vec hit_point, t_3d_vec shadow_ray, double t);

bool				is_in_shadow(t_3d_vec shadow_ray, t_3d_vec hit_point,
						t_rt_info *game, double light_distance);
void				set_color(t_rt_info *game, t_detect_status *st,
						char object_type, int i);
void				set_color_shadow(t_rt_info *game, t_detect_status *st,
						char object_type, int i);

// set_color_utils_sub.c
bool				detect_plain_wrapped(t_3d_vec shadow_ray,
						t_3d_vec hit_point, t_rt_info *game,
						double light_distance);

// wrapper_func.c
char				**x_ft_split(char const *s, char c);
char				*x_ft_substr(char const *s, unsigned int start, size_t len);
void				*x_ft_calloc(size_t count, size_t size);
void				*x_malloc(size_t size);
t_3d_vec			calc_offset(t_3d_vec hit_point, t_3d_vec normal,
						t_3d_vec camera_position, double offset_value);

#endif
