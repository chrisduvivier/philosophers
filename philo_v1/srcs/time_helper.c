#include "philosopher.h"

long long gettime_in_ms(void)
{
	struct timeval now;
	long long	time_in_ms;

	gettimeofday(&now, NULL);
	time_in_ms = (now.tv_sec) * 1000LL + (now.tv_usec) / 1000;
	return (time_in_ms);
}

/*
**	wrapper for the function usleep() which takes the duration in
**	micro seconds as input. This allows to pass in time in ms.
*/

int	msleep(unsigned int tms)
{
	return (usleep(tms * 999));
}
