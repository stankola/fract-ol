//TODO: Header

#include <unistd.h>
#include <string.h>
#include <math.h>
#include "libft.h"
#include "fract-ol.h"

// Might need to reconsider this. If origin is in the center of the screen,
// negative values should be permitted.
int	check_bounds(t_point p)
{
	if (p.x < 0 || p.y < 0 || p.x > SCREEN_WIDTH || p.y > SCREEN_HEIGHT)
		return (0);
	return (1);
}

int	invert_int_by_bytes(int i, unsigned int byteamount)
{
	int	inverted_i;
	int	j;
	int	shift_range;

	if (byteamount > 4)
	{
		ft_fprintf(STDERR_FILENO, "invert_int_by_bytes: %s\n", strerror(33));
		exit (33);
	}
	inverted_i = 0;
	j = -1;
	while (++j < (int)byteamount)
	{
		shift_range = (-byteamount + 2 * j + 1) * 8;
		if (shift_range >= 0)
			inverted_i += (i & (0xFF << (j * 8))) >> shift_range;
		else
			inverted_i += (i & (0xFF << (j * 8))) << -shift_range;
	}
	return (inverted_i);
}
