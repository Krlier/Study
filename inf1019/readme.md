# Sistemas de Computação

## T1

Routine in C made to simulate how a processor handles different processes. 

The file `Interpretador.c` is responsible for reading from a file the process order and their type (Real Time, Round-Robin, etc). 

The file `Escalonador.c` is resposible for handling the processes and their needs, which is the time of execution and interruptions.


## T2

Routine in C made to simulate a page table. The file `simulador.c` reads from a log file which pages will be acessed, then they are handled accordingly to the size of each page and the amount of physical memory available.