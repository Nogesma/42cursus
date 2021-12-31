unsigned char	status_code(unsigned char set, unsigned char n)
{
	static unsigned char	status;

	if (set == 1)
		status = n;
	else if (set == 2)
		status += n;
	return (status);
}

unsigned char	is_fork(unsigned char set, unsigned char n)
{
	static unsigned char	is_fork;

	if (set == 1)
		is_fork = n;
	return (is_fork);
}