# push_swap

Welcome to my **push_swap** project! This is a **C++20** implementation of an École 42 Common Core project designed to sort data on a stack using a limited set of instructions.
This project serves as a personal exercise in understanding and optimizing sorting algorithms and working with **C++20** features, especially the *Standard Template Library (STL)* and *lambda functions*.

## Project Description

The *push_swap* project is a straightforward algorithm challenge: given a set of integer values, two stacks, and a set of instructions, the goal is to sort the data using the minimum number of actions possible. My implementation focuses on achieving this with optimal performance. You can find the project description in the [PDF available in this repository](https://github.com/lorenzoedoardofrancesco/42Cursus/raw/main/push_swap/push_swap.pdf).

> The original project was written in **C**, but this repository contains the **C++20** implementation of the same project.

## Algorithm Performance

To evaluate the efficiency of my algorithm, I ran a series of tests using the [push_swap_tester](https://github.com/SimonCROS/push_swap_tester) by [SimonCros](https://github.com/SimonCROS), with the results as follows:

### 100 Elements Test
```bash
Starting the test: 100 elements, 100 iterations (seed 2795794950)

Worst        : 656 instructions
Average      : 636 instructions
Best         : 617 instructions
Std Deviation: 8.7 instructions
Goal         : 100 % below 700 (0 above)
Accuracy     : 100 % OK (0 KO)
Completed    : 100 %
```

### 500 Elements Test
```bash
Starting the test: 500 elements, 100 iterations (seed 2335630017)

Worst        :  4535 instructions
Average      :  4493 instructions
Best         :  4461 instructions
Std Deviation:  15.2 instructions
Goal         :  100 % below 5000 (0 above)
Accuracy     :  100 % OK (0 KO)
Completed    :  100 % 
```

### 1000 Elements Test
```bash
Starting the test: 1000 elements, 100 iterations (seed 3275014324)

Worst        :  9652 instructions
Average      :  9580 instructions
Best         :  9501 instructions
Std Deviation:  30.1 instructions
Goal         :  100 % below 10000 (0 above)
Accuracy     :  100 % OK (0 KO)
Completed    :  100 %     
```
These results demonstrate the efficiency of the algorithm, consistently performing within the goals set for each test size.

### Big-O Complexity
The **Big-O** complexity of my sorting algorithm is **O(n log n)**, which is typical for efficient comparison-based sorting algorithms. This complexity is inferred from the performance on varying input sizes and the nature of the operations used. For example:

- For an input size of 100 elements, the theoretical number of operations would be approximately `100 * log2(100) = 664` operations.
- For an input size of 500 elements, the theoretical number of operations would be approximately `500 * log2(500) = 4482` operations.
- For an input size of 1000 elements, the theoretical number of operations would be approximately `1000 * log2(1000) = 9965` operations.

These calculations align closely with the observed performance from the test results.


## Video Demonstration

Check out the video below to see the compilation and testing process of the project:

[![asciinema](https://asciinema.org/a/667916.svg)](https://asciinema.org/a/667916)

## Acknowledgments

- The testing tool used is [push_swap_tester](https://github.com/SimonCROS/push_swap_tester) by [SimonCros](https://github.com/SimonCROS). I have edited the print statements to suit my preferences.

Thank you for visiting my project! Feel free to clone the repository and explore the implementation. Your feedback and contributions are welcome!
