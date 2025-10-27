# Homework

## 7.6

Source code: `m.c` and `new_swap.c`

### Difference between 7.1 and 7.6

- `bufp1` is an **uninitialized STATIC** variable
- A new **STATIC** function `incr`
- `count` is a **LOCAL STATIC** variable in `incr`

### Answer

| Symbol | .symtab entry? | Symbol Type | Module where defined | Section |
| --------------- | --------------- | --------------- | --------------- | --------------- |
| buf | true | EXTERN | m.o | .data |
| bufp0 | true | GLOBAL | swap.o | .data |
| bufp1 | true | LOCAL | swap.o | .bss |
| swap | true | GLOBAL | swap.o | .text |
| temp | false | |  |  |
| incr | true | LOCAL | swap.o | .text |
| count | true | LOCAL | swap.o | .bss |

## 7.7

> Source code: `foo5.c` and `bar5.c`. Remember to compile using `-Og` flag.

1. Simply delete the line `x = -0.0` and do nothing. It works fine.
2. Modify x to make `x = 15213` and `y = 15212`. We need x to be of 64-bit hex value: `0x00003b6d00003b6c`.
   - Translate this hex value into double value (more than 300 digits)
   - Use `memcpy` to set x. Note that `sizeof(x)` returns the size of a double type, not an int type in `bar5.c`

## 7.8

### A

```C
/* Module 1 */
int main() {}

/* Module 2 */
static int main = 1;
int p2() {}
```

- (a): REF(main.1) -> DEF(main.1);
- (b): REF(main.2) -> DEF(main.1);

### B

```C
/* Module 1 */
int x;
void main() {}

/* Module 2 */
double x;
int p2() {}
```

- (a): REF(x.1) -> UNKNOWN;
- (b): REF(x.2) -> UNKNOWN;

### C

```C
/* Module 1 */
int x = 1;
void main() {}

/* Module 2 */
double x = 1.0;
int p2() {}
```

- (a): ERROR;
- (b): ERROR;

## 7.9

> Source code: `foo6.c` and `bar6.c`

Because `main` is a global function symbol after linking `foo6` and `bar6` together, the `printf` statement in `p2` prints the contents pointed to by the pointer to the `main` function. Using `objdump` on the executable object file, you should see that the instruction (byte presentation) at `<main>` matches the value printed by the program.

## 7.10

- A. `gcc p.o libx.a`
- B. `gcc p.o libx.a liby.a libx.a`
- C. `gcc p.o libx.a liby.a libx.a libz.a`

## 7.11

The 8 bytes here are storing the data in .bss section. I've checked that `main.o` and `sum.o`'s .bss section are both empty. But prog contains .bss section of size 8. Use `readelf` to check the `prog`, I found two symbols inside .bss section:

1. `completed.0`, OBJECT type
2. `__bss_start`, NOTYPE type

It should be this `completed.0` that takes 8 bytes in .bss section.

## 7.12

- A: `0x4004f8 - 0x4 - 0x4004ea` = `0xa`
- B: `0x400500 - 0x4 - 0x4004da` = `0x22`

## 7.13

> The answer can vary across different machines.

### A

- `libc.a`: 2055 object files: `readelf -h /usr/lib/x86_64-linux-gnu/libc.a | grep 'File:' | wc -l`
  > Better approach: using `ar`: `ar t /usr/lib/x86_64-linux-gnu/libc.a | wc -l`
- `libm.a` is **an ASCII TEXT** file instead of an ELF format file in my WSL2. The script is:

  ```Zsh
  /* GNU ld script
  */
  OUTPUT_FORMAT(elf64-x86-64)
  GROUP ( /usr/lib/x86_64-linux-gnu/libm-2.35.a /usr/lib/x86_64-linux-gnu/libmvec.a )
  ```

  So I think I should count these 2 files using `ar t` command: `libm-2.35.a` contains 795 object files, and `libmvec.a` contains 548 object files.

### B

It generates exactly the same code to execute. But without `-g` flag, all sections related to debugging (e.g., `.debug_info`, `.debug_line`...) will not be included.

### C

**Use `ldd`**: `ldd <executable>`.

```Bash
linux-vdso.so.1 (0x00007ffea31c9000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007dd7cc200000)
/lib64/ld-linux-x86-64.so.2 (0x00007dd7cc4d1000)
```

