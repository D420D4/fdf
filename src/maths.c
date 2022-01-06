//
// Created by plefevre on 1/6/22.
//

int ft_sqrt(int nb) {
	int i;
	int b;
	int max;

	max = 46341;
	if (nb < max)
		max = nb;
	if (nb <= 0)
		return (0);
	i = 0;
	i = (max + 1) / 2;
	b = i / 2;
	while (i != nb / i && b > 0) {
		if (i > nb / i)
			i -= b;
		else
			i += b;
		if (b > 1)
			b = (b + 1) / 2;
		else
			b = 0;
		if (i > 46340)
			i = 46340;
	}
	return (i);

}

int ft_abs(int n) {
	if (n > 0)
		return (n);
	return (-n);
}

int ft_max(int n1, int n2) {
	if (n1 > n2)
		return (n1);
	return (n2);
}