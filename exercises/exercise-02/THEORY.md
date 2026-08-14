## Task 2

```cpp
char *text;
strcpy(text, "Hallo");
```

`text` never got a value. It points at a random address, or at null. `strcpy` writes six characters there without asking.

The behaviour is undefined. Typically either a segmentation fault right away, or the program overwrites something unrelated and crashes somewhere that looks nothing like the real cause. The second case is worse, because the crash shows up far from the bug.

`strcpy` cannot know anything about the space. It gets an address and copies until it hits the null character in the source. Making sure there is room is always the caller's job.

Correct is either an array with a known size:

```cpp
char text[6]; // "Hallo" is 5 characters plus the null character
strcpy(text, "Hallo");
```

or, in C++, `std::string text = "Hallo";` which handles the space itself.

## Task 3

```cpp
char text[5];
strcpy(text, "Hallo");
```

There is room here, but not enough. "Hallo" is five characters, and the terminating null character comes on top. Six bytes are needed and only five exist.

The null character lands right after the array, on memory that belongs to something else. That is a one byte buffer overflow. What happens depends entirely on what happens to sit there: maybe nothing visible, maybe a variable that gets a strange value, maybe a crash. The compiler says nothing, and the program can run correctly many times before it stops doing so.

This is why `strcpy` is considered dangerous and why C++ uses `std::string` instead.

## Task 4

The broken snippet:

```cpp
int a = 5;
int &b;
int *c;
c = &b;
*a = *b + *c;
&b = 2;
```

| Line | Problem |
|------|---------|
| `int &b;` | A reference has to be bound when it is defined. There is no empty reference the way there is an uninitialised pointer. The compiler says "declaration of reference variable 'b' requires an initializer". |
| `c = &b;` | Invalid as long as `b` does not exist. Once `b` is bound to `a`, `&b` gives the address of `a`. A reference has no identity of its own to take the address of. |
| `*a = *b + *c;` | `a` is an int, not a pointer, so `*a` is illegal. Same for `*b`, since `b` is a reference to int. Only `c` can be dereferenced. |
| `&b = 2;` | `&b` is an address value, an rvalue, so you cannot assign to it. To change the value you write `b = 2`, which changes `a`. |

The corrected version is in `task4.cpp`.
