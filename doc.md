# COP3503 Project 1 Documentation
Alec Arreche

### Part 1: Complexity of functions
*Important notes:*
- Since our AVL tree is nearly balanced, the height of the tree, **h** is roughly **log(n)**, where **n** is the number of nodes.
- Assume the complexity of `+` operator for strings is constant.
- Assume the complexity of `==` operator for strings is constant.

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
This function will be called recursively **n** times in all cases, where **n** represents the number of nodes in the tree. Therefore, in all cases, this function is **O(n)**.

```c++
    Student *findSuccessor(Student *node)
```
In the *best case*, this function will find the successor on its first call, resulting in **O(1)**. In the *worst case*, the function will not find a successor until it is called on a leaf node. Since the function goes down a level on every call, its worst case is **O(h)**, where **h** represents the height of the tree. On *average*, it will be called in between, still resulting in a complexity of **O(h)**.

```c++
    vector<Student *> inOrderVector(Student *node, vector<Student *> list)
```
This function traverses the entire tree, so in all cases complexity is **O(n)**, where **n** is the number of nodes in the tree.

```c++
    void verifyParams(string command, string params)
```
For this function, let **p** represent the number of characters in `params`. When `command` is not `"searchName"`, all characters of `params` are traversed to ensure there are no spaces and/or create a substring, both of which have a complexity of **O(p )**. When `command` is `"searchName"`, only two characters in `params` are accessed, which is constant time. In conclusion, we have:

- Best Case (command = "searchName"): **O(1 )**
- Worst Case: **O(p)**
- Average Case: **O(p)**

**Primary Functions**
```c++
    Student *insert(Student *node, long ID, string name)
```
Consider the complexity of normal binary search tree insertion. The best case complexity is **O(1)**, and worst and average case complexities are **O(h)**, where **h** represents the height of the tree. We can ignore the rotations in our `insert` since these are constant complexity. However,  when `node` is not null, our `insert` also calls `getHeight`, which we have shown has a complexity of **O(n)** in all cases, resulting in total complexity as:

- Best Case: **O(1)**
- Worst Case: **O(nh)**
- Average Case: **O(nh)**

```c++
    Student *removeID(Student *node, long ID)
```
In normal binary search tree removal, the best case complexity is constant, with average and worst being **O(h)**, where **h** is the height of the tree. However, `removeID` calls `findSuccessor`, which has a best case **O(1)** complexity and worst and averge case **O(h)** complexity. Since we are unable to prove we will obtain the best case for `findSuccessor` on average, we obtain the following complexities:

- Best Case: **O(1)**
- Worst Case: **O(h^2)**
- Average Case: **O(h^2)**

```c++
    Student *searchID(Student *node, long ID)
```
`searchID` is no different from binary search tree search. Therefore for **h** representing height of tree, we have:

- Best Case: **O(1)**
- Worst Case: **O(h)**
- Average Case: **O(h)**

```c++
    string searchName(Student *node, string name)
```
Unlike `searchID`, `searchName` does not enjoy the benefits of a binary search tree, and there can be multiple matches to the same input, so we must always traverse the entire tree. Therefore, for **n** number of nodes, we obtain a complexity of **O(n)** in all cases.

```c++
    string printInOrder(Student *node)
```
This function traverses the entire tree, so in all cases complexity is **O(n)**, where **n** is the number of nodes in the tree.
```c++
    string printPreOrder(Student *node)
```
This function traverses the entire tree, so in all cases complexity is **O(n)**, where **n** is the number of nodes in the tree.
```c++
    string printPostOrder(Student *node)
```
This function traverses the entire tree, so in all cases complexity is **O(n)**, where **n** is the number of nodes in the tree.
```c++
    int printLevelCount(Student *node)
```
This function calls `getHeight` on the root, which results in the worst case complexity of `getHeight`. Therefore, in all cases, the complexity is **O(n)**, where **n** is the number of nodes in the tree.

```c++
    void removeInOrder(Student *node, int N)
```
This function calls `inOrderVector` every time, which is linear complexity. When `N` is out of range, the function throws an exception, so the best case is linear time; otherwise, `removeID` is called. On average, we assume `N` will be in range and hence, the tree will be nonempty. For **n** = nodes in tree and **h** = height of tree, we obtain a complexity of **O(n + h^2)**. But since **h** is roughly equal to **log(n)**, we have **O(n + (log(n))^2)**. Since **O((log(n))^2)** is slower than **O(n)**, we can reach these final complexities.

- Best Case: **O(n)**
- Worst Case: **O((log(n))^2)**
- Average Case: **O((log(n))^2)**

### Part 2: Reflection

In this assignment, I became more comfortable with implementing various functions on an AVL tree.
This includes tree traversal and the balancing of a binary search tree. 
Additionally, this has been my first project for school where I have used Git for version control. 
I still have the same bad habits with git that I have always had, such as not committing enough, but now I have faced real consequences for this after breaking one function and having to revert a large commit resulting rewriting a lot of code, which is exactly how Git should NOT be used. 
Lastly, I gained experience in handling user input, which although rather simple, can be very tedious with handling strings in C++.


If I was to restart this project, I would find a way to tidy up the AVL class.
In my implementation, the AVL class only stores the associated functions, and calling the functions feels sloppy.
For example, if I wanted to create a new tree, I would first have to create a new `AVL` object, supposed named `avl`.
Then, I would set a `Student` pointer to the root and to insert, I would have to call `root = avl.insert()`, which feels very sloppy.
Ideally, the AVL class would store the root as a class property and eliminate the need to redefine `root` on most functions called.
