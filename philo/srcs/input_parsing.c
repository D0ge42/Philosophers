#include "philosophers.h"

/*Standard atoi*/

int	ft_atoi(char *str)
{
	int						i;
	unsigned long long int	nb;
	int						sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i])
	{
		if (!ft_is_digit(str[i]))
			return (0);
		nb = (nb * 10) + (str[i] - '0');
		if (nb * sign > 2147483647)
			return (0);
		i++;
	}
	return (nb * sign);
}

/*Function to check if provided arguments are valid.
 * Check that every value is > 0 but the last one (it can be 0)
 * String must contain digits only and does not exceed int MAX.
 * Check if number of philosophers is valid.
 * Check if number of arguments is valid*/

int	is_input_valid(int ac, char **av)
{
	int	philo_numbers;
	int	i;

	philo_numbers = ft_atoi(av[1]);
	if (philo_numbers > 200)
		return (0);
	i = 1;
	while (i < ac - 1)
	{
		if (!is_str_only_digits(av[i]))
			return (0);
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	if (ft_atoi(av[ac - 1]) < 0)
		return (0);
	return (1);
}

int	is_str_only_digits(char *str)
{
	while (*str)
	{
		if (!ft_is_digit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
