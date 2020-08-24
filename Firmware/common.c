
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

/*
 * Round the floating point number n to the number of decimal places specified.
 * Note that decimalPlace = 0 means round to nearest int.
 *
 * Also note inaccuracies due to floating point representation
 * 	e.g. fround(123.67) = 123.69999 not 123.7 as expected.
 */
float fround(float n, int decimalPlace)
{
	float f = 0;

	switch (decimalPlace) {
	case 0:
		/* No rounding, just return int */
		f = (n - (int) n > 0.5 ? (int) n + 1 : (int) n);
		break;
	default:
		f = fround(n * decimalPlace * 10, 0) / decimalPlace * 10;
		break;
	}

	return f;
}
