# Short compilation guide

Compilation - simply run make

## Compilation options:
Compilation options are provided throught foo var in make. Options are:
* -DtestNum - num of changable symbols per thread + 1. Example: 3 means that the last two symbols will be changed in the thread during bruteforce.
* -Dmutex - makes program use mutexes instead of spinlocks
* -DNUM_OF_THREADS - num of threads.

example:

     make foo='-DNUM_OF_THREADS=12 -DtestNum=2 -Dmutex' bruteforce_mutex_one
