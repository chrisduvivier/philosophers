#include "philosopher.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = 1;
		if (*str++ == '-')
			sign = -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > LONG_MAX)
			return (-1);
		str++;
	}
	return ((int)(sign * result));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isdigit_string(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (!(ft_isdigit(*str)))
			return (1);
		str++;
	}
	return (0);
}
