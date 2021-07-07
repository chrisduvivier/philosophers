# philosophers
42's projoect "Philosophers" (aka Dining Philosophers): learn the basics of threading a process, how to make threads, discover the mutex.

# Resources
Starting Point
- [How to create and join threads in C (pthreads).](https://www.youtube.com/watch?v=uA8X5zNOGw8&ab_channel=JacobSorber)

- [How to pass arguments to and get results from threads. (pthread_create, pthread_join)](https://www.youtube.com/watch?v=It0OFCbbTJE&ab_channel=JacobSorber)

- [Safety and Speed Issues with Threads. (pthreads, mutex, locks)](https://www.youtube.com/watch?v=9axu8CUvOKY&ab_channel=JacobSorber)

- Reading: [Parallel Computing](https://hpc.llnl.gov/training/tutorials/introduction-parallel-computing-tutorial)
# Specifics of the project
## Arguments
- number_of_philosophers
- time_to_die
- time_to_eat
- time_to_sleep
- number_of_times_each_philosopher_must_eat (optional argument)

## Allowed functions
- `memset`
- `printf`
- `malloc`
- `free`
- `write`
- `usleep`
- `gettimeofday`
- `pthread_create`
- `pthread_detach`
- `pthread_join`: wait for a thread to finish
- `pthread_mutex_init`
- `pthread_mutex_destroy`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`

# Notes
## Notions
- `Race condition`: Multiple threads racing who gets to read/write first, leading to inconsistency when manipulating a variable.  
- `Atomic operation`: When a thread r/w ona variable, other thread cannot interupt it. This solves the race condition.
- `Locks (mutex locks)`: "mutualk exclusion locks". Abstraction that allows 1 thread to exclude other threads (these will have to wait).
- `Deadlock`: situation where multiple programs are blocking each other for executing, due to their conditions. (in this example, when each philosopher grabs the fork of their left, none of them will have both forks and will keep waiting.) 

## My approach
- How to check the state of the forks:
    
    Use a circular integer array where philosopher i would check:
    forks[ i ] and forks[ (i + 1) mod N ] (where N is the total number of philosopher)

- How to pass the `i` (position of philosopher on the round table) to `pthread_create`:

    Create a struct that holds the identifier `i`, as well as `t_philo` which keeps arguments about each sleep/eat/think process and the mutex_lock. 
- [Avoid Dead locks](http://journals.ecs.soton.ac.uk/java/tutorial/java/threads/deadlock.html#:~:text=The%20simplest%20approach%20to%20to,All%20chopsticks%20are%20equal./):

    Set an order to forks, so that philosopher always try to grab the lowest forks first. All philosopher grab from their left hand (from 0th), and the Nth philosopher therefore takes a fork from its right hand (0th index in the rounf table) first.

- "The simulation stops when a philosopher dies.":

    Apply a check condition for every iteration for all philosophers.

- "You can’t have more than 10 ms between the death of a philosopher and when it will print its death.":

    This means that starvation check has to be done at a refresh rate shorter than 10ms to notice the death of philosopher.