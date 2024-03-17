# What's in phase_1?

- In phase_1, we call *strings_not_equal*
- In strings_not_equal, we set *%rbx = %rdi*, and *%rbp = rsi*. Then we call *string_length* for the first time.
- What *string_length* does is to **compute the length of the string stored at the register (%rdi)**.
- The length of the string will be stored in %eax. Return to strings_not_equal.
- Call string_length again to compute the length of the string stored in (%rsi)
- If two strings have different length, bomb!
- Then compare each character of two strings. If any character is different, bomb!
- Safe!

One more thing: in phase_1, the instruction `mov $0x402400, %esi` tells the address of the hidden string. Use gdb to find it out:

```gdb
(gdb)x /s 0x402400
```

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
0x402400:	"Border relations with Canada have never been better."

