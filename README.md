Philosophers 🍝
Dining Philosophers Problem simulation
42 School Project | Thread Synchronization in C

📖 Overview
This project implements a multithreaded simulation of the classic Dining Philosophers Problem, where philosophers alternate between thinking, eating, and sleeping. The challenge is to prevent deadlocks (e.g., fork starvation) while ensuring no philosopher starves. Developed in C using pthread mutexes and threads, this simulation demonstrates core concurrency principles.

🎯 Features
Configurable philosopher count via program arguments

Deadlock prevention using fork ordering (even/odd philosopher strategy)

Real-time status output:
<timestamp> <id> is thinking/eating/sleeping>
<timestamp> <id> died>

Optional meal limit: Stop after N meals per philosopher

Precision timing: Microsecond-level synchronization

Memory-safe: Zero leaks

🛠️ Installation
	clone repo 
 	```cd philosophers  
	make```

🕹️ Usage
```# Mandatory version (mutexes)  
./philo <number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [<meals_needed>]

# Example: 4 philosophers needing 3 meals each  
./philo 4 800 200 200 3  ```

Arguments
```Parameter	Description
number_of_philos	Philosophers (1-200)
time_to_die	Milliseconds before starving
time_to_eat	Milliseconds per meal
time_to_sleep	Milliseconds between meals
meals_needed	(Optional) Stop after N meals```


📜 Compliance
42 School Norm: Strict adherence to coding style

Error Handling: Graceful exit on invalid input

Performance: Handles up tp 200 philosophers without delay

🚀 Bonus
	reimplementation of the mandatory part except using processes and semaphores instead of thread and mutex locks