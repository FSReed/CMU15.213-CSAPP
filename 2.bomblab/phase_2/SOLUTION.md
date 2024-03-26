# What's in phase_2?

1. Read six numbers from the stdin and store them into the memory. The starting address of these six numbers would be stored in %rsp.
2. Check if the input has more than 5 numbers. If not, bomb!
3. Check if the first number equals to 1. If not, bomb!
4. Set `%rbx` and `%rbp`, so that `%rbx` points to the second number, and `%rbp` points to the top of the 6th number (*rbp points to garbage*).
5. Let $A$ be the number pointed by `%rbx`, and $P$ is the number precedes $A$. Check if $A = 2 * P$ for the rest 5 numbers.
6. So the input should be these 6 numbers: `1 2 4 8 16 32`.

