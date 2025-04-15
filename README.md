# reader-writer-semaphore
A system-level solution to the classical Reader-Writer problem, implemented using custom system calls and semaphores.
# Reader-Writer Problem using Semaphores

A system-level solution to the classical Reader-Writer problem, implemented using custom system calls and semaphores.

## Problem Overview

The Reader-Writer problem addresses synchronization when multiple threads read/write a shared resource. This solution ensures:

- Multiple readers can read simultaneously.
- Writers get exclusive access.
- Avoids starvation.

## Features

- Custom semaphore implementation
- Safe concurrent access
- Fair scheduling

## Technologies Used

- C
- OS-level system calls
- Linux semaphores or POSIX threads (depending on implementation)

## How to Run

1. Compile the source using `gcc`:
   ```bash
   gcc -o reader_writer reader_writer.c -lpthread
