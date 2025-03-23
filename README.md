# Philosophers - 42 Project

This project is an implementation of the **Dining Philosophers problem**, showcasing deep understanding of **multithreading, multiprocessing, semaphores, and synchronization** in C. The implementation adheres strictly to the **42 School** requirements, achieving a clean, efficient, and **deadlock-free solution**.

## 🌟 Features
- **Mandatory Part:** Implemented using **only threads**, without a dedicated monitor thread (unlike common implementations).
- **Bonus Part:** Implemented using **both threads and processes**, including a monitor thread to track philosopher states.
- **No deadlocks** - ensures philosophers do not starve.
- **Optimized synchronization** with mutexes and semaphores.
- **Memory-leak free** and robust against race conditions.
- **Different approaches for mandatory and bonus parts, showcasing multiple solutions.**

---

## 🏗️ Implementation Details
### 🔹 Mandatory Part (Threads Only)
- Uses **threads** for each philosopher.
- Implements a solution **without a monitor thread**, making it different from most common approaches.
- Each philosopher picks up forks safely and eats in a synchronized manner.
- Ensures proper handling of shared resources.

### 🔸 Bonus Part (Threads & Processes)
- Uses **both threads and processes** for improved efficiency.
- Implements a **monitor thread** to track philosopher status.
- Uses **semaphores** instead of mutexes for better process synchronization.
- Each philosopher is handled as a separate **process**, preventing race conditions and allowing independent execution.

---

## 🛠️ Compilation & Usage
### 🔧 Build
```bash
make
```

### 🚀 Run the Program
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```
Example:
```bash
./philo 5 800 200 200
```

---

## 📝 Explanation of Arguments
- `number_of_philosophers` - Total number of philosophers.
- `time_to_die` - Time (in ms) a philosopher can stay alive without eating.
- `time_to_eat` - Time (in ms) required to eat.
- `time_to_sleep` - Time (in ms) required to sleep.
- `[number_of_meals]` (Optional) - If provided, the simulation stops once each philosopher has eaten this many times.

---

## 📖 How It Works
1. **Initialization:** Create threads/processes for each philosopher.
2. **Eating & Sleeping:** Each philosopher picks up forks, eats, and then sleeps.
3. **Synchronization:** Mutexes (mandatory) or semaphores (bonus) ensure safe resource access.
4. **Monitor (Bonus Only):** A separate thread/process ensures that no philosopher starves.
5. **Exit Condition:** Program stops when all philosophers have eaten the required number of meals.

---

## 🏆 Why This Implementation?
✅ **Two distinct approaches** - Threads-only for mandatory, Threads + Processes for bonus.
✅ **No monitor thread in mandatory part** - a unique and efficient approach.
✅ **Monitor thread in bonus part** - ensures starvation prevention.
✅ **Uses semaphores in bonus for better process synchronization.**
✅ **Memory-leak free & crash-proof.**

---

## 📜 License
This project is open-source and free to use for educational purposes.

---

A deep dive into concurrency, synchronization, and parallelism! 🧠⚡
