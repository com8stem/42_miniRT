#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdbool.h>

# include "./libft/libft.h"

# define BUFFER_SIZE 42
# define WIDTH 1000
# define HEIGHT 1000

# ifndef EPSILON
#  define EPSILON 1e-6
# endif

#define SHADOW_COLOR 0x222222
#define SHADOW_FACTOR 0.5
#define BACKGROUND_COLOR 0x000000

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
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_imgdata;

typedef struct	s_3d_vec
{
	double	x;
	double	y;
	double	z;
}			t_3d_vec;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct	s_ambient_light
{
	double	ratio;
	t_color	color;
}			t_ambient_light;

typedef struct	s_camera
{
	t_3d_vec	initial_point;
	t_3d_vec	orient;
	double		fov;
}				t_camera;

typedef struct	s_light
{
	t_3d_vec	initial_point;
	double		brightness;
	t_color		color;
}				t_light;

typedef struct	s_sphere
{
	t_3d_vec	center_point;
	double		diameter;
	t_color 	color;
}				t_sphere;

typedef struct	s_plain
{
	t_3d_vec	point;
	t_3d_vec	normal;
	t_color		color;
}				t_plain;

typedef struct	s_cylinder
{
	t_3d_vec	center_point;
	t_3d_vec	orient;
	double		diameter;
	double		height;
	t_color		color;
}				t_cylinder;

typedef struct	s_rt_info
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
	int 			color_map[WIDTH][HEIGHT];
	int				num_camera;
	int				num_light;
	int				num_ambient;
}					t_rt_info;

typedef struct	s_detect_status
{
	double		t;
	bool		is_front;
	int			x;
	int			y;
	double		distance;
	double		min_distance;
	double		t_sphere;
	double		t_plain;
	double		t_cylinder;
	t_3d_vec	ray;
	t_3d_vec	hit_point;
	t_3d_vec	shadow_ray;
}				t_detect_status;

//get_next_line.c
char		*get_next_line(int fd);

//check_validation.c
int			check_argc(int argc);
int			check_filename(char *filename);
int			check_fileformat(char *filename, t_rt_info *game);

//read_file.c
int			read_rtfile(char *filename, t_rt_info *game);

//mlx_conf.c
int			start_up_window(t_rt_info *game);
int			close_window(void);
int			key_hook(int keycode, t_rt_info *game);
void		set_loop_hook(t_rt_info *game);

double		ft_atob(const char *str);

//calc_vector_utils.c
double		dot_product(t_3d_vec vec1, t_3d_vec vec2);
double		norm(t_3d_vec vec);
t_3d_vec	vec_add(t_3d_vec vec1, t_3d_vec vec2);
t_3d_vec	vec_sub(t_3d_vec vec1, t_3d_vec vec2);
t_3d_vec	vec_scalar_mult(t_3d_vec vec, double scalar);
t_3d_vec	vec_normalize(t_3d_vec vec);
t_3d_vec	cross_product(t_3d_vec v1, t_3d_vec v2);
//generate_ray.c
t_3d_vec	generate_ray(t_3d_vec initial_point, t_3d_vec target_point);

//convert_screen_points.c
t_3d_vec	convert_screen_points(int x, int y,double fov);
//set_color_map.c
int			set_color_map(t_rt_info *game);

//detection.c
bool		cross_detection_ray_and_plain(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec normal_plain, t_3d_vec point_on_plain, double *t);
bool		cross_detection_ray_and_sphere(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec center_point, double radius, double *t, bool *is_front);
bool		cross_detection_ray_and_cylinder(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec orient, t_3d_vec center_point, double height, double diameter, double *t);

void		config_error(char *message);
void		parse_sp(char **split, t_rt_info *game, int *sp_count);
void		parse_l(char **split, t_rt_info *game);
void		parse_c(char **split, t_rt_info *game);
void		parse_a(char **split, t_rt_info *game);

void		print_rtinfo(t_rt_info *game);
void		free_split(char **split);
int			count_token(char **line);
void		parse_cy(char **split, t_rt_info *game, int *cy_count);
void		parse_pl(char **split, t_rt_info *game, int *pl_count);

int			apply_ambient(t_rt_info *game, int color);
int			convert_rgb_to_hex_shadow(int r, int g, int b, double brightness);
int			convert_rgb_to_hex(int r, int g, int b, double brightness);
void		check_color_range(int r, int g, int b);

void		show_format_error(char c);
void		free_tokens(char **token);

void		detect_sphere_on_ray(t_rt_info *game, t_detect_status *status);
void		detect_plain_on_ray(t_rt_info *game, t_detect_status *status);
void		detect_cylinder_on_ray(t_rt_info *game, t_detect_status *status);

bool		is_in_shadow(t_3d_vec shadow_ray, t_3d_vec hit_point, t_rt_info *game);
void		set_color(t_rt_info *game, int x, int y, char object_type, int i);
void		set_color_shadow(t_rt_info *game, int x, int y, char object_type, int i);

//wrapper_func.c
char **x_ft_split(char const *s, char c);
char *x_ft_substr(char const *s, unsigned int start, size_t len);
char *x_ft_strjoin(char const *s1, char const *s2);
void *x_ft_calloc(size_t count, size_t size);
void *x_malloc(size_t size);
#endif
