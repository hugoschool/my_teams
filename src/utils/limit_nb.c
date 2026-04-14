extern inline int limit_nb(int nb, int max)
{
    if (nb > max)
        return max;
    return nb;
}
