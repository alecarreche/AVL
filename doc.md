# COP3503 Project 1 Documentation
Alec Arreche

### Part 1: Complexity of functions

**Helper Functions**
```c++
    Student *rotateLeft(Student *node)
```
In all cases, this function is **O(1)**.

```c++
    Student *rotateRight(Student *node)
```
In all cases, this function is **O(1)**.

```c++
    Student *rotateLeftRight(Student *node)
```
In all cases, this function is **O(1)**.
```c++
    Student *rotateRightLeft(Student *node)
```
In all cases, this function is **O(1)**.

```c++
    int getHeight(Student *node)
```
This function will be called recursively **h** times in all cases, where **h** represents the height of the tree. Therefore, in all cases, this function is **O(h)**.

```c++
    Student *findSuccessor(Student *node)
```
In the *best case*, this function will find the successor on its first call, resulting in **O(1)**. In the *worst case*, the function will not find a successor until it is called on a leaf node. Since the function goes down a level on every call, its worst case is **O(h)**, where **h** represents the height of the tree. On *average*, it will be called in between, still resulting in a complexity of **O(h)**.

```c++
    vector<Student *> inOrderVector(Student *node, vector<Student *> list)
```
This function traverses the entire tree in all cases, so it is always **O(n)**, where **n** is the number of nodes in the tree.

```c++
    void verifyParams(string command, string params)
```
For this function, let **c** represent the number of characters in `command`, and let **p** represent the number of characters in `params`. For any `command` input, the operator `==` is called, with a time complexity of **O(c )** for strings. When `command` is not `"searchName"`, all characters of `params` are traversed to ensure there are no spaces and/or create a substring, both of which have a complexity of **O(p )**. When `command` is `"searchName"`, only two characters in `params` are accessed, which is constant time. In conclusion, we have:

- Best Case (command = "searchName"): **O(c )**
- Worst Case: **O(cp)**
- Average Case: **O(cp)**

**Primary Functions**
```c++
    Student *insert(Student *node, long ID, string name)
```

```c++
    Student *removeID(Student *node, long ID)
```

```c++
    Student *searchID(Student *node, long ID)
```

```c++
    string searchName(Student *node, string name)
```

```c++
    string printInOrder(Student *node)
```

```c++
    string printPreOrder(Student *node)
```

```c++
    string printPostOrder(Student *node)
```

```c++
    int printLevelCount(Student *node)
```

```c++
    void removeInOrder(Student *node, int N)
```

### Part 2: Reflection

