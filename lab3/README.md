# Hash Hash Hash

An implementation of three different hashtables, one without any multithreading, and two with different lock implementation.

## Building

Build the program by typing "make"

## Running

./hash-table-test -t 4 -s 50000
Generation: 32,592 usec
Hash table base: 387,564 usec
  - 0 missing
Hash table v1: 394,129 usec
  - 0 missing
Hash table v2: 154,257 usec
  - 0 missing

## First Implementation

To avoid race conditions, we have to use mutex to block out critical sections of the code. 
In particular, this included all of the hash_table_v1_add_entry() function. 
Since the function reads the linked list and edits it, we want to prevent other threads from reading and editing at the same time. 


### Performance

./hash-table-tester -t 1 -s 200000
Generation: 32,044 usec
Hash table base: 411,667 usec
  - 0 missing
Hash table v1: 338,250 usec
  - 0 missing
Hash table v2: 353,554 usec
  - 0 missing

./hash-table-tester -t 2 -s 100000
Generation: 33,088 usec
Hash table base: 389,666 usec
  - 0 missing
Hash table v1: 365,039 usec
  - 0 missing
Hash table v2: 201,990 usec
  - 0 missing

./hash-table-tester -t 4 -s 50000 
Generation: 30,451 usec
Hash table base: 392,442 usec
  - 0 missing
Hash table v1: 403,069 usec
  - 0 missing
Hash table v2: 144,060 usec
  - 0 missing

v1 and the base case remain very much the same speed. This is because that in v1, only one thread can read and change the hashtable at once. 
Therefore, other threads sit around the majority of the time and wait until the hashtable is unlocked, while onlyone thread is doing work. 
This along with additional overhead from multi-threading means that v1 is actually slower.

## Second Implementation

In v2's implementation, I created one mutex for each element of the hashtable. 
Then, instead of locking the whole hashtable, I only locked one element of the hashtable at a time.
This will greatly increase the speed of the program, since threads no longer need to wait around very long for individual elements to be unlocked.

### Performance

  While v1 and v2's speed roughly remains the same, 
  v3 offers a slow down of between 25-50% when doubling the thread count.
  This is due to benefits of multithreading and parallelism, multiple threads can work at the same time.
  Theoretically, v3's speed would decrease 50% after doubling the thread count, but we introduce more overhead which slows down the program.

## Cleaning up

To clean up, enter "make clean"
