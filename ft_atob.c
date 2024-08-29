#include "minirt.h"

static int	_ft_is_space(int n)
{
	if (n == ' ')
		return (1);
	return (0);
}

double ft_atob(const char *str)
{
	double	result;
	double	sign;
	double	factor;
	int		i;

	result = 0.0;
	sign = 1.0;
	factor = 0.1;
	i = 0;
	while (_ft_is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[i]))
		{
			result = result + (str[i] - '0') * factor;
			factor *= 0.1;
			i++;
		}
	}
	return (result * sign);
}