# Short compilation guide

make foo='-DtestNum=<num of changable symbols per thread +1> -Dmutex(to use mutexes instead spinlocks) -DNUM_OF_THREADS=<num o fthreads>' bruteforce_mutex_one

example:
     make foo='-DNUM_OF_THREADS=12 -DtestNum=2 -Dmutex' bruteforce_mutex_one
