# philosopher
An introduction to multi-thread programming by solving the dinning problem at 42 London



### The problem with 200 philosophers
#### hread Scheduling Overhead

- With 200 philosophers, you're creating 200 threads
- The OS scheduler has to manage all these threads
- As the number of threads approaches or exceeds the number of CPU cores, scheduling becomes more complex
#### Resource Contention

- More philosophers mean more mutex locks/unlocks
- More competition for CPU time
- More context switching overhead
#### Timing Precision

- With so many threads, the time between checks for each philosopher becomes less precise
- Some philosophers might get more CPU time than others
- This can lead to inconsistent monitoring of death conditions

#### System-Dependent Behavior

- Different systems handle thread scheduling differently
- Results can vary based on:
    - Number of CPU cores
    - System load
    - OS scheduling policy
    - Available memory