# Exercise 2
## A
The difference between fork() and vfork() is ...

## B
Threads share memory, therefore the global variable is incremented without problem.

## C
The threads that do not get access to the resource right away are blocked, and have
to wait for their turn.

The resources are not fairly used, the three first threads are allowed to complete first,
before the last two.

## D
When the program run (without the mutex) we see that the two variables are not always the same.
Most of the time they are off by one, indicating that we are printing between the increments in
thread1.

When we add a mutex around the incrementation and print parts the numbers are always the same.

## E
We solve the problem with a random sleep before grabbing a fork. This way we ensure that
everyone does not try and grab a fork at once. 
