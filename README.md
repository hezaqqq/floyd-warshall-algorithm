# Floyd–Warshall Graph Project
![EFREI](https://badgen.net/badge/Project/EFREI/blue?icon=github)
![C](https://img.shields.io/badge/C-A8B9CC?style=flat&logo=c&logoColor=black)

Implementation of the Floyd–Warshall algorithm to compute shortest paths on directed weighted graphs.

## Description

This project was developed as part of the Graph Theory course (SM601I-2526PSP01) at EFREI. The goal is to implement the Floyd–Warshall algorithm in C to compute shortest paths in a graph.

The program loads a graph from a text file, stores it using an adjacency matrix and a predecessor matrix, and then runs the algorithm to find the shortest paths between every pair of vertices.

The program prints the matrices at each step of the algorithm, this helps visualize how the distances are updated over time.

It works with directed graphs and supports weighted edges, including negative values and ensures readability so the matrices stay readable on the terminal.

## Getting Started

### Dependencies

* C compiler (GCC recommended)
* Standard C libraries (`stdio.h`, `stdlib.h`)
* OS: Linux / macOS / Windows (with terminal)
* No external libraries required

### Installing

1. Clone or download the project files
2. Ensure the folder structure is like:
```
/project
├── main.c
├── graph.c
├── graph.h
└── /graphs
    ├── graph1.txt
    ├── graph2.txt
    ├── ...
    └── graph13.txt
```

3. Make sure all graph `.txt` files are in the correct path (same directory or update path in `main.c`)

### Executing program

1. Compile the program:
```
gcc main.c graph.c -o floyd-warshall
```

2. Run the program:
```
./floyd-warshall
```
