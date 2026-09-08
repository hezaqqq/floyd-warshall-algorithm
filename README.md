# Floyd–Warshall Graph Project

An implementation of the Floyd–Warshall algorithm in C to compute shortest paths on directed weighted graphs.

## Description

Graph algorithms can be used to analyse paths and distances between vertices in a graph.

The [Floyd–Warshall algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm) is used to compute the shortest paths between every pair of vertices in a weighted graph.

This project was developed as part of the **Graph Theory course**. The goal of the project is to implement the Floyd–Warshall algorithm in C to compute shortest paths in a graph.

The program loads a graph from a text file, stores it using an adjacency matrix and a predecessor matrix, and then runs the algorithm to find the shortest paths between every pair of vertices.

The program prints the matrices at each step of the algorithm, making it possible to visualize how the distances are updated over time.

It works with directed graphs and supports weighted edges, including negative values.

## Getting Started

### Dependencies

To compile and run the project, you need:

* A C compiler such as **GCC**
* A terminal or command prompt
* A C development environment such as **Visual Studio Code**, **Code::Blocks**, or **CLion** (optional)

The project uses standard C libraries and does not require any external libraries.

The project is designed to run on common operating systems such as Windows, Linux, and macOS, provided a compatible C compiler is available.

### Installing

Clone or download the project files.

Make sure that the graph `.txt` files are available in the location expected by the program.

If necessary, update the graph file path in `main.c`.

### Executing program

Compile the project using your C compiler. For example, with GCC:

```bash
gcc main.c graph.c -o floyd-warshall
```

Then run the program:

**Linux / macOS:**

```bash
./floyd-warshall
```

**Windows:**

```bash
floyd-warshall.exe
```

Once the program starts, follow the instructions displayed in the terminal.

The program will load a graph from a text file and execute the Floyd–Warshall algorithm, displaying the matrices at each step.

1. Select or provide the graph to process.

2. The program loads the graph and initializes the matrices.

3. The Floyd–Warshall algorithm calculates the shortest paths.

4. The matrices are displayed during the execution to visualize the changes.

## Help

### The program does not compile

Make sure that:

* All `.c` and `.h` files are present in the project directory.

* Your C compiler is correctly installed and accessible from the terminal.

* Both `main.c` and `graph.c` are included when compiling the program.

For GCC, you can check your installation with:

```bash
gcc --version
```

### The program does not start

Make sure you are running the executable from the correct directory.

On Linux/macOS:

```bash
./floyd-warshall
```

On Windows:

```bash
floyd-warshall.exe
```

### Testing individual functions

Some functions are not directly used through the main program because they are intended to be used internally by the graph and Floyd–Warshall implementation.

To test these functions directly, modify `main.c` and call the desired function manually.
