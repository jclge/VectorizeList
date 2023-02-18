# VectorizeList

##### This Python 3.X package is meant to "vectorize" a list based on a very simple algorithm. It was created to be used on heavy datasets.
Give VectorizeList a list of string and it will return a list of *int*, depending on the arguments:

-   Which represents the strings based on their order of appearance.
-   Which represents the strings based on their number of occurence.
-   Same thing as before but reversed.

### Usage
---
```python
>>> from VectorizeList import compute_list

>>> compute_list(["a", "b", "c", "d", "a"])
[0, 1, 2, 3, 0]
```

```python
>>> from VectorizeList import compute_list

>>> compute_list(["a", "b", "c", "d", "a", "a", "b"], frequency=True, reversed=False)
[3, 2, 0, 1, 3, 3, 2]
```

```python
>>> from VectorizeList import compute_list

>>> compute_list(["a", "b", "c", "d", "a", "a", "b"], frequency=True, reversed=True)
[0, 1, 2, 3, 0, 0, 1]
```

---

*Made with love by Julien Calenge • 2023*

*Please note this is an amateur project and I'm not good enough in C for you to trust my code, but thanks for checking it out, PRs are welcome.*