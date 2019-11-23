# process-scheduling, memory allocation
round robin scheduling in minix, divide user processes into 2 groups, group A has 2x more time than group B. Added system calls checking group of process and changing it.
worst fit memory allocation
# Semaphores/Monitors
4 processes on buffor:
A1 generate even numbers if less than 10 even in buffor, 
A2 generate odd numbers if even > odd in buffor, 
B1 remove even numbers if more than 3 numbers in buffor, 
B2 remove odd numbers if more than 7 numbers in buffor
critical section solved with semaphores/monitors

