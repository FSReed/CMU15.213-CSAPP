# What's in phase_3?

1. The value passed to `%rdx` and `%rcx` will serve as the start and the end of the address interval. In phase_3, we have 2 inputs.
2. First check the input should be more than 1. Otherwise, bomb!
3. Then, check **if the value of input[0] belongs to the interval [0, 7]**. If not, bomb!
4. The value of input[0] will be used to compute the address based on $address = 0x402470 + rax \times 8$.
5. As the value of `%fax` has been restricted to 0 to 7, there are 8 addresses to choose. Below is the output by gdb:

```Output from gdb
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./bomb...
0x402470:	5.8830265e-39	0	5.88311198e-39	0
0x402480:	5.88303631e-39	0	5.88304612e-39	0
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./bomb...
0x402470:	0x0000000000400f7c	0x0000000000400fb9
0x402480:	0x0000000000400f83	0x0000000000400f8a
0x402490:	0x0000000000400f91	0x0000000000400f98
0x4024a0:	0x0000000000400f9f	0x0000000000400fa6
```

6. Use the address accessed by the first input, we can get the second value in the memory. So there will be **8 pairs of correct answers**.
7. If the pair (input[0], input[1]) matches the correct answer, pass!

PS: All 8 pairs:
- (0, 0xcf)
- (1, 0x137)
- (2, 0x2c3)
- (3, 0x100)
- (4, 0x185)
- (5, 0xce)
- (6, 0x2aa)
- (7, 0x147)

