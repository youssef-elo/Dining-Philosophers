#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct pmps
{
	int capacity;
	pthread_mutex_t lock;
};

struct pmps pumps[4];

void *fueler(void *nb)
{
	int car_tank;
	int *id = (int *)nb;
	int pump_check[4] ={0,0,0,0};
	while (1)
	{
		for (int i =0; i < 4;i++)
		{
			if (pthread_mutex_trylock(&pumps[i].lock) == 0)
			{
				car_tank =0;
				if (pumps[i].capacity)
				{
					// printf("Fueling car %d at pump %d\n", *id, i);
					if (pumps[i].capacity <= 100)
					{
						car_tank = pumps[i].capacity;
						pumps[i].capacity = 0;
					}
					else
					{
						car_tank = 100;
						pumps[i].capacity -= 100;
						pump_check[i] = 1;
					}
					// sleep(1);
					printf("Car %d is done fueling at %d%%\n", *id, car_tank);
					if (!pumps[i].capacity)
						printf("Pump %d is out of fuel\n", i+1);
				}
				else if (pumps[i].capacity == 0)
					pump_check[i] = 1;
				pthread_mutex_unlock(&pumps[i].lock);
				if (car_tank)
					return NULL;
			}
		}
		int check = 0;
		for (int i =0; i < 4;i++)
		{
			if (pump_check[i])
				check++;
		}
		if (check == 4)
			return NULL;
	}
}

int main(int argc, char **argv)
{
    if ( argc != 3)
        return 0;
    int cars = atoi(argv[1]);
	if (cars > 1000)
		return 0;
    int capacity = atoi(argv[2]);
    pthread_t cars_th[cars];
	for (int i =0; i < 4; i++)
	{
		pumps[i].capacity = capacity;
		pthread_mutex_init(&(pumps[i].lock), NULL);
	}
	for (unsigned long i = 1; i <= cars;i++)
	{
		unsigned long *arg = malloc(sizeof(unsigned long));
		*arg = i;
		pthread_create(cars_th + i -1, NULL, fueler,(void *) arg);
	}
	for ( int i = 0; i < cars; i++)
		pthread_join(cars_th[i],NULL);
}
