## Task 1b: how `5 - 3 - fraction1 - 7 - fraction2` is read

Minus is left associative, so the expression groups from the left:

```
((((5 - 3) - fraction1) - 7) - fraction2)
```

The compiler picks an operator one step at a time, from the types of the two operands in that step:

| Step | Expression | Types | Operator |
|------|------------|-------|----------|
| 1 | `5 - 3` | `int - int` | built in integer subtraction, none of our functions |
| 2 | `2 - fraction1` | `int - Fraction` | non member `operator-(int, const Fraction &)` |
| 3 | `(...) - 7` | `Fraction - int` | member `Fraction::operator-(int)` |
| 4 | `(...) - fraction2` | `Fraction - Fraction` | member `Fraction::operator-(const Fraction &)` |

Step 2 is the only one that cannot be a member function. A member is always called on the left operand, and there the left operand is an `int`. You cannot add members to a built in type, so the function has to live outside the class.

Step 1 is worth noticing: `5 - 3` is plain integer arithmetic before any `Fraction` is involved. The class only ever sees the number 2.

With `fraction1 = 1/2` and `fraction2 = 2/3`:

```
5 - 3        = 2
2 - 1/2      = 3/2
3/2 - 7      = -11/2
-11/2 - 2/3  = -37/6
```
