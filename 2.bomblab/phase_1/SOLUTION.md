# What's in phase_1?

- In phase_1, we call *strings_not_equal*
- In strings_not_equal, we set *%rbx = %rdi*, and *%rbp = rsi*. Then we call *string_length* for the first time.
- What *string_length* does is to **compute the length of the string stored at the register (%rdi)**.
- The length of the string will be stored in %eax. Return to strings_not_equal.
- Call string_length again to compute the length of the string stored in (%rsi)
- If two strings have different length, bomb!
- Then compare each character of two strings. If any character is different, bomb!
- Safe!

