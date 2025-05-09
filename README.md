# Lost‑Temple Parenthesization Solver – ASA Project 1 (2024/25)

## 🔍 Overview
This program automates the **parenthesization** of a sequence of integers under a custom binary operator ⊕ so that the evaluated expression matches a desired result.  
The operator is defined only by its lookup table, supplied as part of the input.  
The solver was developed for the *Analysis and Design of Algorithms* course (ASA) at Instituto Superior Técnico.

Given  
* an *n × n* table describing ⊕, and  
* a sequence of *m* integers followed by the target value,

the solver uses dynamic programming to explore sub‑expressions and records, for each subsequence **S_{i…j}**, every distinct value reachable together with the split point that produced it.  
If at the end a value equal to the target appears for **S_{0…m‑1}**, the algorithm reconstructs the **leftmost** parenthesization that yields it; otherwise it reports failure.

## 📜 Example
|⊕|1|2|3|
|-|-|-|-|
|1|2|2|1|
|2|3|2|1|
|3|1|3|3|
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

## ⚙️ Compiling

| Component | Command |
|-----------|---------|
| **Solver** | `g++ -std=c++11 -O3 -Wall main.cpp -o solver -lm` |
| **Generator** | `g++ -std=c++11 -O3 -Wall gerador.cpp -o generator` |

## 🧪 Testing

### Generate a random instance
```bash
./generator n m > input.txt     # n = table size, m = sequence length
```
The generator always emits an instance that **has at least one valid parenthesization**.

### Solve an instance
```bash
./solver < input.txt        # reads stdin, writes stdout
```
