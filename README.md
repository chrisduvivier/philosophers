# philosophers
42's projoect "Philosophers": learn the basics of threading a process, how to make threads, discover the mutex.

# Specifics of the project
## Arguments
- number_of_philosophers
- time_to_die
- time_to_eat
- time_to_sleep
- [number_of_times_each_philosopher_must_eat]

## Allowed functions
- `memset`
- `printf`
- `malloc`
- `free`
- `write`,
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