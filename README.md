# Parallel Monte Carlo Integration using OpenMP

This repository contains a solution for a laboratory assignment on **Parallelism and Concurrency**. The goal is to numerically calculate the integral of a function using the **Monte Carlo method**, parallelized with **OpenMP** in C.

## Problem

The program calculates the approximate value of the integral for the function:

$$f(x) = e^{-x^2}$$

within the interval $[0, 10]$.

Monte Carlo integration estimates the area by averaging function values at $N$ random points within the interval. The precision of the result depends on the number of samples $N$.

### Key Features
* **Language:** C (Standard Library)
* **Parallelism:** OpenMP
* **Thread Safety:** Uses `rand_r` with unique seeds per thread to ensure thread-safe random number generation.
* **Output:** Integral value, Error estimation, and Execution time.

## Building the Project

To compile the program, you need `gcc` (or a compatible compiler) with OpenMP support.

```bash
gcc -fopenmp -o multi montecarlo.c -lm
