
/*
 * Return the number of characters that would be needed to represent the integer
 * `num` as a string (returned length does NOT include null-terminator) .
 */
static short num_length(int num)
{
	short length = 0;
	if (num < 0) ++length, num *= -1; /* For '-' (negative) sign */
	while (num > 0) ++length, num /= 10;
	return length;
}
