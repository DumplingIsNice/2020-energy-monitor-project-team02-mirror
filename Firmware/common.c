static short num_length(int num)
{
	short length = 0;
	if (num < 0) ++length, num *= -1; /* For '-' (negative) sign */
	while (num > 0) ++length, num /= 10;
	return length;
}
