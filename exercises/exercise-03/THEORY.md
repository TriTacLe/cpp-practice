## Task 1: errors in the original Circle

| Original | Problem |
|----------|---------|
| `circle(double radius_);` | The constructor has to be named exactly like the class, so `Circle`. |
| `int get_area() const;` | An area is not an integer. The return type has to be `double`, otherwise the decimals are cut off silently. |
| `private double radius;` | `private` is an access specifier and needs a colon: `private:`. |
| `}` | A class definition ends with a semicolon: `};`. |
| `public Circle::Circle(...)` | `public` is not written on definitions outside the class. |
| `: radius_(radius)` | The initialiser list is reversed. The member is initialised from the parameter: `radius(radius_)`. |
| `int Circle::get_area() { ... }` | Missing `const`. The definition has to match the declaration exactly, otherwise it is a new function that overrides nothing. |
| `Circle::get_circumference() const { ... }` | Missing return type. |
| `circumference = 2.0 * pi * radius;` | `circumference` is never declared. |

## Task 2: the holes in the client program

The original:

```cpp
/*---*/ circle(5);
/*---*/ area = circle.get_area();
cout << "Arealet er lik " /*---*/ endl;
double circumference = /*---*/.get_circumference();
```

| Hole | Fill |
|------|------|
| 1 | The type. `Circle circle(5);` calls the constructor with 5. |
| 2 | The type of `area`. `get_area()` returns `double`. |
| 3 | Two output operators, one for `area` and one for `endl`. |
| 4 | The object it is called on, so `circle`. |
