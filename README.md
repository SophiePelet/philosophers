*This project has been created as part of the 42 curriculum by sopelet*  
  
### Description  
  
This project is an introduction to the concept of **multithreading processes**.  
This project allows you to explore the creation of **threads** and the use of **mutexes**.  
  
#### Project Overview  
  
- **One or more philosophers** sit at a round table. There is a large bowl of spaghetti  
in the middle of the table  
- The philosophers take turns **eating**, **thinking**, and **sleeping**  
While they are eating, they are not thinking nor sleeping;  
while thinking, they are not eating nor sleeping;  
and, of course, while sleeping, they are not eating nor thinking   
- There are **forks** on the table. There are as many forks as philosophers  
- a philosopher must pick up both the fork to their right and the fork to their left before eating  
- When a philosopher has finished eating, they put their forks back on the table and start sleeping.  
Once awake, they start thinking again. **The simulation stops when a philosopher dies of starvation**  
- Every philosopher needs to eat and **should never starve**  
- **Philosophers do not communicate** with each other  
- Philosophers do not know if another philosopher is about to die  
- Philosophers should **avoid dying**  
  
#### Global rules  
  
* **Arguments** :  
    - **number_of_philosophers**: the number of philosophers (also the number of forks)  
    - **time_to_die** (in ms): if a philosopher has not started eating within  
    **time_to_die milliseconds** since the start of their last meal or the start of the simulation,  
    they die  
    - **time_to_eat** (in ms): the time it takes for a philosopher to eat. During that time,  
    they will need to hold two forks  
    - **time_to_sleep** (in ms): the time a philosopher will spend sleeping  
    - **nb_of_times_each_philosopher_must_eat** (**optional**): if all philosophers have eaten at least  
    **number_of_times_each_philosopher_must_eat** times, the simulation stops. If not specified,  
    the simulation stops when a philosopher dies  
* Each philosopher has a number ranging from 1 to **number_of_philosophers**  
  
### Instructions  
  
* Compile the *philo* program using:  
```make```  
* Run the program using:  
```./philo philo_arguments```  
* Remove the objects files using:  
```make clean```  
* Remove the objects files and the executable using:  
```make fclean```  
* Clean and remake everything using:  
```make re```  
  
### Resources  
  
Before starting this project I read documentation about multithreading processes and mutexes:  
* About **threads**:
    * [Threads overview](https://www.geeksforgeeks.org/c/multithreading-in-c/)  
    * [About threads](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)
    * [Intro to threads](https://youtu.be/d9s_d28yJq0?si=LKXtLoVjyCIBCDhJ)  
    * [Processes Vs Threads](https://youtu.be/IKG1P4rgm54?si=3gBn4z0Z6lLGGCSP)  
    * [Race conditions](https://youtu.be/FY9livorrJI?si=1Way2BIQGRJVKM8z)  
    * [Threads in loops](https://youtu.be/xoXzp4B8aQk?si=cyQBEnMhLCPqIe7L)  
  
* About **mutexes**:  
    * [What is a mutex](https://youtu.be/oq29KUy29iQ?si=bIxoxR8oeY2S0A08)  
    * [Mutexes overview](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)  
  
* About **AI use**:  
AI was used as an educational tool. It was used as a tool to have a better understanding of the  
core concepts of the project.  
It was also used during the testing phase of the project.  
  
### Grade  
100/100