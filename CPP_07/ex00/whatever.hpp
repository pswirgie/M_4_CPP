
template <typename T>
void	swap( T& src, T& dst)
{
	T	tmp;
	tmp = src;
	src = dst;
	dst = tmp;
}

template <typename T>
T&	min( T& src, T& dst)
{
	if (src < dst)
		return (src);
	return (dst);
}

template <typename T>
T&	max( T& src, T& dst)
{
	if (src > dst)
		return (src);
	return (dst);
}
