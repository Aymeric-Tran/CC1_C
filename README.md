# B-Tree Database

## Description

This project implements a simple database using a B-Tree to store and manage data. The project includes the following features:
- Data insertion
- Data selection
- Data deletion
- Data display

## Files

- `btree.h`: Declarations of structures and functions for the B-Tree.
- `btree.c`: Implementation of functions for the B-Tree.
- `fp_open.c`: Functions for reading and writing data to a file.
- `main.c`: Main entry point of the program.
- `repl.c`: Command-line interface to interact with the database.

## Commands

- `.exit`: Exit the program.
- `insert`: Insert data into the file and the B-Tree.
- `select`: Display data from the B-Tree.
- `delete`: Delete a key from the B-Tree.
- `show`: Display data from the file.

## Why I Wrote the Code This Way

- Modularity: The code is divided into multiple files (btree.h, btree.c, fp_open.c, main.c, repl.c) to separate concerns and improve maintainability. Each file has a specific responsibility, making the code easier to understand and modify.
- B-Tree Structure: A B-Tree is used for efficient data insertion, deletion, and search operations. B-Trees are well-suited for database implementations due to their balanced nature and ability to handle large amounts of data.
- Command-Line Interface: The REPL (Read-Eval-Print Loop) interface in repl.c allows users to interact with the database using simple commands. This makes the program user-friendly and easy to test.

## Potential Enhancements
- Error Handling: Improve error handling to provide more informative messages and handle edge cases more gracefully.
- Concurrency: Add support for concurrent access to the database, allowing multiple users to interact with the database simultaneously.
- Persistence: Implement a more robust persistence mechanism to ensure data integrity and support larger datasets.
- Indexing: Add indexing capabilities to improve search performance for specific fields.

## Authors
### Aymeric Tran



