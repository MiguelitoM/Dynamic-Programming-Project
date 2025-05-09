# Lost‑Temple Parenthesization Solver – ASA Project 1 (2024/25)

## Overview
This program automates the **parenthesization** of a sequence of integers under a custom binary operator ⊕ so that the evaluated expression matches a desired result.  
The operator is defined only by its lookup table, supplied as part of the input.  
The solver was developed for the *Analysis and Design of Algorithms* course (ASA) at Instituto Superior Técnico.

### Core idea
Given  

* an *n × n* table describing ⊕, and  
* a sequence of *m* integers followed by the target value,

the solver uses dynamic programming to explore sub‑expressions and records, for each subsequence **S_{i…j}**, every distinct value reachable together with the split point that produced it.  
If at the end a value equal to the target appears for **S_{0…m‑1}**, the algorithm reconstructs the **leftmost** parenthesization that yields it; otherwise it reports failure. This guarantees O(m³) time in the worst case with a memory footprint of O(m²·n).

---

## Repository Layout
```
.
├── main.cpp       # parenthesization solver
├── gerador.cpp    # random instance generator with guaranteed solution
└── README.md      # (this file)
```

---

## Building

| Component | Command |
|-----------|---------|
| **Solver** | `g++ -std=c++11 -O3 -Wall main.cpp -o solver -lm` |
| **Generator** | `g++ -std=c++11 -O3 -Wall gerador.cpp -o generator` |

---

## Running

### Solve an instance
```bash
./solver < input.txt        # reads stdin, writes stdout
# or, with the original naming:
./a.out < tests/instance1
```

### Generate a random instance
```bash
./generator n m > input.txt     # n = table size, m = sequence length
```
The generator always emits an instance that **has at least one valid parenthesization**.

---

## Input / Output format (brief)
* **Line 1:** `n m` – operator table size and sequence length  
* Next *n* **lines:** the operator table (row‑major)  
* **Line n + 2:** *m* integers – the sequence  
* **Last line:** target value  

The solver prints:
```
1
(<leftmost parenthesization>)
```
if successful, or simply  
```
0
```
when no parenthesization yields the target.

---

## Example
```
Input
2 4
1 2
2 1
1 2 2 1
1

Output
1
(((1 2) 2) 1)
```

---

## Learning Outcomes
* Design of bottom‑up DP on expression trees  
* Space reduction strategies for DP grids  
* Random instance generation that preserves solvability  
* C++11 performance tuning with `-O3` and `std::chrono` timing

---

## Authors & License
Developed by <author‑name(s)>.  
Released under the MIT License.
