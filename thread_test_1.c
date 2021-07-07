#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	*myturn() {
	
	for (int i=0; i < 8; i++)
	{
		sleep(1);
		printf("My turn! %d\n", i);
	}
	return (NULL);
}

void	yourturn()
{
	int	i;

	i = 0;
	for (int i=0; i < 3; i++)
	{ 
		sleep(2);
		printf("Your turn! %d\n", i);
	}
	return ();
}

int	main()
{
	pthread_t new_thread;

	pthread_create(&new_thread, NULL, myturn, NULL);
	yourturn();
	pthread_join(new_thread, NULL);     //make it wait for the end of thread before exit main.
	return (0);
}
