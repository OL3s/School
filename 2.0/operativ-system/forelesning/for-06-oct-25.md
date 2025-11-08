# Forelesning 06 - 25. oktober 2023

## Synchronization
Balance = Balance + 1
Instructions:
1. Load Balance to register R1
2. Add 1 to R1
3. Store R1 to Balance

Balance is a shared variable; critical section. (A piece of code only one thread can execute at once.)